#include "logger.hpp"
#include "manual.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

Logger::Logger(string filename) 
{
    ifstream file(filename);
    if (!file.good())
    {
        ofstream new_file(filename);
        new_file.close();
    }
    file_.open(filename, ios::out | ios::app);
}

Logger::~Logger() 
{
    file_.close();
}

string Logger::get_time_stamp()
{
    time_t now = time(nullptr);
    string timestamp = asctime(localtime(&now));
    timestamp = timestamp.substr(0, timestamp.size() - 1);
    return timestamp;
}

void Logger::log(string message, string colour) 
{
    if (message == "")
        return;
    string data = "[" + this->get_time_stamp() + "] " + message;
    file_ << data << endl;
    cout << colour << data << KWHT << endl;
}