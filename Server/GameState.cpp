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
#include <cstring>
#include <map>

#define MAX_MESSAGES 500
#define MAX_MESSAGE_LENGTH 500


GameState::GameState(SQLConnector * input){
    sql = input;
    curSession = 1;

    // 0 means no messages. The first message will be 1.
    globalMessageNumber = 0;

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
    std::cout << "  Creating Account..." << std::endl;
    std::cout << "  Account: " << account << std::endl;
    std::cout << "  Key: " << keyStringHex << std::endl;
    std::cout << "  Salt: " << saltStringHex << std::endl;
    bool success = false;
    if(sql->insert_account(account, keyStringHex, saltStringHex)){
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
    std::cout << "  Logging in..." << std::endl;
    std::cout << "  Account: " << account << std::endl;
    std::cout << "  Key: " << keyStringHex << std::endl;
    return AccountManager::authenticateAccount(account, keyStringHex);
}

void GameState::disconnectSession(int sessionId){
    activeSessions.erase(sessionId);
    sessions.erase(sessionId);
    return;
}

void GameState::playerCommand(char * command, int sessionId){
    std::string pCommand(command);
    std::vector<std::string> pCommandTokens = Utils::tokenfy(pCommand, ' ');
    if (pCommandTokens[0] == "/s"){
        std::cout << "Detected a say command!" << std::endl;
        // Save the incoming message and return the assigned message number
        std::string saying = pCommand.substr(3,std::string::npos);
        storeMessage(saying, sessionId);
    }
    else if (pCommandTokens[0] == "/y"){
        std::cout << "Detected a yell command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/ooc"){
        std::cout << "Detected an out of character command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/h"){
        std::cout << "Detected a help channel command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/w"){
        std::cout << "Detected a whisper command!" << std::endl;
    }
    std::cout << "Full player command: " << command << std::endl;
}

void GameState::selectPlayer(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        activeSessions.insert(sessionId);
    }
    return;
}

Player GameState::readPlayer(std::string name){
    return Player("example", "Shaman", 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, "Poop", "Stain", "Human", "Male", "Scarred", "Pale", 
                  "Newcomers_Guild", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 
                  0.0);
}

void GameState::storePlayer(std::string name){
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


/**
    @return : The number of the most recent message received by the server
**/
long long int GameState::getGlobalMessageNumber() {
    if(globalMessageNumber > MAX_MESSAGES){
        // 0 means either no messages or
        // Ran out of message space
        return 0;
    }
    else {
        // Return the latest message number in the global message buffer
        return globalMessageNumber;
    }
}

/**
    Returns a message and the account that spoke it

    // TODO: Change this to be player-based
    // TODO: Broadcast all messages in realtime instead of storing them

    @param messageNumber : IN. The message number of the message to get
    @param message : OUT. The message to output

    @return : 0 if failed to retrieve message, else the message number of the returned message
**/
long long int GameState::getMessage(long long int messageNumber, char *messageOutput, char *accountNameOutput) {
    // Look up the requested message and return it
    if(messageNumber >= 1 && messageNumber <= MAX_MESSAGES){
        std::cout << "Looking up message " << messageNumber << std::endl;

        // Look up the message and account name
        // Remember, index = messageNumber - 1
        std::string message = globalMessageArray.at(messageNumber-1);
        std::string accountName = sessionAccounts[globalMessageAccountArray.at(messageNumber-1)];
        // std::cout << accountName << ": " << message << std::endl;

        std::strcpy(messageOutput, message.c_str());
        std::strcpy(accountNameOutput, accountName.c_str());
        return messageNumber;
    }
    else {
        // Invalid message
        return 0;
    }
}


/**
    @param message : The message to store
    @param accountName : The name of the account that spoke

    // TODO: Change to players instead of accounts

    @return : the global message number assigned to the message stored.
                If 0, then failed to store message.
**/
long long int GameState::storeMessage(std::string message, int sessionId) {
    if(globalMessageNumber > MAX_MESSAGES){
        std::cout << "Ran out of message space! Reached max number of messages" << std::endl;
        // Ran out of message space
        return 0;
    } else{
        // Increase the global message number (start at 1 - 0 means no messages)
        globalMessageNumber++;
        // std::cout << "Saving message with number " << globalMessageNumber << ": " << message << std::endl;
        // TODO: Are things guaranteed to be atomic and reentrant?
        // Atomically assign message a global message number
        // Store the first message at index 0, second message at 1, etc.
        globalMessageArray.push_back(message);
        // Store the username of the account that sent the message
        globalMessageAccountArray.push_back(sessionId);
        return globalMessageNumber;
    }
}


// TODO: Make this player name instead of account name
void GameState::setSessionAccountName(char *accountName, int sessionId){
    std::string accountNameString = accountName;
    sessionAccounts[sessionId] = accountNameString;
    // TODO: Return something if session account was already registered
}
