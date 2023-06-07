// In the Name of God

#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <sstream>

#include "server.hpp"
#include "manual.hpp"
#include "error.hpp"
#include "logger.hpp"

using namespace std;

Server::Server()
    : server_fd(NOT_CONNECTED),
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

        for (int i = 0; i <= max_sd; i++)
        {
            if (FD_ISSET(i, &working_set))
            {
                if (i == server_fd) // new clinet
                {
                    int new_client_fd = accept_client(server_fd);
                    this->add_new_client(new_client_fd);
                }
                else if (i == STD_IN) // input buffer
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

void Server::add_new_client(int new_client_fd)
{
    FD_SET(new_client_fd, &master_set);
    if (new_client_fd > max_sd)
        max_sd = new_client_fd;
    ClientInfo new_client_info = {new_client_fd, NO_ID_ASSIGNED};
    clients.push_back(new_client_info);
    this->logger->log("new client with fd = " + to_string(new_client_fd) + " joined", KCYN);
}

void Server::handle_clients_request(int client_fd)
{
    char command[MAX_STRING_SIZE] = {0};
    if (recv(client_fd, command, MAX_STRING_SIZE, 0) == 0) // EOF client sending close signal
        close_client(client_fd);
    else // client sending msg
    {
        string server_response = Info::status[200];
        vector<string> tokens = split_string(string(command), " ");
        try
        {
            if (tokens[0] == "client" && tokens.size() == 2)
                this->add_client_id(stoi(tokens[1]), client_fd);
            else if (tokens[0] == "send" && tokens.size() == 4)
                this->send_msg_to_client(stoi(tokens[1]), stoi(tokens[2]) + 1, stoi(tokens[3]), client_fd);
            else
                throw Error(106);
        }

        catch (const std::invalid_argument &ia)
        {
            server_response = Info::status[105];
        }
        catch (Error &e)
        {
            server_response = e.what();
        }
        logger->log("client with fd = " + to_string(client_fd) + " :: " + command);
        logger->log("server response to client with fd = " +
                        to_string(client_fd) + " :: " + server_response,
                    KYEL);
        int status = send(client_fd, server_response.c_str(), strlen(server_response.c_str()), 0);
        if (status == 0)
            logger->log(Info::status[107] + "FD=" + to_string(client_fd), KRED);
    }
}

void Server::send_msg_to_client(int receiver_id, int msg, int sender_id, int sender_fd)
{
    //check sender id
    for (int i = 0; i < clients.size(); i++)
        if (clients[i].fd != sender_fd && clients[i].id == sender_id)
            throw Error(108);

    //find reciver fd
    for
    

    // int receiver_fd = get_client_fd(receiver_id);
    // if (sender_fd == NOT_CONNECTED || receiver_fd == NOT_CONNECTED)
    //     throw Error(103);
    // string msg_str = to_string(msg);
    // send(sender_fd, msg_str.c_str(), msg_str.size(), 0);
    // send(receiver_fd, msg_str.c_str(), msg_str.size(), 0);
}

void Server::add_client_id(int id, int client_fd)
{
    for (int i = 0; i < clients.size(); i++)
        if (clients[i].fd == client_fd)
        {
            if (clients[i].id != NO_ID_ASSIGNED)
                throw Error(104);

            clients[i].id = id;
            break;
        }
}

void Server::close_client(int client_fd)
{
    close(client_fd);
    FD_CLR(client_fd, &master_set);
    for (int i = 0; i < clients.size(); i++)
        if (clients[i].fd == client_fd)
        {
            clients.erase(clients.begin() + i);
            break;
        }
    this->logger->log("client with fd = " + to_string(client_fd) + " left", KRED);
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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw Error(102);
    else
        this->logger->log(Info::status[230], KGRN);

    if (listen(server_fd, MAX_CONNECTIONS) < 0)
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
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&address_len);
    return client_fd;
}
