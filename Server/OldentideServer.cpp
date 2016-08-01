// Filename:    OldentideServer.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "OldentideServer.h"
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

using namespace std;
#define MAX_MESSAGES 500
#define MAX_MESSAGE_LENGTH 500


OldentideServer::OldentideServer(int port){
    sql = new SQLConnector();
    gamestate = new GameState(sql);
    adminshell = new AdminShell(sql);

    // 0 means no messages. The first message will be 1. 
    globalMessageNumber = 0;

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
                case GETSALT: 
                    saltHandler((PACKET_GETSALT*)packet, client);
                    break;
                case CREATEACCOUNT: 
                    createAccountHandler((PACKET_CREATEACCOUNT*)packet, client);
                    break;
                case LOGIN: 
                    loginHandler((PACKET_LOGIN*)packet, client);
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
                case MESSAGE:
                    messageHandler((PACKET_MESSAGE*)packet, client);
                    break;
                case GETLATESTMESSAGE:
                    getLatestMessageHandler((PACKET_GETLATESTMESSAGE*)packet, client);
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
    cout << "Generic packet received" << endl;
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
    cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << endl;
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void OldentideServer::disconnectHandler(PACKET_DISCONNECT * packet){
    //cout << "DISCONNECT Enum ID: " << packet->packetType << endl;
    gamestate->disconnectSession(packet);
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void OldentideServer::saltHandler(PACKET_GETSALT *packet, sockaddr_in client){
    PACKET_GETSALT returnPacket;
    cout << "saltHandler" << endl;
    // Check to make sure account already exists
    // If account doesn't exist, notify user
    // else, return the salt so the user can start key calculation
    int account_exists = sql->get_account_salt(packet->account, returnPacket.saltStringHex);
    if(account_exists){
        strcpy(returnPacket.account, packet->account);
        cout << "  User " << returnPacket.account << " was found on the server." << endl;
        cout << "  Returning salt: " << returnPacket.saltStringHex << endl;
    }
    else {
        cout << "  User " << packet->account << " was not found on the server!" << endl;
        //string failedAccount = "FAILED";
        strcpy(returnPacket.account, "failed");
    }
    // Either return the salt or return the response
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void OldentideServer::createAccountHandler(PACKET_CREATEACCOUNT *packet, sockaddr_in client){
    cout << "createAccountHandler" << endl;
    PACKET_CREATEACCOUNT returnPacket;
    if(gamestate->createAccount(packet)) {
        cout << "  User " << packet->account << " was created successfully!" << endl;
        strcpy(returnPacket.account, packet->account);
    }
    else {
        cout << "  Failed to create user " << packet->account << endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}


void OldentideServer::loginHandler(PACKET_LOGIN * packet, sockaddr_in client){
    cout << "loginHandler" << endl;
    PACKET_CREATEACCOUNT returnPacket;
    //cout << "LOGIN Enum ID: " << packet->packetType << endl;
    if(gamestate->loginUser(packet)) {
        cout << "  User " << packet->account << " logged in successfully!" << endl;
        strcpy(returnPacket.account, packet->account);
    }
    else {
        cout << "  Failed login attempt for user: " << packet->account << endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
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

void OldentideServer::messageHandler(PACKET_MESSAGE *packet, sockaddr_in client){
    cout << "server messageHandler" << endl;
    PACKET_MESSAGE returnPacket;
    if(packet->globalMessageNumber != 0){
        cout << "Message lookup" << endl;
        // Look up the requested message and return it
        if(packet->globalMessageNumber >= 1 && packet->globalMessageNumber <= MAX_MESSAGES){
            cout << "Looking up message " << packet->globalMessageNumber << endl;
            // Remember, index = messageNumber - 1
            string message_lookup = globalMessageArray.at(packet->globalMessageNumber-1);
            cout << message_lookup << endl; 
            // Look up the message and return it
            strcpy(returnPacket.message, message_lookup.c_str());
            returnPacket.globalMessageNumber = packet->globalMessageNumber;
            // strcpy(returnPacket.account, globalMessageAccountArray[packet->globalMessageNumber]); 
        }
        else {
            // Invalid message
            returnPacket.globalMessageNumber = 0; 
        }
    }
    else {
        // Save the incoming message and return the assigned message number
        if(globalMessageNumber > MAX_MESSAGES){
            cout << "Ran out of message space! Reached max number of messages" << endl;
            // Ran out of message space
            returnPacket.globalMessageNumber = 0;
        } else{
            globalMessageNumber++;
            cout << "Saving message with number " << globalMessageNumber << ": " << packet->message << endl;
            // TODO: Sanitize message?
            // TODO: Make this more efficient/effective 
            // Increase the global message number (start at 1 - 0 means no messages)
            // TODO: Atomically assign message a global message number
            std::string message = packet->message;
            //char *message = (char *) malloc(MAX_MESSAGE_LENGTH);
            // TODO: Atomically store message in global array of messages
            //strcpy(message, packet->message);
            // Store the first messsage at index 0, second message at 1, etc.
            globalMessageArray.push_back(message);
            // TODO: Store the username of the account that sent the message
            // globalMessageAccountArray[globalMessageNumber-1] = "dummy user";

            // TODO: Create a packet that only has the message number
            returnPacket.globalMessageNumber = globalMessageNumber;
        }
    }
    
    // Return the message number to indicate success, or null on error 
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_MESSAGE), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void OldentideServer::getLatestMessageHandler(PACKET_GETLATESTMESSAGE *packet, sockaddr_in client){
    cout << "server getLatestMessageHandler" << endl;
    PACKET_GETLATESTMESSAGE returnPacket;

    if(globalMessageNumber > MAX_MESSAGES){
        // 0 means failed or no messages
        // Ran out of message space
        returnPacket.globalMessageNumber = 0;
    }
    else {
        // Return the latest message number in the global message buffer
        returnPacket.globalMessageNumber = globalMessageNumber;
    }

    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_GETLATESTMESSAGE), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}
