// in the name of God

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "manual.hpp"
#include "server.hpp"

using namespace std;

map<int,string> Info::status =  Info::create_map();


int main(int argc, char const *argv[]) 
{
    Server server;
    server.start();
    return 0;
}
