// Filename:    OldentideServer.h
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Header for dedicated server class.

#ifndef OLDENTIDE_OLDENTIDESERVER_H
#define OLDENTIDE_OLDENTIDESERVER_H

#include "Player.h"
#include "Npc.h"
#include "Packets.h"
#include "SQLConnector.h"
#include <string>
#include <set>
#include <vector>

class OldentideServer{
    public:
        OldentideServer(int port);
        ~OldentideServer();
        void run();
        static bool listen;
        std::vector<Player>* getPlayers();
        std::vector<Npc>* getNpcs();
    private:
        int sockfd;
        SQLConnector * sql;
        std::vector<Player>* players;
        std::vector<Npc>* npcs;
        void populateNpcs();
        bool verifySession(int session);
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
        static std::vector<std::string> split(std::string s, char delim);
        static void startAdminShell();
        static void printUsage();
        static void printLogo();
};

#endif //OLDENTIDE_OLDENTIDESERVER_H
