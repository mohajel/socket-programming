// In the Name of God

#include "server.hpp"
#include "manual.hpp"
#include "error.hpp"

#include <iostream>

using namespace std;

Server::Server()
    :
    server_fd(NOT_CONNECTED),
    server_port(SERVER_PORT),
    server_ip(SERVER_IP),
    max_sd(0)
{
    this->logger = new Logger(Paths::LOG_SERVER_PATH);
}

Server::~Server()
{
    delete this->logger;
}


void Server::start() 
{
    server_fd = setup_server(server_port);
    set_fd_set();
    run_server();
}

void Server::set_fd_set()
{
    max_sd = server_fd;
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    FD_SET(STD_IN, &master_set);
}

void Server::run_server()
{
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);

        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            {    
                if (i == server_fd) // new clinet
                {  
                    int new_client_fd = accept_client(server_fd);
                    FD_SET(new_client_fd, &master_set);
                    if (new_client_fd > max_sd)
                        max_sd = new_client_fd;
                    // manager->add_new_client(new_client_fd); //this must be handled with care
                }

                else if (i == STD_IN) //input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                    command[last_char - 1] = '\0';
                    this->logger->log("server :: " + string(command));
                }
                else // client sending msg
                {
                    this->handle_clients_request(i);
                }
            }
        }
    }
}

void Server::handle_clients_request(int client_fd)
{
    char command[MAX_STRING_SIZE] = {0};
    if (recv(client_fd , command, MAX_STRING_SIZE, 0) == 0) // EOF client sending close signal
    {
        this->logger->log("client with fd = " + to_string(client_fd) + " closed", KCYN);
        close(client_fd);
        FD_CLR(client_fd, &master_set);   
    }
    else // client sending msg
    {
        logger->log("client with fd = " + to_string(client_fd) + " :: " + command);
        int status = send(client_fd, command, strlen(command), 0);
        if (status == 0)
            printf("%s***\t could not send to client fd = %d\t***%s\n",KRED, client_fd, KWHT);
    }
}

int Server::setup_server(int port)
{
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
        throw Error(101);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    address.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw Error(102);
	else
		this->logger->log(Info::status[230], KGRN);

	if(listen(server_fd, MAX_CONNECTIONS) < 0)
        throw Error(103);
	else
        this->logger->log(Info::status[231], KGRN);

    return server_fd;
}

int Server::accept_client(int server_fd)
{
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);
    return client_fd;
}

