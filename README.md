# In the Name of God

*Mohammad Mohajel Sadegi*

# Socket Programming

Socket programming is a method of communication between two computers using a network protocol, typically TCP/IP. It allows for the exchange of data between client and server applications running on separate machines.

# Description

In this project we are creating a simple client-server application using socket programming in C++.

we get requests from clients and send them to other clients.

We use *select* to handle multiple clients and multipul inputs from diffrent file descriptors without blocking both in our server and client.

# How to Run
Use make to compile the project in client and server directories. 
Then run server and client in two diffrent terminals.

```bash 
./bin/server
```
```bash
./bach/client <client_id>
```
# How Selecet Works

select() allows a program to monitor multiple file descriptors,
       waiting until one or more of the file descriptors become "ready"
       for some class of I/O operation (e.g., input possible).  A file
       descriptor is considered ready if it is possible to perform a
       corresponding I/O operation (e.g., read(2), or a sufficiently
       small write(2)) without blocking.

   File descriptor sets
       The principal arguments of select() are three "sets" of file
       descriptors (declared with the type fd_set), which allow the
       caller to wait for three classes of events on the specified set
       of file descriptors.  Each of the fd_set arguments may be
       specified as NULL if no file descriptors are to be watched for
       the corresponding class of events.

       Note well: Upon return, each of the file descriptor sets is
       modified in place to indicate which file descriptors are
       currently "ready".  Thus, if using select() within a loop, the
       sets must be reinitialized before each call.

       The contents of a file descriptor set can be manipulated using
       the following macros:

       FD_ZERO()
              This macro clears (removes all file descriptors from) set.
              It should be employed as the first step in initializing a
              file descriptor set.

       FD_SET()
              This macro adds the file descriptor fd to set.  Adding a
              file descriptor that is already present in the set is a
              no-op, and does not produce an error.

       FD_CLR()
              This macro removes the file descriptor fd from set.
              Removing a file descriptor that is not present in the set
              is a no-op, and does not produce an error.

       FD_ISSET()
              select() modifies the contents of the sets according to
              the rules described below.  After calling select(), the
              FD_ISSET() macro can be used to test if a file descriptor
              is still present in a set.  FD_ISSET() returns nonzero if
              the file descriptor fd is present in set, and zero if it
              is not.
# Classes
## Client
It consists of these classes

Our main class is class client that we instantiate in main function it takes client id as an argument
```c++
// main.cpp
int main(int argc, char const *argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: ./client <client_id>\n");
        exit(EXIT_FAILURE);
    }
    Client client(atoi(argv[1]));
    client.start(PORT, SERVER_IP);

    return 0;
}
```

It contains these methods
```c++
public:
    void start(int port, const char *server_ip);
private:
    void connect_to_server(int port, const char *ip);
    void set_fd_set();
    void send_initial_request(int client_id);
    void send_requests();
```
*start* method basically calls other 4 and after setting fd and connecting to server, it goes throw a while loop in last method and uses select to handle input both from input buffer and client socket simultanuously.

```c++
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);

        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            {    
                if (i == server_fd) // server sending msg
                {  
                    char command[MAX_STRING_SIZE] = {0};
                    if (recv(i , command, MAX_STRING_SIZE, 0) == 0) 
                    { // EOF
                        // connction closed ....
                        continue;
                    }
                    // respond to server ...
                }

                else if (i == STD_IN) //input buffer
                {
                    // ...
                }
            }
        }
    }
```

#================================================================================
## Server

```c++
// main.cpp
int main(int argc, char const *argv[]) 
{
    Server server;
    server.start();
    return 0;
}
```

It contains these methods
```c++
public:
    void start();
private:
    void set_fd_set();
    void run_server();
    void close_client(int client_fd);
    void handle_clients_request(int client_fd);
    void add_new_client(int client_fd);
    int setup_server(int port); 
    int accept_client(int server_fd);
    void add_client_id(int id, int client_fd);
    void send_msg_to_client(int receiver_id, int msg, int sender_id, int sender_fd)
```
# Tests
Here, I provide some tests to show how our program works.
I handled all the edge cases and errors possible in this senario.

## Test 1 : 
Requesting a *client_fd* that has already been assigened to other client.
![My Image](./test-pictures/1.png)

## Test 2 :
Requesting a second *client_fd* 
![My Image](./test-pictures/2.png)

## Test 3 :
Invalid command and number format
![My Image](./test-pictures/3.png)

## Test 4 :
Sending a message to a client that is not connected
![My Image](./test-pictures/4.png)

## Test 5 :
Sending a message to yourself
![My Image](./test-pictures/5.png)

## Test 6 :
Sending a message to a client that is connected
![My Image](./test-pictures/6.png)

## Test 7 :
Sending a message to a client that is connected but with wrong id
![My Image](./test-pictures/7.png)

## Test 8 :
Client disconnecting
![My Image](./test-pictures/8.png)

## Test 9 :
Server disconnecting
![My Image](./test-pictures/9.png)

## Test 10 :
Server log file
![My Image](./test-pictures/10.png)

## Test 11 :
Clients log file
![My Image](./test-pictures/11.png)
![My Image](./test-pictures/12.png)

