// Filename:    GameState.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Game State Class implementation.
//              This class will be responsible for maintaining the Players, 
//              NPCs necessary to preserve the game state.  It will also 
//              perform the bulk of database interactions.

#include "GameState.h"
#include "Utils.h"
#include <iterator>
#include <iostream>

using namespace std;

GameState::GameState(SQLConnector * input){
    sql = input;
    curSession = 1;
}

GameState::~GameState(){
    return;
}

bool GameState::verifySession(PACKET_GENERIC * packet){
    if (sessions.find(packet->sessionId) != sessions.end()){
        return true;
    }
    else if ( packet->packetType == CONNECT){
        return true;
    }
    else{
        return false;
    }
}

bool GameState::verifyActiveSession(int sessionId){
    if (activeSessions.find(sessionId) != activeSessions.end()){
        return true;
    }
    else{
        return false;
    }
}

bool GameState::loginUser(PACKET_LOGIN * packet){
    cout << "Account: " << packet->account << endl;
    cout << "Password: " << packet->password << endl;
    return true;
}

void GameState::disconnectSession(PACKET_DISCONNECT * packet){
    activeSessions.erase(packet->sessionId);
    sessions.erase(packet->sessionId);
    return;
}

void GameState::playerCommand(PACKET_SENDPLAYERCOMMAND * packet){
    cout << packet->command << endl;
    string pCommand(packet->command);
    vector<string> pCommandTokens = tokenfy(pCommand, ' ');
    if (pCommandTokens[0] == "/s"){
        cout << "poop" << endl;
    }
    else if (pCommandTokens[0] == "/h"){
        cout << "pee" << endl;
    }
}

void GameState::selectPlayer(PACKET_SELECTCHARACTER * packet){
    if (sessions.find(packet->sessionId) != sessions.end()){
        activeSessions.insert(packet->sessionId);
    }
    return;
}

Player GameState::readPlayer(string name){
    return Player("example", 0, 0, "Poop", "Stain", "Human", "Male", "Shaman", 0, 0, 0, 0, 0.0, "Newcomers_Guild");   
}

void GameState::storePlayer(string name){
    return;   
}

int GameState::generateSession(PACKET_CONNECT * packet){
    if (sessions.find(packet->sessionId) != sessions.end()){
        return packet->sessionId;
    }
    else{
        sessions.insert(curSession);
        curSession++;
        return (curSession - 1);
    }
}
