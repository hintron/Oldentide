// Filename:    OldentideServer.h
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Header for dedicated server class.
//              This server is a traditional Universal Datagram Protocol
//              (UDP) Server which will recieve and handle all game
//              packets sent from client.

#ifndef OLDENTIDE_OLDENTIDESERVER_H
#define OLDENTIDE_OLDENTIDESERVER_H

#include "AdminShell.h"
#include "GameState.h"
#include "Npc.h"
#include "Packets.h"
#include "Player.h"
#include "SQLConnector.h"
#include <string>
#include <set>

class OldentideServer{
    public:
        OldentideServer(int port);
        ~OldentideServer();
        void run();
    private:
        int sockfd;
        SQLConnector * sql;
        GameState * gamestate;
        AdminShell * adminshell;
        void genericHandler(PACKET_GENERIC * packet);
        void ackHandler(PACKET_ACK * packet);
        void connectHandler(PACKET_CONNECT * packet);
        void disconnectHandler(PACKET_DISCONNECT * packet);
        void loginHandler(PACKET_LOGIN * packet);
        void listCharactersHandler(PACKET_LISTCHARACTERS * packet);
        void selectCharacterHandler(PACKET_SELECTCHARACTER * packet);
        void deleteCharacterHandler(PACKET_DELETECHARACTER * packet);
        void createCharacterHandler(PACKET_CREATECHARACTER * packet);
        void initializeGameHandler(PACKET_INITIALIZEGAME * packet);
        void updatePcHandler(PACKET_UPDATEPC * packet);
        void updateNpcHandler(PACKET_UPDATENPC * packet);
        void sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet);
        void sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet);
        void sendServerActionHandler(PACKET_SENDSERVERACTION * packet);
};

#endif //OLDENTIDE_OLDENTIDESERVER_H
