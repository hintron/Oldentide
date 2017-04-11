// Filename:    Server.h
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
#include <arpa/inet.h>
#include <set>
#include <string>

class Server{
    public:
        Server(int port);
        ~Server();
        void Run();
    private:
        int sockfd;
        SQLConnector * sql;
        GameState * gameState;
        AdminShell * adminshell;
        void GenericHandler(PACKET_GENERIC * packet, sockaddr_in client);
        void AckHandler(PACKET_ACK * packet, sockaddr_in client);
        void ConnectHandler(PACKET_CONNECT * packet, sockaddr_in client);
        void DisConnectHandler(PACKET_DISCONNECT * packet, sockaddr_in client);
        void ListCharactersHandler(PACKET_LISTCHARACTERS * packet, sockaddr_in client);
        void SelectCharacterHandler(PACKET_SELECTCHARACTER * packet, sockaddr_in client);
        void DeleteCharacterHandler(PACKET_DELETECHARACTER * packet, sockaddr_in client);
        void CreateCharacterHandler(PACKET_CREATECHARACTER * packet, sockaddr_in client);
        void InitializeGameHandler(PACKET_INITIALIZEGAME * packet, sockaddr_in client);
        void UpdatePcHandler(PACKET_UPDATEPC * packet, sockaddr_in client);
        void UpdateNpcHandler(PACKET_UPDATENPC * packet, sockaddr_in client);
        void SendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet, sockaddr_in client);
        void SendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet, sockaddr_in client);
        void SendServerActionHandler(PACKET_SENDSERVERACTION * packet, sockaddr_in client);
};

#endif //OLDENTIDE_SERVER_H
