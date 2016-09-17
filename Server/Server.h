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
        void GenericHandler(PACKET_GENERIC * packet);
        void AckHandler(PACKET_ACK * packet);
        void ConnectHandler(PACKET_CONNECT * packet, sockaddr_in client);
        void DisConnectHandler(PACKET_DISCONNECT * packet);
        void GetSaltHandler(PACKET_GETSALT *packet, sockaddr_in client);
        void CreateAccountHandler(PACKET_CREATEACCOUNT *packet, sockaddr_in client);
        void LoginHandler(PACKET_LOGIN * packet, sockaddr_in client);
        void ListCharactersHandler(PACKET_LISTCHARACTERS * packet);
        void SelectCharacterHandler(PACKET_SELECTCHARACTER * packet);
        void DeleteCharacterHandler(PACKET_DELETECHARACTER * packet);
        void CreateCharacterHandler(PACKET_CREATECHARACTER * packet);
        void InitializeGameHandler(PACKET_INITIALIZEGAME * packet);
        void UpdatePcHandler(PACKET_UPDATEPC * packet);
        void UpdateNpcHandler(PACKET_UPDATENPC * packet);
        void SendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet);
        void SendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet);
        void SendServerActionHandler(PACKET_SENDSERVERACTION * packet);
        void UnityHandler(PACKET_UNITY * packet, sockaddr_in client);
};

#endif //OLDENTIDE_SERVER_H
