// Filename:    GameState.h
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Game State Class implementation.
//              This class will be responsible for maintaining the Players, 
//              NPCs necessary to preserve the game state.  It will also 
//              perform the bulk of database interactions.

#include "GameState.h"

using namespace std;

GameState::GameState(SQLConnector * input){
    sql = input;
}

GameState::~GameState(){
    return;
}

bool GameState::verifySession(int session){
    return true;
}

Player GameState::loadPlayer(string name){
    return Player("example", 0, 0, "Poop", "Stain", "Human", "Male", "Shaman", 0, 0, 0, 0, 0.0);   
}

void GameState::storePlayer(string name){
    return;   
}
