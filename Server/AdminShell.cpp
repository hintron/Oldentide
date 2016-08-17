// Filename:    AdminShell.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_6_2016
// Purpose:     Provide an interface for the administrator to interact with
//              the server.  This class will handle all server admin commands.

#include "AdminShell.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <string>

AdminShell::AdminShell(SQLConnector * input){
    sql = input;
    gethostname(serverHostname, HOST_NAME_MAX);
}

AdminShell::~AdminShell(){
    return;
}

void AdminShell::operator()(){
    run();
}

void AdminShell::run(){
    std::string adminCommand; 
    std::cout << "Starting Server Administrator Shell.\n";
    printLogo();
    while(true){
	    do
	    {
            std::cout << "OldentideAdmin@" << serverHostname << ": ";
            getline(std::cin,adminCommand);
	    }while(adminCommand.empty());
        std::vector<std::string> adminTokens = Utils::tokenfy(adminCommand, ' ');
        if (adminTokens[0] == "/shutdown"){
            std::cout << "Oldentide Dedicated Server is shutting down..." << std::endl;
            exit(EXIT_SUCCESS);
            return;
        }
        else if (adminTokens[0] == "/list"){
            if (adminTokens.size() == 2){
                std::cout << adminTokens[1];
                if (adminTokens[1] == "players"){
                    std::cout << "PCSSSSSS" << std::endl;          
                }
                if (adminTokens[1] == "npcs"){
                    std::cout << "NPCSSSSS" << std::endl;    
                }
            }
            else{
                printUsage();
            }
        }
        else if (adminTokens[0] == "/db"){
            std::string cmd = adminCommand.erase(0,4);
            sql->execute(cmd);
        }
        else{
            printUsage();
        }
    }
}

void AdminShell::printUsage(){
    std::cout << "Dedicated Server Admin Usage:" << std::endl;
    std::cout << "/shutdown    = Shuts down the server." << std::endl;
    std::cout << "/list <var>  = Lists all entities of given <var> on server, where <var> is [players, npcs]." << std::endl;
    std::cout << "/db <query>  = Runs a given sql query on the sqlite3 database." << std::endl;
}

void AdminShell::printLogo(){
    std::cout << "  ____           ___   _____         _____  _____  ___   _____" << std::endl;
    std::cout << " /    \\  |      |   \\  |      |   |    |      |    |  \\  |" << std::endl;
    std::cout << "/      \\ |      |    \\ |      |\\  |    |      |    |   \\ |" << std::endl;
    std::cout << "|      | |      |    | |___   | \\ |    |      |    |   | |___" << std::endl;
    std::cout << "\\      / |      |   /  |      |  \\|    |      |    |   / |" << std::endl;
    std::cout << " \\____/  |_____ |__/   |____  |   \\    |    __|__  |__/  |____" << std::endl;
    std::cout << " " << std::endl; 
    std::cout << "                              |" << std::endl;
    std::cout << "                             / \\" << std::endl;
    std::cout << "                            /\\_/\\" << std::endl;
    std::cout << "                           / | | \\" << std::endl;
    std::cout << "                           \\ |_| /" << std::endl;
    std::cout << "                            \\/ \\/" << std::endl;
    std::cout << "                             \\ /" << std::endl;
    std::cout << "                              |" << std::endl;
    std::cout << " " << std::endl;
}
