#pragma once

#include <string>

class Error
{
public:
    Error(int error_number , std::string extra_info = "");
    std::string what(bool more_info = false);
private:
    int error_number;
    std::string extra_info;
};