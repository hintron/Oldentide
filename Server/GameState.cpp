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
#include <cstring>
#include <map>

#define MAX_MESSAGES 500
#define MAX_MESSAGE_LENGTH 500


GameState::GameState(SQLConnector * input) {
    sql = input;
    curSession = 1;
}

GameState::~GameState() {
    return;
}

// Checks if the session id given by the user is valid before allowing further interaction.
bool GameState::VerifySession(int sessionId) {
    if (sessions.find(sessionId) != sessions.end()) {
        return true;
    }
    else {
        return false;
    }
}

// Active sessions refer to users that have already authenticated and may or may not be already using a character.
bool GameState::VerifyActiveSession(int sessionId) {
    if (activeSessions.find(sessionId) != activeSessions.end()) {
        return true;
    }
    else {
        return false;
    }
}

void GameState::DisconnectSession(int sessionId) {
    activeSessions.erase(sessionId);
    sessions.erase(sessionId);
    return;
}

void GameState::PlayerCommand(char * command, int sessionId) {
    std::string pCommand(command);
    std::vector<std::string> pCommandTokens = utils::Tokenfy(pCommand, ' ');
    if (pCommandTokens[0] == "/s") {
        std::cout << "Detected a say command!" << std::endl;
        // Save the incoming message and return the assigned message number
        std::string saying = pCommand.substr(3,std::string::npos);
    }
    else if (pCommandTokens[0] == "/y") {
        std::cout << "Detected a yell command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/ooc") {
        std::cout << "Detected an out of character command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/h") {
        std::cout << "Detected a help channel command!" << std::endl;
    }
    else if (pCommandTokens[0] == "/w") {
        std::cout << "Detected a whisper command!" << std::endl;
    }
    std::cout << "Full player command: " << command << std::endl;
}

void GameState::SelectPlayer(int sessionId) {
    if (sessions.find(sessionId) != sessions.end()) {
        activeSessions.insert(sessionId);
    }
    return;
}

//Player GameState::ReadPlayer(std::string name) {
//    return void;
//}

void GameState::StorePlayer(std::string name) {
    return;
}

int GameState::GenerateSession(int sessionId) {
    if (sessions.find(sessionId) != sessions.end()) {
        return sessionId;
    }
    else {
        sessions.insert(curSession);
        curSession++;
        return (curSession - 1);
    }
}

void GameState::SetSessionAccountName(char *accountName, int sessionId) {
    std::string accountNameString = accountName;
    sessionAccounts[sessionId] = accountNameString;
}

std::string GameState::GetSessionAccountName(int sessionId) {
    return sessionAccounts[sessionId];
}

std::set<Player> GameState::getPlayers() {
    return players;
}
