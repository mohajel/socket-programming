// In the Name of God

#include <cstring>
#include <string>
#include <iostream>

#include "client.hpp"
#include "manual.hpp"
#include "error.hpp"

using namespace std;

Client::Client(int client_id)
    : server_fd(NOT_CONNECTED),
      client_id(client_id),
      max_sd(0)
{
    this->logger = new Logger("client_" + to_string(client_id) + ".log");
}

Client::~Client()
{
    delete this->logger;
}

void Client::start(int port, const char *server_ip)
{
    try
    {
        connect_to_server(port, server_ip);
        set_fd_set();
        send_initial_request(this->client_id);
        send_requests();
    }
    catch (Error &e)
    {
        logger->log(e.what(), KRED);
        exit(EXIT_FAILURE);
    }
}

void Client::connect_to_server(int port, const char *ip)
{
    struct sockaddr_in server_address;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        throw Error(101);
    this->logger->log(Info::status[200], KGRN);
}

void Client::set_fd_set()
{
    FD_ZERO(&master_set);
    FD_SET(STD_IN, &master_set);
    FD_SET(server_fd, &master_set);
    max_sd = server_fd;
}

void Client::send_initial_request(int client_id)
{
    string request = "client " + to_string(client_id);
    send(server_fd, request.c_str(), request.length(), 0);
}

void Client::send_requests()
{
    while (1)
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);
        for (int i = 0; i <= max_sd; i++)
        {
            if (FD_ISSET(i, &working_set))
            {
                if (i == STD_IN) // input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                    command[last_char - 1] = '\0';
                    this->logger->log("client :: " + string(command));
                    send(server_fd, command, strlen(command), 0);
                }
                else if (i == server_fd) // server response
                {
                    char respone[MAX_STRING_SIZE];
                    int input_length = recv(server_fd, respone, MAX_STRING_SIZE, 0);
                    if (input_length == 0) // server closed
                        throw Error(102);
                    respone[input_length] = '\0';
                    this->logger->log("server :: " + string(respone));
                }
                else
                    throw Error(103);
            }
        }
    }
}