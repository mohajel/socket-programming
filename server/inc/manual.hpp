#pragma once

#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <map>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8181
#define NO_ID_ASSIGNED -1

#define MAX_CONNECTIONS 20
#define MAX_NAME_SIZE 256
#define MAX_STRING_SIZE 4096
#define NOT_CONNECTED -1
#define NOT_FOUND -1
#define STD_IN 0
#define STD_OUT 1

//colors
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

//messages
#define WELCOME_MESSAGE "welcome to khane ghamar khanom\n0. signin\n1. signup\nCommand -> <Choice number>\n"

namespace Paths
{
    const std::string LOG_SERVER_PATH = "../logs/server.log";
}

struct Info
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> messages = 
        {
            {101, "CANNOT_CREATE_FD_FOR_SERVER"},
            {102, "ERROR_WHILE_BINDING"},
            {103, "ERROR_IN_LISTENING"},
            {104, "CLIENT_ALREADY_HAS_AN_ID"},
            {105, "INVALID_NUMBER_FORMAT"},
            {106, "INVALID_COMMAND_FORMAT"},
            {107, "COULD_NOT_SEND_RESPONSE_TO_CLIENT"},
            {108, "INVALID_SENDER_ID"},
            {109, "REQUESTED_CLIENT_IS_NOT_CONNECTED"},
            {110, "ID_ALREADY_ASSIGNED"},
            {111, "CANT_SEND_MASSEGE_TO_YOURSELF"},

            {200, "REQUEST_HANDELED_SUCCESSFULLY"},
            {201, "USER_LOGED_OUT_SUCCESSFULLY"},
            {230, "SERVER_BINDED_SUCCESSFULLY"},
            {231, "SERVER_IS_LISTENING"},
        };
        return messages;
    }
    static std::map<int,std::string> status;
};