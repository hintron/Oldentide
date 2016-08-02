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

// Checks if the session id given by the user is valid before allowing further interaction.
bool GameState::verifySession(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        return true;
    }
    else{
        return false;
    }
}

// Active sessions refer to users that have already authenticated and may or may not be already using a character.
bool GameState::verifyActiveSession(int sessionId){
    if (activeSessions.find(sessionId) != activeSessions.end()){
        return true;
    }
    else{
        return false;
    }
}

bool GameState::createAccount(char * account, char * keyStringHex, char * saltStringHex){
    cout << "  Creating Account..." << endl;
    cout << "  Account: " << account << endl;
    cout << "  Key: " << keyStringHex << endl;
    cout << "  Salt: " << saltStringHex << endl;
    bool success = false;
    // TODO: Remove iterations from insert_account and sql schema
    if(sql->insert_account(account, keyStringHex, saltStringHex, 1 << 20)){
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

bool GameState::loginUser(char * account, char * keyStringHex){
    cout << "  Logging in..." << endl;
    cout << "  Account: " << account << endl;
    cout << "  Key: " << keyStringHex << endl;
    return AccountManager::authenticate_account(account, keyStringHex);
}

void GameState::disconnectSession(int sessionId){
    activeSessions.erase(sessionId);
    sessions.erase(sessionId);
    return;
}

void GameState::playerCommand(char * command){
    string pCommand(command);
    vector<string> pCommandTokens = tokenfy(pCommand, ' ');
    if (pCommandTokens[0] == "/s"){
        cout << "Detected a say command!" << endl;
    }
    else if (pCommandTokens[0] == "/y"){
        cout << "Detected a yell command!" << endl;
    }
    else if (pCommandTokens[0] == "/ooc"){
        cout << "Detected an out of character command!" << endl;
    }
    else if (pCommandTokens[0] == "/h"){
        cout << "Detected a help channel command!" << endl;
    }
    else if (pCommandTokens[0] == "/w"){
        cout << "Detected a whisper command!" << endl;
    }
    cout << "Full player command: " << command << endl;
}

void GameState::selectPlayer(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        activeSessions.insert(sessionId);
    }
    return;
}

Player GameState::readPlayer(string name){
    return Player("example", 0, 0, "Poop", "Stain", "Human", "Male", "Shaman", 0, 0, 0, 0, 0.0, "Newcomers_Guild");   
}

void GameState::storePlayer(string name){
    return;   
}

int GameState::generateSession(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        return sessionId;
    }
    else{
        sessions.insert(curSession);
        curSession++;
        return (curSession - 1);
    }
}
