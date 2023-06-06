#include "logger.hpp"
#include "manual.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Logger::Logger(string log_file_name, bool )
// 	:
// 	log_file_name(log_file_name)
// {
// }

// void Logger::log(string type, string command)
// {
// 	ofstream log_file;
// 	log_file.open(this->log_file_name, ios::app);
// 	time_t date = time(0);
// 	char* dt = ctime(&date);
// 	dt[strlen(dt) - 1] = '\0';
// 	log_file << '[' << dt << "] " << type << ": " << command << endl;
// 	log_file.close();
// }