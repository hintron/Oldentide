// Filename:    UnitTest.cpp
// Author:      Joseph DeVictoria
// Date:        September_24_2016
// Purpose:     A non-exhaustive unit testing platform to quickly enable functions.

// Load the testing framework (do it ABOVE the catch include!)
#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include "AdminShell.h"
#include "GameState.h"
#include "Npc.h"
#include "Packets.h"
#include "Player.h"
#include "Server.h"
#include "SQLConnector.h"
#include "Utils.h"


TEST_CASE( "Insert Player", "[insert]" ) {
    SQLConnector* sql = new SQLConnector();
    sockaddr_in dummyClient;
    Player p(dummyClient, "example", "Shaman", 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Poop", "Stain", "Newcomers_Guild",
             "Human", "Male", "Scarred", "Pale", 0, 0, 0, 0, 0, 0,
             0, 0, 0, 0, 0, 0, 0, "heady", "chest", "army", "handy", "leggy", "footy", "elven cloak", "necklace", "ring1", "ring2", "lrighthand", "lefthand", "zone", 0.0, 0.0, 0.0, 0.0, 0.0);

    REQUIRE( sql->InsertPlayer(p) == true );
    delete sql;
}





TEST_CASE( "Insert Account", "[insert]" ) {
    SQLConnector* sql = new SQLConnector();
    REQUIRE( sql->InsertAccount("my_account", "my_key", "my_salt") == true );
    delete sql;
}



// int main() {
//     SQLConnector* sql = new SQLConnector();
//     std::cout << "Welcome to the Oldentide Unit Tester." << std::endl;
//     std::cout << "Tests are added as needed! You will not see every function here." << std::endl;
//     std::cout << "Please select a function to check from the list below:" <<std::endl;
//     std::cout << "1. SQLConnector::InsertPlayer" << std::endl;
//     bool running = true;
//     while(running) {
//         std::string test;
//         getline(std::cin, test);
//         switch(atoi(test.c_str())) {
//             case 1:
//                 sockaddr_in dummyClient;
//                 Player p(dummyClient, "example", "Shaman", 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Poop", "Stain", "Newcomers_Guild",
//                          "Human", "Male", "Scarred", "Pale", 0, 0, 0, 0, 0, 0,
//                          0, 0, 0, 0, 0, 0, 0, "heady", "chest", "army", "handy", "leggy", "footy", "elven cloak", "necklace", "ring1", "ring2", "lrighthand", "lefthand", "zone", 0.0, 0.0, 0.0, 0.0, 0.0);
//                 if (sql->InsertPlayer(p)) {
//                     std::cout << "Great Success!" << std::endl;
//                 }
//                 else {
//                     std::cout << "Huge Mistake..." << std::endl;
//                 }
//         }
//     }
// }
