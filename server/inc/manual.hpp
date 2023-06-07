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
#define NOT_CONNECTED -3
#define NOT_FOUND -1
#define STD_IN 0
#define STD_OUT 1

#define MAX_CONNECTIONS 20
#define MAX_NAME_SIZE 256
#define MAX_STRING_SIZE 4096
#define NOT_CONNECTED -3
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

            {109, "THE_ROOM_CAPACITY_IS_FULL"},
            {110, "SUCCESSFULLY_DONE"},
            {111, "THIS_ROOM_ALREADY_EXISTS"},
            {112, "YOU_ARE_NOT_IN_ROOM_YET"},

            {200, "REQUEST_HANDELED_SUCCESSFULLY"},

            {201, "USER_LOGED_OUT_SUCCESSFULLY"},

            {230, "SERVER_BINDED_SUCCESSFULLY"},
            {231, "SERVER_IS_LISTENING"},

            {232, "YOU_LOGED_IN_BEFORE"},
            {311, "USER_SIGNED_UP.ENTER_YOUR -PASS-MONEY-PHONE-ADDR-"},
            {312, "INFORMATION_CHANGED_SUCCESSFULLY"},
            {401, "INVALID_VALUE"},
            {403, "ACCESS_DENIED"},
            {412, "INVALID_CAPACITY_VALUE"},
            {413, "SUCCESSFULLY_LEAVING"},
            {430, "INVALID_USERNAME/PASSWORD"},
            {451, "USER_ALREADY_EXISTS"},
            {503, "BAD_SEQUENCE_OF_COMMANDS"}
        };
        return messages;
    }
    static std::map<int,std::string> status;
};

vector<string> split_string(string line, string delimiters)
{
    vector<string> result;
    string temp;
    for (char i : line)
        if (delimiters.find(i) != string::npos)
        {
            if (!temp.empty())
                result.push_back(temp);
            temp = "";
        }
        else
            temp += i;
    if (!temp.empty())
        result.push_back(temp);
    return result;
}

int string_to_int(const std::string& str) {
    try 
    {
        return std::stoi(str);
    } 
    catch (const std::invalid_argument& ia) 
    {
        return -1;
    }
}