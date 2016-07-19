// Filename:    OldentideServer.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
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

using namespace std;

OldentideServer::OldentideServer(int port){
    sql = new SQLConnector();
    gamestate = new GameState(sql);
    adminshell = new AdminShell(sql);

    // Create server address struct.
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        cout << "Cannot create socket..." << endl;
        exit(EXIT_FAILURE);
    }

    // Bind socket to a port.
    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0){
        cout << "Cannot bind socket..." << endl;
        exit(EXIT_FAILURE); 
    };
}

OldentideServer::~OldentideServer(){
    delete sql;
    delete gamestate;
    delete adminshell;
}

void OldentideServer::run(){
    thread shell(*adminshell);
    sockaddr_in client;
    socklen_t len = sizeof(client);
    cout << "Server Running!\n";
    bool listen = true;
    while(listen){
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        int n = recvfrom(sockfd, (void *)packet, sizeof(PACKET_GENERIC), 0, (struct sockaddr *)&client, &len);
        if (gamestate->verifySession(packet)){
            switch (packet->packetType){
                case GENERIC:
		    cout << "PAcket 0 received";
                    genericHandler((PACKET_GENERIC*)packet);
                    break;
                case ACK: 
                    ackHandler((PACKET_ACK*)packet);
                    break;
                case CONNECT: 
                    connectHandler((PACKET_CONNECT*)packet, client);
                    break;
                case DISCONNECT: 
                    disconnectHandler((PACKET_DISCONNECT*)packet);
                    break;
                case LOGIN: 
                    loginHandler((PACKET_LOGIN*)packet);
                    break;
                case LISTCHARACTERS: 
                    listCharactersHandler((PACKET_LISTCHARACTERS*)packet);
                    break;
                case SELECTCHARACTER: 
                    selectCharacterHandler((PACKET_SELECTCHARACTER*)packet);
                    break;
                case DELETECHARACTER: 
                    deleteCharacterHandler((PACKET_DELETECHARACTER*)packet);
                    break;
                case CREATECHARACTER: 
                    createCharacterHandler((PACKET_CREATECHARACTER*)packet);
                    break;
                case INITIALIZEGAME: 
                    initializeGameHandler((PACKET_INITIALIZEGAME*)packet);
                    break;
                case UPDATEPC: 
                    updatePcHandler((PACKET_UPDATEPC*)packet);
                    break;
                case UPDATENPC: 
                    updateNpcHandler((PACKET_UPDATENPC*)packet);
                    break;
                case SENDPLAYERCOMMAND: 
                    sendPlayerCommandHandler((PACKET_SENDPLAYERCOMMAND*)packet);
                    break;
                case SENDPLAYERACTION: 
                    sendPlayerActionHandler((PACKET_SENDPLAYERACTION*)packet);
                    break;
                case SENDSERVERACTION: 
                    sendServerActionHandler((PACKET_SENDSERVERACTION*)packet);
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
void OldentideServer::genericHandler(PACKET_GENERIC * packet){
    //cout << "GENERIC Enum ID: " << packet->packetType << endl;
    free(packet);
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void OldentideServer::ackHandler(PACKET_ACK * packet){
    //cout << "ACK Enum ID: " << packet->packetType << endl;
    free(packet);
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.  Do not generate new sessions.
void OldentideServer::connectHandler(PACKET_CONNECT * packet, sockaddr_in client){
    //cout << "CONNECT Enum ID: " << packet->packetType << endl;
    PACKET_CONNECT returnPacket;
    returnPacket.sessionId = gamestate->generateSession(packet);
    cout << "  New connection started, session id " << returnPacket.sessionId << " sent to client!" << endl;
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void OldentideServer::disconnectHandler(PACKET_DISCONNECT * packet){
    //cout << "DISCONNECT Enum ID: " << packet->packetType << endl;
    gamestate->disconnectSession(packet);
    free(packet);
}

void OldentideServer::loginHandler(PACKET_LOGIN * packet){
    //cout << "LOGIN Enum ID: " << packet->packetType << endl;
    bool temp = gamestate->loginUser(packet);
    free(packet);
}

void OldentideServer::listCharactersHandler(PACKET_LISTCHARACTERS * packet){
    //cout << "LISTCHARACTERS Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::selectCharacterHandler(PACKET_SELECTCHARACTER * packet){
    //cout << "SELECTCHARACTER Enum ID: " << packet->packetType << endl;
    gamestate->selectPlayer(packet);
    free(packet);
}

void OldentideServer::deleteCharacterHandler(PACKET_DELETECHARACTER * packet){
    //cout << "DELETECHARACTER Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::createCharacterHandler(PACKET_CREATECHARACTER * packet){
    //cout << "CREATECHARACTER Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::initializeGameHandler(PACKET_INITIALIZEGAME * packet){
    //cout << "INITIALIZEGAME Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::updatePcHandler(PACKET_UPDATEPC * packet){
    //cout << "UPDATEPC Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::updateNpcHandler(PACKET_UPDATENPC * packet){
    //cout << "UPDATENPC Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet){
    //cout << "SENDPLAYERCOMMAND Enum ID: " << packet->packetType << endl;
    if (gamestate->verifyActiveSession(packet->sessionId)){
        gamestate->playerCommand(packet);
    }
    else{
        cout << "Nonactive session requested to send a player command..." << packet->sessionId << endl;
    }
    free(packet);
}

void OldentideServer::sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet){
    //cout << "SENDPLAYERACTION Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::sendServerActionHandler(PACKET_SENDSERVERACTION * packet){
    //cout << "SENDSERVERACTION Enum ID: " << packet->packetType << endl;
    free(packet);
}
