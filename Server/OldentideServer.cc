// Filename:    OldentideServer.cc
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
#include <arpa/inet.h>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <limits.h>

using namespace std;

OldentideServer::OldentideServer(int port){
    populateNpcs();
    players = new vector<Player>;
    sql = new SQLConnector();

    // Create server address struct.
    sockaddr_in server;
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
}

OldentideServer::~OldentideServer(){
    players->clear();
    delete players;
    npcs->clear();
    delete npcs;
}

void OldentideServer::run(){
    sockaddr_in client;
    socklen_t len = sizeof(client);
    listen = true;

    // Main listening loop.
    thread shell (startAdminShell);
    cout << "Server Running!\n";
    while(OldentideServer::listen){
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        int n = recvfrom(sockfd, (void *)packet, sizeof(packet), 0, (struct sockaddr *)&client, &len);
        if (verifySession(packet->sessionId)){ 
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
                    listen = false;
                    break;
            }
        }
    }
    shell.join();
    return;
}

void OldentideServer::populateNpcs(){
    npcs = new vector<Npc>;
}

bool OldentideServer::verifySession(int session){
    cout << endl << session << endl;
    return true;
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

vector<string> OldentideServer::split(string s, char delim) {
    string token;
    vector<string> tokens;
    istringstream ss(s);
    while(getline(ss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

void OldentideServer::startAdminShell(){
    string adminCommand;
    char serverHostname[HOST_NAME_MAX];
    gethostname(serverHostname, HOST_NAME_MAX);
    cout << "Starting Server Administrator Shell.\n";
    printLogo();
    while(true){
        cout << "  OldentideAdmin@" << serverHostname << ": ";
        getline(cin,adminCommand);
        vector<string> adminTokens = split(adminCommand, ' ');
        if (adminTokens[0] == "/shutdown"){
            listen = false;
            cout << "  Oldentide Dedicated Server is shutting down..." << endl;
            exit(EXIT_SUCCESS);
            return;
        }
        else if(adminTokens[0] == "/list"){
            if (adminTokens.size() == 2){
                if (adminTokens[1] == "PC"){
                    cout << "PCSSSSSS" << endl;          
                }
                if (adminTokens[1] == "NPC"){
                    cout << "NPCSSSSS" << endl;    
                }
            }
            else{
                printUsage();
            }
        }
        else{
            printUsage();
        }
    }
}

void OldentideServer::printUsage(){
    cout << "    Dedicated Server Admin Usage:" << endl;
    cout << "    /shutdown    = Shuts down the server." << endl;
    cout << "    /list <var>  = Lists all entities of given <var> on server, where var is [PC, NPC]." << endl;
}

void OldentideServer::printLogo(){
    cout << "    ____           ___   _____         _____  _____  ___   _____" << endl;
    cout << "   /    \\  |      |   \\  |      |   |    |      |    |  \\  |" << endl;
    cout << "  /      \\ |      |    \\ |      |\\  |    |      |    |   \\ |" << endl;
    cout << "  |      | |      |    | |___   | \\ |    |      |    |   | |___" << endl;
    cout << "  \\      / |      |   /  |      |  \\|    |      |    |   / |" << endl;
    cout << "   \\____/  |_____ |__/   |____  |   \\    |    __|__  |__/  |____" << endl;
    cout << "   " << endl; 
    cout << "                                ^" << endl;
    cout << "                               / \\" << endl;
    cout << "                              /\\_/\\" << endl;
    cout << "                             / | | \\" << endl;
    cout << "                             \\ |_| /" << endl;
    cout << "                              \\/ \\/" << endl;
    cout << "                               \\ /" << endl;
    cout << "                                |" << endl;
    cout << "   " << endl;
}
