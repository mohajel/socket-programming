#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "utils.hpp"

using namespace std;


std::vector<std::string> split_string(std::string line, std::string delimiters)
{
    std::vector<std::string> result;
    std::string temp;
    for (char i : line)
        if (delimiters.find(i) != std::string::npos)
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

int string_to_int(const std::string& str) 
{
    try 
    {
        return std::stoi(str);
    } 
    catch (const std::invalid_argument& ia) 
    {
        return -1;
    }
}