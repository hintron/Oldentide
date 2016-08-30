// Filename:    Main.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Contains the main method for the Oldentide dedicated server.

#include "Server.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    // TODO: Parameter checking
    // Have parameter checking and exit gracefully if server address and port aren't specified
    if (argc != 2) {
        std::cout << "Invalid number of arguments passed to " << argv[0] << "; Exiting..." << std::endl;
        return 1;
    }
    int port = atoi(argv[1]);
    Server * server = new Server(port);
    server->Run();
    delete server;
    return 0;
}
