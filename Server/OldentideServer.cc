// Filename:    OldentideServer.cc
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

OldentideServer::OldentideServer(int port)(
    int sockfd;
    struct sockaddr_in serverAddress;

    // Create server address struct.
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Failed to create socket.");
        exit(EXIT_FAILURE);
    }
    
    // Bind socket to a port.
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("Failed to bind socket.");
        exit(EXIT_FAILURE);
    }

    players = new vector<Player>;
    populateNpcs();
)

OldentideServer::~OldentideServer(
    players.clear();
    delete players;
    npcs.clear();
    delete npcs;
)

void OldentideServer::run(){

}

void OldentideServer::populateNpcs(){
    npcs = new vector<Npc>;
}
