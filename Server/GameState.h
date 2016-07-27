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
        bool verifyActiveSession(int sessionId);
        bool createAccount(PACKET_CREATEACCOUNT * packet);
        bool loginUser(PACKET_LOGIN * packet);
        void disconnectSession(PACKET_DISCONNECT * packet);
        void playerCommand(PACKET_SENDPLAYERCOMMAND * packet);
        void selectPlayer(PACKET_SELECTCHARACTER * packet);
        int generateSession(PACKET_CONNECT * packet);
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
