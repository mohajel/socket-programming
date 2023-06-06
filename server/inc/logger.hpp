#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

#include "manual.hpp"

// class Logger
// {
// public:
//     Logger(std::string log_file_name);
//     void log(std::string type, std::string command);

// private:
//     std::string log_file_name;
// };


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    Logger(std::string filename) 
    {
        std::ifstream file(filename);
        if (!file.good())
        {
            std::ofstream new_file(filename);
            new_file.close();
        }
        file_.open(filename, std::ios::out | std::ios::app);
    }

    std::string get_time_stamp()
    {
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::asctime(std::localtime(&now));
        timestamp = timestamp.substr(0, timestamp.size() - 1);
        return timestamp;
    }

    ~Logger() 
    {
        file_.close();
    }

    void log(std::string message, std::string colour = KWHT) 
    {
        if (message == "")
            return;
        std::string data = "[" + this->get_time_stamp() + "] " + message;
        file_ << data << std::endl;
        std::cout << colour << data << KWHT << std::endl;
    }

private:
    std::ofstream file_;
};