#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>

#include "manual.hpp"
class Logger 
{
public:
    Logger(std::string filename);
    ~Logger();
    void log(std::string message, std::string colour = KWHT);

private:
    std::string get_time_stamp();

    std::ofstream file_;
};
