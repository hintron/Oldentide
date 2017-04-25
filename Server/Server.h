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
        // sockaddr_in client; // The current client that is being served
        socklen_t CLIENT_LEN; // The size of the client socket type
        SQLConnector * sql;
        GameState * gameState;
        AdminShell * adminshell;
        std::string GetIpAndPortFromSocket(sockaddr_in *socket);
        uint8_t ReceiveDataFromClient(msgpack::object *data_out, sockaddr_in *client);


        void GenericHandler(msgpack::object *data, sockaddr_in client);
        void AckHandler(msgpack::object *data, sockaddr_in client);
        void ConnectHandler(msgpack::object *data, sockaddr_in client);
        void DisconnectHandler(msgpack::object *data, sockaddr_in client);
        void ListCharactersHandler(msgpack::object *data, sockaddr_in client);
        void SelectCharacterHandler(msgpack::object *data, sockaddr_in client);
        void DeleteCharacterHandler(msgpack::object *data, sockaddr_in client);
        void CreateCharacterHandler(msgpack::object *data, sockaddr_in client);
        void InitializeGameHandler(msgpack::object *data, sockaddr_in client);
        void UpdatePcHandler(msgpack::object *data, sockaddr_in client);
        void UpdateNpcHandler(msgpack::object *data, sockaddr_in client);
        void SendPlayerCommandHandler(msgpack::object *data, sockaddr_in client);
        void SendPlayerActionHandler(msgpack::object *data, sockaddr_in client);
        void SendServerActionHandler(msgpack::object *data, sockaddr_in client);
        void UnityHandler(msgpack::object *data, sockaddr_in client);
};

#endif //OLDENTIDE_SERVER_H
