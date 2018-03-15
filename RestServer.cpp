#include <RestServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <RestRequestParams.h>
#include <RestRequestProcessor.h>
#include <sstream>
#include <vector>
#include <pthread.h>
#include <fcntl.h>
#include <memory>

void* task(void* fd)
{
    int clientSocket = *((int*)fd);
    std::cout << "Processing: " << clientSocket << std::endl;
    char buffer[1024];
    int requestHeader = read(clientSocket, buffer, 1024 - 1);
    std::cout << "Read: " << requestHeader << std::endl;

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

RestServer::RestServer(int port, int numberOfPendingConnections) : socketFileDescriptor(-1)
{
    this->port = port;
    this->numberOfPendingConnections = numberOfPendingConnections;
    if (InitServer())
    {
        int opt = 1;
        // Set master socket for multiple connections
        setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

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
        /*
        else
        {
            fcntl(socketFileDescriptor, F_SETFL, O_NONBLOCK);
        }
        */
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

        int threadCount = 0;
        std::vector<pthread_t> workers;
        running = true;
        std::cout << "Server socket: " << socketFileDescriptor << std::endl;

        struct sockaddr_storage socketStorage;
        socklen_t socketStorageSize = sizeof socketStorage;

        while (running)
        {
            int clientSocket = accept(socketFileDescriptor,
                                      (struct sockaddr*)&socketStorage,
                                      &socketStorageSize);

            std::cout << "Accepted connection: " << clientSocket << std::endl;

            pthread_t* worker = new pthread_t;

            if (pthread_create(worker, NULL, &task, (void*)&clientSocket) != 0)
            {
                std::cout << "Haven't been able to create thread!" << std::endl;
            }
            else
            {
                workers.push_back(*worker);
                if (++threadCount > 20 ) // Max of 20 threads allowed
                {
                    std::cout << "Breaking out..." << std::endl;
                    break;
                }
            }
        }

        std::cout << "Workers count: " << workers.size() << std::endl;
        for (auto& worker : workers)
        {
            pthread_join(worker, nullptr);
            std::cout << "Joined" << std::endl;
        }

        std::cout << "Closing server's socket" << std::endl;
        close(socketFileDescriptor);
    }
}
