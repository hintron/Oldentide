// Filename:    GameState.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Game State Class implementation.
//              This class will be responsible for maintaining the Players, 
//              NPCs necessary to preserve the game state.  It will also 
//              perform the bulk of database interactions.

#include "GameState.h"
#include <iterator>

using namespace std;

GameState::GameState(SQLConnector * input){
    sql = input;
    curSession = 0;
}

GameState::~GameState(){
    return;
}

bool GameState::verifySession(PACKET_GENERIC * packet){
    if (sessions.find(packet->sessionId) != sessions.end()){
        return true;
    }
    else if (packet->packetType == GENERIC || packet->packetType == CONNECT){
        return true;
    }
    else{
        return false;
    }
}

Player GameState::loadPlayer(string name){
    return Player("example", 0, 0, "Poop", "Stain", "Human", "Male", "Shaman", 0, 0, 0, 0, 0.0, "Newcomers_Guild");   
}

void GameState::storePlayer(string name){
    return;   
}

int GameState::generateSession(){
    sessions.insert(curSession);
    curSession++;
    return (curSession - 1);
}

bool GameState::playerSessionLookup(int session){
    set<Player>::iterator it;
    for (it = players.begin(); it != players.end(); ++it){
        Player temp(*it);
        if (temp.getSession() == session){
            return true;
        }
    }
    return false;
}
