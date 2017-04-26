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
#include <sstream>
#include "Utils.h"
#include <netdb.h> // For getnameinfo() and related flags


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

    std::cout << "Server socket: " << utils::GetIpAndPortFromSocket(&server) <<  std::endl;
}

Server::~Server() {
    delete sql;
    delete gameState;
    delete adminshell;
}

void Server::Run() {
    std::thread shell(*adminshell);

    bool listen = true;
    while(listen) {
        sockaddr_in client;
        msgpack::object_handle deserialized_data;
        uint8_t packetType;
        deserialized_data = utils::ReceiveDataFrom(sockfd, &packetType, &client);

        switch (packetType) {
            case false:
                std::cout << "Error receiving packet! Ignoring..." << std::endl;
                break;
            case GENERIC:
                GenericHandler(&deserialized_data, &client);
                break;
            case ACK:
                AckHandler(&deserialized_data, &client);
                break;
            case CONNECT:
                ConnectHandler(&deserialized_data, &client);
                break;
            case DISCONNECT:
                DisconnectHandler(&deserialized_data, &client);
                break;
            case LISTCHARACTERS:
                ListCharactersHandler(&deserialized_data, &client);
                break;
            case SELECTCHARACTER:
                SelectCharacterHandler(&deserialized_data, &client);
                break;
            case DELETECHARACTER:
                DeleteCharacterHandler(&deserialized_data, &client);
                break;
            case CREATECHARACTER:
                CreateCharacterHandler(&deserialized_data, &client);
                break;
            case INITIALIZEGAME:
                InitializeGameHandler(&deserialized_data, &client);
                break;
            case UPDATEPC:
                UpdatePcHandler(&deserialized_data, &client);
                break;
            case UPDATENPC:
                UpdateNpcHandler(&deserialized_data, &client);
                break;
            case SENDPLAYERCOMMAND:
                SendPlayerCommandHandler(&deserialized_data, &client);
                break;
            case SENDPLAYERACTION:
                SendPlayerActionHandler(&deserialized_data, &client);
                break;
            case SENDSERVERACTION:
                SendServerActionHandler(&deserialized_data, &client);
                break;
            case UNITY:
                UnityHandler(&deserialized_data, &client);
                break;
            default:
                std::cout << "Received unknown packet of type " << packetType << std::endl;
                break;
        }
    }
    shell.join();
    return;
}



// // Return error
// int Server::CreateUdpServer(int port){
//     //Set sockfd
// }


// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::GenericHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketGeneric packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::AckHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketAck packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.
void Server::ConnectHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketConnect packet;
    deserialized_data->get().convert(packet);

    // No need to check for session validity with connect requests

    PacketConnect returnPacket;
    returnPacket.sessionId = gameState->GenerateSession(packet.sessionId);
    // Use MessagePack to serialize data
    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);

    // Send the packet
    utils::SendDataTo(sockfd, &buffer, CONNECT, client);

    std::cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << std::endl;
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::DisconnectHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketDisconnect packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    gameState->DisconnectSession(packet.sessionId);
}

void Server::ListCharactersHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketListcharacters packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    std::string account = gameState->GetSessionAccountName(packet.sessionId);
    std::cout << "Account: " << account << " requested their character list." << std::endl;

    // TODO: Need to get an actual list of the player's characters

    PacketListcharacters returnPacket;
    returnPacket.sessionId = packet.sessionId;
    // TODO: return the same packetId that it came with?
    returnPacket.packetId = packet.packetId;
    // TODO: For testing only
        returnPacket.characters.push_back(std::string("Grapthar")); // Test
        returnPacket.characters.push_back(std::string("Harry Potter")); // Test
        returnPacket.characters.push_back(std::string("Willy Wonka")); // Test
    // Use MessagePack to serialize data
    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);
    // Send the packet
    utils::SendDataTo(sockfd, &buffer, LISTCHARACTERS, client);
}

void Server::SelectCharacterHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketSelectcharacter packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    std::cout << "TODO: Need to select character " << packet.character << std::endl;
    // TODO: Select the requested character
    gameState->SelectPlayer(packet.sessionId);
}

void Server::DeleteCharacterHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "TODO: Delete Character handler!" << std::endl;
}

void Server::CreateCharacterHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketCreatecharacter packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }

    // TODO:
    std::cout << "TODO: Create character " << packet.lastName << ", " <<  packet.firstName << std::endl;
}

void Server::InitializeGameHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "InitializeGameHandler!" << std::endl;
}

void Server::UpdatePcHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "UpdatePcHandler!" << std::endl;
}

void Server::UpdateNpcHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "UpdateNpcHandler!" << std::endl;
}

void Server::SendPlayerCommandHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    PacketSendplayercommand packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    std::cout << "SendPlayerCommandHandler!" << std::endl;

    // TODO: Get active session stuff working
    // if (gameState->VerifyActiveSession(packet.sessionId)) {
        gameState->PlayerCommand(packet.command, packet.sessionId);
    // }
    // else {
    //     std::cout << "Nonactive session requested to send a player command..." << packet.sessionId << std::endl;
    // }

    std::stringstream server_response_s;
    server_response_s << "Server says " << packet.sessionId << " session sent message: " << packet.command;

    PacketSendservercommand returnPacket;
    returnPacket.sessionId = packet.sessionId;
    returnPacket.packetId = packet.packetId;
    returnPacket.command = server_response_s.str();

    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);
    utils::SendDataTo(sockfd, &buffer, SENDSERVERCOMMAND, client);
}

void Server::SendPlayerActionHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "SendPlayerActionHandler!" << std::endl;
}

void Server::SendServerActionHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "SendServerActionHandler!" << std::endl;
}


void Server::UnityHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "UnityHandler!" << std::endl;

//     std::cout << "0x" << std::hex << packet->data1 << std::endl;
//     std::cout << "0x" << std::hex << packet->data2 << std::endl;
//     std::cout << "0x" << std::hex << packet->data3 << std::endl;
//     std::cout << "0x" << std::hex << packet->data4 << std::endl;
//     std::cout << "0x" << std::hex << packet->data5 << std::endl;
//     std::cout << "------------------------" << std::endl;
//     PacketUnity retPacket;
//     retPacket.data1 = packet->data1;
//     retPacket.data2 = packet->data2;
//     retPacket.data3 = packet->data3;
//     retPacket.data4 = packet->data4;
//     retPacket.data5 = packet->data5;
//     std::cout << "retPacket: " << std::endl;
//     std::cout << "0x" << std::hex << retPacket.data1 << std::endl;
//     std::cout << "0x" << std::hex << retPacket.data2 << std::endl;
//     std::cout << "0x" << std::hex << retPacket.data3 << std::endl;
//     std::cout << "0x" << std::hex << retPacket.data4 << std::endl;
//     std::cout << "0x" << std::hex << retPacket.data5 << std::endl;
//     std::cout << "----------------------------------------------" << std::endl;
//     sendto(sockfd, (void *)&retPacket, sizeof(PACKET_UNITY), 0, (struct sockaddr *)client, CLIENT_LEN);
}