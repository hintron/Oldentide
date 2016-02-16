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
    int n;
    //char mesg[1000];
    sockaddr_in client;
    socklen_t len = sizeof(client);
    bool listen = true;

    // Main listening loop.
    cout << "Server Running!\n";
    while(listen){
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        n = recvfrom(sockfd, (void *)packet, sizeof(packet), 0, (struct sockaddr *)&client, &len);
        //sendto(sockfd, mesg, n, 0, (struct sockaddr *)&client, sizeof(client));
        switch (packet->packetType){
            case GENERIC:
                cout << "GENERIC\n\r";
                genericHandler((PACKET_GENERIC*)packet);
                break;
            case ACK: 
                cout << "ACK\n\r";
                ackHandler((PACKET_ACK*)packet);
                break;
            case CONNECT: 
                cout << "CONNECT\n\r";
                connectHandler((PACKET_CONNECT*)packet);
                break;
            case DISCONNECT: 
                cout << "DISCONNECT\n\r";
                disconnectHandler((PACKET_DISCONNECT*)packet);
                break;
            case LOGIN: 
                cout << "LOGIN\n\r";
                loginHandler((PACKET_LOGIN*)packet);
                break;
            case LISTCHARACTERS: 
                cout << "LISTCHARACTERS\n\r";
                listCharactersHandler((PACKET_LISTCHARACTERS*)packet);
                break;
            case SELECTCHARACTER: 
                cout << "SELECTCHARACTER\n\r";
                selectCharacterHandler((PACKET_SELECTCHARACTER*)packet);
                break;
            case DELETECHARACTER: 
                cout << "DELETECHARACTER\n\r";
                deleteCharacterHandler((PACKET_DELETECHARACTER*)packet);
                break;
            case CREATECHARACTER: 
                cout << "CREATECHARACTER\n\r";
                createCharacterHandler((PACKET_CREATECHARACTER*)packet);
                break;
            case INITIALIZEGAME: 
                cout << "INITIALIZEGAME\n\r";
                initializeGameHandler((PACKET_INITIALIZEGAME*)packet);
                break;
            case UPDATEPC: 
                cout << "UPDATEPC\n\r";
                updatePcHandler((PACKET_UPDATEPC*)packet);
                break;
            case UPDATENPC: 
                cout << "UPDATENPC\n\r";
                updateNpcHandler((PACKET_UPDATENPC*)packet);
                break;
            case SENDPLAYERCOMMAND: 
                cout << "SENDPLAYERCOMMAND\n\r";
                sendPlayerCommandHandler((PACKET_SENDPLAYERCOMMAND*)packet);
                break;
            case SENDPLAYERACTION: 
                cout << "SENDPLAYERACTION\n\r";
                sendPlayerActionHandler((PACKET_SENDPLAYERACTION*)packet);
                break;
            case SENDSERVERACTION: 
                cout << "SENDSERVERACTION\n\r";
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
    free(packet);
}

void OldentideServer::ackHandler(PACKET_ACK * packet){
    free(packet);
}

void OldentideServer::connectHandler(PACKET_CONNECT * packet){
    free(packet);
}

void OldentideServer::disconnectHandler(PACKET_DISCONNECT * packet){
    free(packet);
}

void OldentideServer::loginHandler(PACKET_LOGIN * packet){
    free(packet);
}

void OldentideServer::listCharactersHandler(PACKET_LISTCHARACTERS * packet){
    free(packet);
}

void OldentideServer::selectCharacterHandler(PACKET_SELECTCHARACTER * packet){
    free(packet);
}

void OldentideServer::deleteCharacterHandler(PACKET_DELETECHARACTER * packet){
    free(packet);
}

void OldentideServer::createCharacterHandler(PACKET_CREATECHARACTER * packet){
    free(packet);
}

void OldentideServer::initializeGameHandler(PACKET_INITIALIZEGAME * packet){
    free(packet);
}

void OldentideServer::updatePcHandler(PACKET_UPDATEPC * packet){
    free(packet);
}

void OldentideServer::updateNpcHandler(PACKET_UPDATENPC * packet){
    free(packet);
}

void OldentideServer::sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet){
    free(packet);
}

void OldentideServer::sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet){
    free(packet);
}

void OldentideServer::sendServerActionHandler(PACKET_SENDSERVERACTION * packet){
    free(packet);
}
