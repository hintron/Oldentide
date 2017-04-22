// Filename:    Server.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "Server.h"
#include <cstring>
#include <iostream>
#include <iterator>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <limits.h>
#include <msgpack.hpp>
#include "Utils.h"


Server::Server(int port) {
    sql = new SQLConnector();
    gameState = new GameState(sql);
    adminshell = new AdminShell(sql, gameState);

    // Create server address struct.
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        std::cout << "Cannot create socket..." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Bind socket to a port.
    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0) {
        std::cout << "Cannot bind socket..." << std::endl;
        exit(EXIT_FAILURE);
    };
}

Server::~Server() {
    delete sql;
    delete gameState;
    delete adminshell;
}

void Server::Run() {
    std::thread shell(*adminshell);
    sockaddr_in client;
    socklen_t len = sizeof(client);

    bool listen = true;
    while(listen) {
        char *packet = (char *)malloc(PACKET_MAX_SIZE);
        int n = recvfrom(sockfd, packet, PACKET_MAX_SIZE, 0, (struct sockaddr *)&client, &len);

        uint8_t packetType = utils::GetPacketTypeFromPacket(packet);
        uint16_t msgpckSize = utils::GetMsgpckSizeFromPacket(packet);

        std::cout << "Packet type: " << (unsigned int) packetType << std::endl;
        std::cout << "Msgpck Size: " << msgpckSize << std::endl;

        // Check to make sure we don't accidentally access data outside the packet!
        if(msgpckSize > MSGPCK_MAX_PAYLOAD_SIZE){
            std::cout << "Msgpck Size is too large to be correct! Ignoring packet and continuing to avoid buffer overflow..." << std::endl;
            continue;
        }

        // Convert to std::string so we can use it with messagepack
        std::string msgpck_data = utils::GetMsgpckDataFromPacket(packet);

        utils::PrintStringHex(&msgpck_data);

        // Use MessagePack to Deserialize the payload
        msgpack::object_handle oh = msgpack::unpack(msgpck_data.data(), msgpck_data.size());
        msgpack::object deserialized = oh.get();
        std::cout << deserialized << std::endl;
        TestData test;
        deserialized.convert(test);

        // Prove that deserialization worked
        std::cout << test.value << std::endl;
        std::cout << test.i << std::endl;

        continue;

        // TODO: Get messagepack working for all types of packets!

        bool validSession = true;
        // TODO: Uncomment for production code
        // if (packetType != CONNECT) {
        //     validSession = gameState->VerifySession(packet->sessionId);
        // }
        if (validSession) {
            switch (packetType) {
                case GENERIC:
                    GenericHandler((PACKET_GENERIC*)packet, client);
                    break;
                case ACK:
                    AckHandler((PACKET_ACK*)packet, client);
                    break;
                case CONNECT:
                    ConnectHandler((PACKET_CONNECT*)packet, client);
                    break;
                case DISCONNECT:
                    DisConnectHandler((PACKET_DISCONNECT*)packet, client);
                    break;
                case LISTCHARACTERS:
                    ListCharactersHandler((PACKET_LISTCHARACTERS*)packet, client);
                    break;
                case SELECTCHARACTER:
                    SelectCharacterHandler((PACKET_SELECTCHARACTER*)packet, client);
                    break;
                case DELETECHARACTER:
                    DeleteCharacterHandler((PACKET_DELETECHARACTER*)packet, client);
                    break;
                case CREATECHARACTER:
                    CreateCharacterHandler((PACKET_CREATECHARACTER*)packet, client);
                    break;
                case INITIALIZEGAME:
                    InitializeGameHandler((PACKET_INITIALIZEGAME*)packet, client);
                    break;
                case UPDATEPC:
                    UpdatePcHandler((PACKET_UPDATEPC*)packet, client);
                    break;
                case UPDATENPC:
                    UpdateNpcHandler((PACKET_UPDATENPC*)packet, client);
                    break;
                case SENDPLAYERCOMMAND:
                    SendPlayerCommandHandler((PACKET_SENDPLAYERCOMMAND*)packet, client);
                    break;
                case SENDPLAYERACTION:
                    SendPlayerActionHandler((PACKET_SENDPLAYERACTION*)packet, client);
                    break;
                case SENDSERVERACTION:
                    SendServerActionHandler((PACKET_SENDSERVERACTION*)packet, client);
                    break;
                case UNITY:
                    UnityHandler((PACKET_UNITY*)packet, client);
                    break;
                default:
                    std::cout << "Received unknown packet of type " << packetType << std::endl;
                    break;
           }
        }
        else {
            free(packet);
        }

        // TODO: Instead of freeing the packet at the end of every function call, free it here, when they all join back up!
        // free(packet);
    }
    shell.join();
    return;
}

// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::GenericHandler(PACKET_GENERIC * packet, sockaddr_in client) {
    free(packet);
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::AckHandler(PACKET_ACK * packet, sockaddr_in client) {
    free(packet);
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.
void Server::ConnectHandler(PACKET_CONNECT * packet, sockaddr_in client) {
    PACKET_CONNECT returnPacket;
    returnPacket.sessionId = gameState->GenerateSession(packet->sessionId);
    std::cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << std::endl;
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::DisConnectHandler(PACKET_DISCONNECT * packet, sockaddr_in client) {
    gameState->DisconnectSession(packet->sessionId);
    free(packet);
}

void Server::ListCharactersHandler(PACKET_LISTCHARACTERS * packet, sockaddr_in client) {
    std::string account = gameState->GetSessionAccountName(packet->sessionId);
    std::cout << "Account: " << account << " requested their character list." << std::endl;

    free(packet);
}

void Server::SelectCharacterHandler(PACKET_SELECTCHARACTER * packet, sockaddr_in client) {
    gameState->SelectPlayer(packet->sessionId);
    free(packet);
}

void Server::DeleteCharacterHandler(PACKET_DELETECHARACTER * packet, sockaddr_in client) {
    free(packet);
}

void Server::CreateCharacterHandler(PACKET_CREATECHARACTER * packet, sockaddr_in client) {
    free(packet);
}

void Server::InitializeGameHandler(PACKET_INITIALIZEGAME * packet, sockaddr_in client) {
    free(packet);
}

void Server::UpdatePcHandler(PACKET_UPDATEPC * packet, sockaddr_in client) {
    free(packet);
}

void Server::UpdateNpcHandler(PACKET_UPDATENPC * packet, sockaddr_in client) {
    free(packet);
}

void Server::SendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet, sockaddr_in client) {
    if (gameState->VerifyActiveSession(packet->sessionId)) {
        gameState->PlayerCommand(packet->command, packet->sessionId);
    }
    else {
        std::cout << "Nonactive session requested to send a player command..." << packet->sessionId << std::endl;
    }
    PACKET_SENDSERVERCOMMAND returnPacket;
    std::string temp = "Server says " + std::to_string(packet->sessionId) + " session sent message: ";
    temp.append(packet->command);
    strcpy(returnPacket.command, temp.c_str());
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_SENDSERVERCOMMAND), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::SendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet, sockaddr_in client) {
    free(packet);
}

void Server::SendServerActionHandler(PACKET_SENDSERVERACTION * packet, sockaddr_in client) {
    free(packet);
}


void Server::UnityHandler(PACKET_UNITY * packet, sockaddr_in client) {
    std::cout << "0x" << std::hex << packet->data1 << std::endl;
    std::cout << "0x" << std::hex << packet->data2 << std::endl;
    std::cout << "0x" << std::hex << packet->data3 << std::endl;
    std::cout << "0x" << std::hex << packet->data4 << std::endl;
    std::cout << "0x" << std::hex << packet->data5 << std::endl;
    std::cout << "------------------------" << std::endl;
    PACKET_UNITY retPacket;
    retPacket.data1 = packet->data1;
    retPacket.data2 = packet->data2;
    retPacket.data3 = packet->data3;
    retPacket.data4 = packet->data4;
    retPacket.data5 = packet->data5;
    std::cout << "retPacket: " << std::endl;
    std::cout << "0x" << std::hex << retPacket.data1 << std::endl;
    std::cout << "0x" << std::hex << retPacket.data2 << std::endl;
    std::cout << "0x" << std::hex << retPacket.data3 << std::endl;
    std::cout << "0x" << std::hex << retPacket.data4 << std::endl;
    std::cout << "0x" << std::hex << retPacket.data5 << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    sendto(sockfd, (void *)&retPacket, sizeof(PACKET_UNITY), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}