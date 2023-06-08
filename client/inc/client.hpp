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

#include "manual.hpp"


class Client
{
public:
    Client();
    void start();
    void connect_to_server(int port, const char* ip);
    void set_fd_set();
    void send_requests();

private:
    int server_fd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
};
