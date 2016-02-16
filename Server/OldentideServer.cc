// Filename:    OldentideServer.cc
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

OldentideServer::OldentideServer(int port){
    sockaddr_in server;
    
    // Create server address struct.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        cout << "Cannot create socket...";
        exit(EXIT_FAILURE);
    }

    // Bind socket to a port.
    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0){
        cout << "Cannot bind socket...";
       exit(EXIT_FAILURE); 
    };
    
    players = new vector<Player>;
    populateNpcs();
}

OldentideServer::~OldentideServer(){
    players->clear();
    delete players;
    npcs->clear();
    delete npcs;
}

void OldentideServer::run(){
    //char mesg[1000];
    sockaddr_in client;
    socklen_t len = sizeof(client);
    bool listen = true;

    // Main listening loop.
    cout << "Server Running!\n";
    while(listen){
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        int n = recvfrom(sockfd, (void *)packet, sizeof(packet), 0, (struct sockaddr *)&client, &len);
        //sendto(sockfd, mesg, n, 0, (struct sockaddr *)&client, sizeof(client));
        switch (packet->packetType){
            case GENERIC:
                genericHandler((PACKET_GENERIC*)packet);
                break;
            case ACK: 
                ackHandler((PACKET_ACK*)packet);
                break;
            case CONNECT: 
                connectHandler((PACKET_CONNECT*)packet);
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
        //listen = false;
    } 
}

void OldentideServer::populateNpcs(){
    npcs = new vector<Npc>;
}

void OldentideServer::genericHandler(PACKET_GENERIC * packet){
    cout << "GENERIC Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::ackHandler(PACKET_ACK * packet){
    cout << "ACK Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::connectHandler(PACKET_CONNECT * packet){
    cout << "CONNECT Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::disconnectHandler(PACKET_DISCONNECT * packet){
    cout << "DISCONNECT Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::loginHandler(PACKET_LOGIN * packet){
    cout << "LOGIN Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::listCharactersHandler(PACKET_LISTCHARACTERS * packet){
    cout << "LISTCHARACTERS Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::selectCharacterHandler(PACKET_SELECTCHARACTER * packet){
    cout << "SELECTCHARACTER Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::deleteCharacterHandler(PACKET_DELETECHARACTER * packet){
    cout << "DELETECHARACTER Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::createCharacterHandler(PACKET_CREATECHARACTER * packet){
    cout << "CREATECHARACTER Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::initializeGameHandler(PACKET_INITIALIZEGAME * packet){
    cout << "INITIALIZEGAME Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::updatePcHandler(PACKET_UPDATEPC * packet){
    cout << "UPDATEPC Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::updateNpcHandler(PACKET_UPDATENPC * packet){
    cout << "UPDATENPC Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet){
    cout << "SENDPLAYERCOMMAND Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet){
    cout << "SENDPLAYERACTION Enum ID: " << packet->packetType << endl;
    free(packet);
}

void OldentideServer::sendServerActionHandler(PACKET_SENDSERVERACTION * packet){
    cout << "SENDSERVERACTION Enum ID: " << packet->packetType << endl;
    free(packet);
}
