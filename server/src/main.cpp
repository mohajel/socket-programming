// in the name of God

#include "manual.hpp"
#include "server.hpp"

using namespace std;

map<int,string> Info::status =  Info::create_map();

int main(int argc, char const *argv[]) 
{
    Server server;
    server.start_and_run_server();
    return 0;
}
