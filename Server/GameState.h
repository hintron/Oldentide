// Filename:    GameState.h
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Header for Game State class.
//              This class will be responsible for maintaining the Players,
//              NPCs necessary to preserve the game state.  It will also
//              perform the bulk of database interactions.

#ifndef OLDENTIDE_GAMESTATE_H
#define OLDENTIDE_GAMESTATE_H

#include "Npc.h"
#include "Player.h"
#include "SQLConnector.h"
#include <set>
#include <string>
#include <vector>
#include <map>

class GameState{
    public:
        GameState(SQLConnector * sql);
        ~GameState();
        bool VerifySession(int sessionId);
        bool VerifyActiveSession(int sessionId);
        bool CreateAccount(char * account, char * keyStringHex, char * saltStringHex);
        bool LoginUser(char * account, char * keyStringHex);
        void DisconnectSession(int sessionId);
        void PlayerCommand(char * command, int);
        void SelectPlayer(int sessionId);
        int GenerateSession(int sessionId);
        long long int GetGlobalMessageNumber();
        long long int GetMessage(long long int, char *, char *);
        long long int StoreMessage(std::string, int);
        void SetSessionAccountName(char *, int);

    private:
        SQLConnector * sql;
        std::set<Player> players;
        std::set<Npc> npcs;
        std::set<int> sessions;
        std::set<int> activeSessions;
        // TODO: Make this players instead of accounts?
        std::map<int, std::string> sessionAccounts;
        int curSession;
        // The index of the array will be the global message number
        long long int globalMessageNumber;
        // Create a global array of char pointers for the messages
        // Malloc space for each new message
        std::vector<std::string> globalMessageArray;
        std::vector<int> globalMessageAccountArray;
        Player ReadPlayer(std::string name);
        void StorePlayer(std::string name);
};

#endif // OLDENTIDE_GAMESTATE_H
