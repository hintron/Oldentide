// Filename:    Server.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "Server.h"
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <limits.h>

Server::Server(int port) {
    sql = new SQLConnector();
    gamestate = new GameState(sql);
    adminshell = new AdminShell(sql);

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
    delete gamestate;
    delete adminshell;
}

void Server::Run() {
    std::thread shell(*adminshell);
    sockaddr_in client;
    socklen_t len = sizeof(client);
    std::cout << "Server Running!\n";
    std::cout << "Packet Sizes:\n";
    std::cout << "GENERIC: " << sizeof(PACKET_GENERIC) << std::endl;
    std::cout << "ACK: " << sizeof(PACKET_ACK) << std::endl;
    std::cout << "CONNECT: " << sizeof(PACKET_CONNECT) << std::endl;
    std::cout << "DISCONNECT: " << sizeof(PACKET_DISCONNECT) << std::endl;
    std::cout << "GETSALT: " << sizeof(PACKET_GETSALT) << std::endl;
    std::cout << "CREATEACCOUNT: " << sizeof(PACKET_CREATEACCOUNT) << std::endl;
    std::cout << "LOGIN: " << sizeof(PACKET_LOGIN) << std::endl;
    std::cout << "LISTCHARACTERS: " << sizeof(PACKET_LISTCHARACTERS) << std::endl;
    std::cout << "SELECTCHARACTER: " << sizeof(PACKET_SELECTCHARACTER) << std::endl;
    std::cout << "DELETECHARACTER: " << sizeof(PACKET_DELETECHARACTER) << std::endl;
    std::cout << "CREATECHARACTER: " << sizeof(PACKET_CREATECHARACTER) << std::endl;
    std::cout << "INITIALIZEGAME: " << sizeof(PACKET_INITIALIZEGAME) << std::endl;
    std::cout << "UPDATEPC: " << sizeof(PACKET_UPDATEPC) << std::endl;
    std::cout << "UPDATENPC: " << sizeof(PACKET_UPDATENPC) << std::endl;
    std::cout << "SENDPLAYERCOMMAND: " << sizeof(PACKET_SENDPLAYERCOMMAND) << std::endl;
    std::cout << "SENDPLAYERACTION: " << sizeof(PACKET_SENDPLAYERACTION) << std::endl;
    std::cout << "SENDSERVERACTION: " << sizeof(PACKET_SENDSERVERACTION) << std::endl;
	bool validSession = true;
    bool listen = true;
    while(listen) {
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        int n = recvfrom(sockfd, (void *)packet, sizeof(PACKET_GENERIC), 0, (struct sockaddr *)&client, &len);
        
        if (packet->packetType != CONNECT) {
			validSession = gamestate->VerifySession(packet->sessionId);
		}
        if (validSession) {
            switch (packet->packetType) {
                case GENERIC:
                    GenericHandler((PACKET_GENERIC*)packet);
                    break;
                case ACK:
                    AckHandler((PACKET_ACK*)packet);
                    break;
                case CONNECT:
                    ConnectHandler((PACKET_CONNECT*)packet, client);
                    break;
                case DISCONNECT:
                    DisConnectHandler((PACKET_DISCONNECT*)packet);
                    break;
                case GETSALT:
                    SaltHandler((PACKET_GETSALT*)packet, client);
                    break;
                case CREATEACCOUNT:
                    CreateAccountHandler((PACKET_CREATEACCOUNT*)packet, client);
                    break;
                case LOGIN:
                    LoginHandler((PACKET_LOGIN*)packet, client);
                    break;
                case LISTCHARACTERS:
                    ListCharactersHandler((PACKET_LISTCHARACTERS*)packet);
                    break;
                case SELECTCHARACTER:
                    SelectCharacterHandler((PACKET_SELECTCHARACTER*)packet);
                    break;
                case DELETECHARACTER:
                    DeleteCharacterHandler((PACKET_DELETECHARACTER*)packet);
                    break;
                case CREATECHARACTER:
                    CreateCharacterHandler((PACKET_CREATECHARACTER*)packet);
                    break;
                case INITIALIZEGAME:
                    InitializeGameHandler((PACKET_INITIALIZEGAME*)packet);
                    break;
                case UPDATEPC:
                    UpdatePcHandler((PACKET_UPDATEPC*)packet);
                    break;
                case UPDATENPC:
                    UpdateNpcHandler((PACKET_UPDATENPC*)packet);
                    break;
                case SENDPLAYERCOMMAND:
                    SendPlayerCommandHandler((PACKET_SENDPLAYERCOMMAND*)packet);
                    break;
                case SENDPLAYERACTION:
                    SendPlayerActionHandler((PACKET_SENDPLAYERACTION*)packet);
                    break;
                case SENDSERVERACTION:
                    SendServerActionHandler((PACKET_SENDSERVERACTION*)packet);
                    break;
                case UNITY:
                    UnityHandler((PACKET_UNITY*)packet, client);
                    break;
           }
        }
        else {
            free(packet);
        }
    }
    shell.join();
    return;
}

// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::GenericHandler(PACKET_GENERIC * packet) {
    free(packet);
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::AckHandler(PACKET_ACK * packet) {
    free(packet);
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.
void Server::ConnectHandler(PACKET_CONNECT * packet, sockaddr_in client) {
    PACKET_CONNECT returnPacket;
    returnPacket.sessionId = gamestate->GenerateSession(packet->sessionId);
    std::cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << std::endl;
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::DisConnectHandler(PACKET_DISCONNECT * packet) {
    gamestate->DisconnectSession(packet->sessionId);
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::SaltHandler(PACKET_GETSALT *packet, sockaddr_in client) {
    PACKET_GETSALT returnPacket;
    std::cout << "SaltHandler" << std::endl;
    // Check to make sure account already exists
    // If account doesn't exist, notify user
    // else, return the salt so the user can start key calculation
    int account_exists = sql->GetAccountSalt(packet->account, returnPacket.saltStringHex);
    if (account_exists) {
        strcpy(returnPacket.account, packet->account);
        std::cout << "User " << returnPacket.account << " was found on the server." << std::endl;
        std::cout << "Returning salt: " << returnPacket.saltStringHex << std::endl;
    }
    else {
        std::cout << "User " << packet->account << " was not found on the server!" << std::endl;
        //std::string failedAccount = "FAILED";
        strcpy(returnPacket.account, "failed");
    }
    // Either return the salt or return the response
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::CreateAccountHandler(PACKET_CREATEACCOUNT *packet, sockaddr_in client) {
    PACKET_CREATEACCOUNT returnPacket;
    if (gamestate->CreateAccount(packet->account, packet->keyStringHex, packet->saltStringHex)) {
        std::cout << "User " << packet->account << " was created successfully!" << std::endl;
        strcpy(returnPacket.account, packet->account);
    }
    else {
        std::cout << "Failed to create user " << packet->account << std::endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::LoginHandler(PACKET_LOGIN * packet, sockaddr_in client) {
    PACKET_CREATEACCOUNT returnPacket;
    if (gamestate->LoginUser(packet->account, packet->keyStringHex)) {
        std::cout << "User " << packet->account << " logged in successfully!" << std::endl;
        strcpy(returnPacket.account, packet->account);
        // Register the accountName to the sessionId
        gamestate->SetSessionAccountName(packet->account, packet->sessionId);
    }
    else {
        std::cout << "Failed login attempt for user: " << packet->account << std::endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::ListCharactersHandler(PACKET_LISTCHARACTERS * packet) {
    free(packet);
}

void Server::SelectCharacterHandler(PACKET_SELECTCHARACTER * packet) {
    gamestate->SelectPlayer(packet->sessionId);
    free(packet);
}

void Server::DeleteCharacterHandler(PACKET_DELETECHARACTER * packet) {
    free(packet);
}

void Server::CreateCharacterHandler(PACKET_CREATECHARACTER * packet) {
    free(packet);
}

void Server::InitializeGameHandler(PACKET_INITIALIZEGAME * packet) {
    free(packet);
}

void Server::UpdatePcHandler(PACKET_UPDATEPC * packet) {
    free(packet);
}

void Server::UpdateNpcHandler(PACKET_UPDATENPC * packet) {
    free(packet);
}

void Server::SendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet) {
    if (gamestate->VerifyActiveSession(packet->sessionId)) {
        gamestate->PlayerCommand(packet->command, packet->sessionId);
    }
    else {
        std::cout << "Nonactive session requested to send a player command..." << packet->sessionId << std::endl;
    }
    free(packet);
}

void Server::SendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet) {
    free(packet);
}

void Server::SendServerActionHandler(PACKET_SENDSERVERACTION * packet) {
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
