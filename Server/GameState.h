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
#include "Object.h"
#include "Packets.h"
#include "Player.h"
#include "SQLConnector.h"
#include <set>
#include <string>

class GameState{
    public:
        GameState(SQLConnector * sql);
        ~GameState();
        bool verifySession(PACKET_GENERIC * packet);
        Player loadPlayer(std::string name);
        void storePlayer(std::string name);
        int generateSession();
    private:
        SQLConnector * sql;
        std::set<Player> players;
        std::set<Npc> npcs;
        std::set<Object> objects;
        std::set<int> sessions;
        int curSession;
        bool playerSessionLookup(int session);
};

#endif // OLDENTIDE_GAMESTATE_H
