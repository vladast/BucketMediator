#include <RestServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <RestRequestParams.h>
#include <RestRequestProcessor.h>
#include <sstream>
#include <vector>

RestServer::RestServer(int port, int numberOfPendingConnections) : socketFileDescriptor(-1)
{
    this->port = port;
    this->numberOfPendingConnections = numberOfPendingConnections;
    if (InitServer())
    {
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_port = htons(port);
        socketAddress.sin_addr.s_addr = INADDR_ANY;
        bzero(&(socketAddress.sin_zero), 8);

        if (bind(socketFileDescriptor,
                 (struct sockaddr*)&socketAddress,
                 sizeof(struct sockaddr)) == -1)
        {
            socketFileDescriptor = -1; // Indicates an error
        }
    }
    running = false;
}

bool RestServer::InitServer()
{
    return (socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) != 1;
}

bool RestServer::IsValid() const
{
    return socketFileDescriptor == -1;
}

void RestServer::Run()
{
    if (listen(socketFileDescriptor, numberOfPendingConnections) == -1)
    {
        socketFileDescriptor = -1;
    }
    else
    {
        running = true;
        while (running)
        {
            struct sockaddr_storage socketStorage;
            socklen_t socketStorageSize = sizeof socketStorage;
            int clientSocket = accept(socketFileDescriptor,
                                      (struct sockaddr*)&socketStorage,
                                      &socketStorageSize);
            char buffer[1024];
            int requestHeader = read(clientSocket, buffer, 1024 - 1);

            buffer[requestHeader] = '\0';
            std::stringstream ss(buffer);
            HttpRequest httpRequest(ss);
            std::cout << "Method: " << httpRequest.GetMethod() << std::endl;
            std::cout << "URI: " << httpRequest.GetRequestUri() << std::endl;

            RestRequestParams restParams(httpRequest.GetRequestUri());

            RestRequestProcessor restRequestProcessor;
            HttpResponse httpResponse = restRequestProcessor(restParams);

            std::string response = httpResponse.ToString();
            write(clientSocket, response.c_str(), response.size());

            close(clientSocket);
        }
        close(socketFileDescriptor);
    }
}
