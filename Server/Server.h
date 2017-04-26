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

        void GenericHandler(msgpack::object_handle *data, sockaddr_in *client);
        void AckHandler(msgpack::object_handle *data, sockaddr_in *client);
        void ConnectHandler(msgpack::object_handle *data, sockaddr_in *client);
        void DisconnectHandler(msgpack::object_handle *data, sockaddr_in *client);
        void ListCharactersHandler(msgpack::object_handle *data, sockaddr_in *client);
        void SelectCharacterHandler(msgpack::object_handle *data, sockaddr_in *client);
        void DeleteCharacterHandler(msgpack::object_handle *data, sockaddr_in *client);
        void CreateCharacterHandler(msgpack::object_handle *data, sockaddr_in *client);
        void InitializeGameHandler(msgpack::object_handle *data, sockaddr_in *client);
        void UpdatePcHandler(msgpack::object_handle *data, sockaddr_in *client);
        void UpdateNpcHandler(msgpack::object_handle *data, sockaddr_in *client);
        void SendPlayerCommandHandler(msgpack::object_handle *data, sockaddr_in *client);
        void SendPlayerActionHandler(msgpack::object_handle *data, sockaddr_in *client);
        void SendServerActionHandler(msgpack::object_handle *data, sockaddr_in *client);
        void UnityHandler(msgpack::object_handle *data, sockaddr_in *client);
};

#endif //OLDENTIDE_SERVER_H
