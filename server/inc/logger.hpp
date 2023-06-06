#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

class Logger
{
public:
    Logger(std::string log_file_name);
    void log(std::string type, std::string command);

private:
    std::string log_file_name;
};
