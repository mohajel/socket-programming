// In the Name of God

#include <cstring>
#include <string>
#include <iostream>

#include "client.hpp"
#include "manual.hpp"

using namespace std;

Client::Client()
    :
    server_fd(NOT_CONNECTED),
    max_sd(0)
{
}

void Client::connect_and_send_requests_to_server() 
{
    // "hostName":"127.0.0.1",
    // "commandChannelPort":
    // FileDataContainers::config config = file_handler.read_config(Paths::CONFIG_SERVER_DATA_PATH);
    // connect_to_server(config.commandChannelPort, config.hostName.c_str());
    connect_to_server(8181, "127.0.0.1");
    set_fd_set();
    send_requests();
}

void Client::connect_to_server(int port, const char* ip)
{
    struct sockaddr_in server_address;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(ip);

    if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error in connecting to server\n");
        exit(EXIT_FAILURE);
    }
}

void Client::set_fd_set() {
    FD_ZERO(&master_set);
    FD_SET(STD_IN, &master_set);
    FD_SET(server_fd, &master_set);
    max_sd = server_fd;
}

void Client::send_requests()
{
    
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);
        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            { 
                if (i == STD_IN) //input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                    command[last_char - 1] = '\0';
                    printf("YOU ENTERED %s\n\n",command);
                    send(server_fd, command, strlen(command), 0);
                    // char* first_arg = strtok(command, " ");
                }
                else if (i == server_fd) //server response
                {
                    char respone[MAX_STRING_SIZE];
                    int last_char = recv(server_fd, respone, MAX_STRING_SIZE, 0);
                    respone[last_char] = '\0';
                    printf("%s\n\n",respone);
                }
                else
                    printf("\n%s***\tproblem accurd :cant connect to server\t***%s\n", KRED, KWHT);
            }
        }
    }
}