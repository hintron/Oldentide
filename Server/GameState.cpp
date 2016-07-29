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
#include "AccountManager.h"

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

bool GameState::createAccount(PACKET_CREATEACCOUNT *packet){
    cout << "  Creating Account..." << endl;
    cout << "  Account: " << packet->account << endl;
    cout << "  Key: " << packet->keyStringHex << endl;
    cout << "  Salt: " << packet->saltStringHex << endl;
    bool success = false;
    if(sql->insert_account(packet->account, packet->keyStringHex, packet->saltStringHex, 1 << 20)){
        success = true;
    }
    else {
        printf("Unable to insert new account record into database...\n");
    }
    printf("Listing all created accounts...\n");
    sql->list_accounts();
    // TODO: Overwrite stack sensitive variables with with 0's,
    // since it doesn't get zeroed out once it's off the stack
    //for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
    //    generated_key[i] = 0;
    //}
    //for(int i = strlen(); i > 0); --i){
    //    password[i] = 0;
    //}
    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can
    return success;
}

bool GameState::loginUser(PACKET_LOGIN * packet){
    cout << "  Logging in..." << endl;
    cout << "  Account: " << packet->account << endl;
    cout << "  Key: " << packet->keyStringHex << endl;
    return AccountManager::authenticate_account(packet->account, packet->keyStringHex);
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
