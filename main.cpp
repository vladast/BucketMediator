#include <stdlib.h>
#include <iostream>
#include <getopt.h>

/**
 * @brief Prints help menu
 */
void print_help();

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
            print_help();
            exit(EXIT_FAILURE);
        }
    }

    std::cout << "Port number: " << portNumber << std::endl;

    return EXIT_SUCCESS;
}

void print_help()
{
    std::string help = "bucketmediator version 0.1 Copyright (c) 2018 Vladimir Stankovic\n"
                       "usage: bucketmediator [options]\n"
                       "Options:\n"
                       "-h              show help\n"
                       "-p <value>      set port number\n";
    std::cout << help << std::endl;
}
