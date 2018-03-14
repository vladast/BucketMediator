#ifndef __REST_SERVER_H__
#define __REST_SERVER_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> // needed for bzero

class RestServer
{
    int port;
    int numberOfPendingConnections;
    int socketFileDescriptor;
    struct sockaddr_in socketAddress;
    bool running;
public:
    RestServer(int port, int numberOfPendingConnections = 10);
    int GetPort() const { return port; }
    void SetPort(int port) { this->port = port; }
    int GetNumberOfPendingConnections() const { return numberOfPendingConnections; }
    void SetNumberOfPendingConnections(int number) { numberOfPendingConnections = number; }
public:
    bool InitServer();
    bool IsValid() const;
    void Run();
};

#endif // __REST_SERVER_H__
