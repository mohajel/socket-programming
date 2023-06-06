#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h> 
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <unistd.h>

#if __has_include(<jsoncpp/json/json.h>)
# include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif

#include "manual.hpp"
#include "logger.hpp"

class Server
{

public:
    Server();
    ~Server();
    void start();
    void set_fd_set();
    void run_server();

private:
    Logger *logger;
    int server_port;
    std::string server_ip;
    int setup_server(int port); 
    int accept_client(int server_fd);

    int server_fd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
    
};
