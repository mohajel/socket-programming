// in the name of God

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
#include<unistd.h>

#include "manual.hpp"
#include "client.hpp"

using namespace std;

map<int,string> Info::status =  Info::create_map();

int main(int argc, char const *argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: ./client <client_id>\n");
        exit(EXIT_FAILURE);
    }
    Client client(atoi(argv[1]));
    client.start(PORT, SERVER_IP);

    return 0;
}