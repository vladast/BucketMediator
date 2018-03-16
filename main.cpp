#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <unistd.h> // sleep
#include <AwsS3Helper.h>
#include <FileHelper.h>
#include <FileInfo.h>
#include <AudioInfoSerializer.h>
#include <FileSizeInfoSerializer.h>
#include <RestServer.h>

/**
 * @brief Prints help menu
 */
void PrintHelp();

/**
 * @brief Checks whether config file is present
 * @return true if present, oterwise false
 */
bool IsConfigFileCreated();

/**
 * @brief Main entry-point
 * @return Program execution status code
 */
int main(int argc, char **argv)
{
    int commandLineOption = 0;
    uint portNumber = 8089;
    while ((commandLineOption = getopt(argc, argv, "hp:")) != -1)
    {
        switch (commandLineOption) {
        case 'p':
            portNumber = atoi(optarg);
            break;
        case 'h':
        default:
            PrintHelp();
            exit(EXIT_FAILURE);
        }
    }

    RestServer restServer(portNumber, 5);
    typedef void * (*RUNPTR)(void*);
    pthread_t worker;
    if (pthread_create(&worker, nullptr, (RUNPTR) &RestServer::Run, &restServer) != 0)
    {
        std::cout << "Haven't been able to create thread!" << std::endl;
    }
    else
    {
        // Additional processing here.
        // restServer.Stop();
    }
    pthread_join(worker, nullptr);

    return EXIT_SUCCESS;
}

void PrintHelp()
{
    std::string help = "bucketmediator version 0.1 Copyright (c) 2018 Vladimir Stankovic\n"
                       "usage: bucketmediator [options]\n"
                       "Options:\n"
                       "-h              show help\n"
                       "-p <value>      set port number\n";
    std::cout << help << std::endl;
}
