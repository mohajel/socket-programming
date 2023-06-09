#pragma once

#include <string.h>
#include <vector>

#include "manual.hpp"
#include "logger.hpp"

struct ClientInfo
{
    int fd;
    int id;
};


class Server
{

public:
    Server();
    ~Server();
    void start();

private:
    void set_fd_set();
    void run_server();
    void close_client(int client_fd);
    void handle_clients_request(int client_fd);
    void add_new_client(int client_fd);
    int setup_server(int port); 
    int accept_client(int server_fd);
    void add_client_id(int id, int client_fd);
    void send_msg_to_client(int receiver_id, int msg, int sender_id, int sender_fd);
    
    std::vector<ClientInfo> clients;
    Logger *logger;
    int server_port;
    bool in_closing_status;
    std::string server_ip;

    int server_fd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
    
};
