// Filename:    UnitTest.cpp
// Author:      Joseph DeVictoria
// Date:        September_24_2016
// Purpose:     A non-exhaustive unit testing platform to quickly enable functions.

#include "AdminShell.h"
#include "GameState.h"
#include "LoginManager.h"
#include "Npc.h"
#include "Packets.h"
#include "Player.h"
#include "Server.h"
#include "SQLConnector.h"
#include "Utils.h"
#include <iostream>
#include <string>

int main() {
    SQLConnector* sql = new SQLConnector();
    std::cout << "Welcome to the Oldentide Unit Tester." << std::endl;
    std::cout << "Tests are added as needed! You will not see every function here." << std::endl;
    std::cout << "Please select a function to check from the list below:" <<std::endl;
    std::cout << "1. SQLConnector::InsertPlayer" << std::endl;
    bool running = true;
    while(running) {
        std::string test;
        getline(std::cin, test);
        switch(atoi(test.c_str())) {
            case 1:
                sockaddr_in dummyClient;
                Player p(dummyClient, "example", "Shaman", 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Poop", "Stain", "Dorks", 
                         "Human", "Male", "Scarred", "Pale", "Newcomers_Guild", 0, 0, 0, 0, 0, 0, 
                         0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0);
                if (sql->InsertPlayer(p)) {
                    std::cout << "Great Success!" << std::endl;
                }
                else {
                    std::cout << "Huge Mistake..." << std::endl;
                }
        }
    }
}
