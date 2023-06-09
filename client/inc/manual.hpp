#pragma once

#include <sstream>
#include <map>
#include <vector>

#define SERVER_IP "127.0.0.1"
#define PORT 8181
#define MAX_CONNECTIONS 20
#define MAX_NAME_SIZE 256
#define MAX_STRING_SIZE 4096
#define NOT_CONNECTED -1
#define NOT_ASSIGNED -1
#define NOT_FOUND -1
#define STD_IN 0
#define STD_OUT 1

// colors
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

namespace Paths
{
    const std::string LOG_SERVER_PATH = "../logs/";
}
struct Info
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> messages = 
        {
            {101, "CANNOT_CONNECT_TO_SERVER"},
            {102, "SERVER_DISCONNECTED"},
            {103, "PROBLEM_OCCURED_WHILE_SENDING_MESSAGE"},
            {200, "CONNECTED_TO_SERVER_SUCCEFFULLY"},
        };
        return messages;
    }
    static std::map<int,std::string> status;
};