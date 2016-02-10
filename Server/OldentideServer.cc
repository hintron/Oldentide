// Filename:    OldentideServer.cc
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
#include <iostream>
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
    char mesg[1000];
    sockaddr_in client;
    socklen_t len = sizeof(client);
    bool listen = true;

    // Main listening loop.
    cout << "Server Running!\n";
    while(listen){
        n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *)&client, &len);
        //sendto(sockfd, mesg, n, 0, (struct sockaddr *)&client, sizeof(client));
        cout << mesg << endl;
        //listen = false;
    } 
}

void OldentideServer::populateNpcs(){
    npcs = new vector<Npc>;
}
