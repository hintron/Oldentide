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
        void SetSessionAccountName(char * accountName, int sessionId);
        std::string GetSessionAccountName(int sessionId);
        std::set<Player> getPlayers();

    private:
        SQLConnector * sql;
        std::set<Player> players;
        std::set<Npc> npcs;
        std::set<int> sessions;
        std::set<int> activeSessions;
        std::map<int, std::string> sessionAccounts;
        int curSession;
        //Player ReadPlayer(std::string name);
        void StorePlayer(std::string name);
};

#endif // OLDENTIDE_GAMESTATE_H
