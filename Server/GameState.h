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
#include "GameObject.h"
#include "Player.h"
#include "SQLConnector.h"
#include <set>
#include <string>

class GameState{
    public:
        GameState(SQLConnector * sql);
        ~GameState();
        bool verifySession(int sessionId);
        bool verifyActiveSession(int sessionId);
        bool createAccount(char * account, char * keyStringHex, char * saltStringHex);
        bool loginUser(char * account, char * keyStringHex);
        void disconnectSession(int sessionId);
        void playerCommand(char * command);
        void selectPlayer(int sessionId);
        int generateSession(int sessionId);
    private:
        SQLConnector * sql;
        std::set<Player> players;
        std::set<Npc> npcs;
        std::set<GameObject> gameObjects;
        std::set<int> sessions;
        std::set<int> activeSessions;
        int curSession;
        Player readPlayer(std::string name);
        void storePlayer(std::string name);
};

#endif // OLDENTIDE_GAMESTATE_H
