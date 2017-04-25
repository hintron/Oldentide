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

    std::cout << "Server socket: " << GetIpAndPortFromSocket(&server) <<  std::endl;

    // Set up some client constants
    CLIENT_LEN = sizeof(sockaddr_in);
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
        msgpack::object deserialized_data;
        uint8_t packetType = ReceiveDataFromClient(&deserialized_data, &client);

        switch (packetType) {
            case false:
                std::cout << "Error receiving packet! Ignoring..." << std::endl;
                break;
            case GENERIC:
                GenericHandler(&deserialized_data, client);
                break;
            case ACK:
                AckHandler(&deserialized_data, client);
                break;
            case CONNECT:
                ConnectHandler(&deserialized_data, client);
                break;
            case DISCONNECT:
                DisconnectHandler(&deserialized_data, client);
                break;
            case LISTCHARACTERS:
                ListCharactersHandler(&deserialized_data, client);
                break;
            case SELECTCHARACTER:
                SelectCharacterHandler(&deserialized_data, client);
                break;
            case DELETECHARACTER:
                DeleteCharacterHandler(&deserialized_data, client);
                break;
            case CREATECHARACTER:
                CreateCharacterHandler(&deserialized_data, client);
                break;
            case INITIALIZEGAME:
                InitializeGameHandler(&deserialized_data, client);
                break;
            case UPDATEPC:
                UpdatePcHandler(&deserialized_data, client);
                break;
            case UPDATENPC:
                UpdateNpcHandler(&deserialized_data, client);
                break;
            case SENDPLAYERCOMMAND:
                SendPlayerCommandHandler(&deserialized_data, client);
                break;
            case SENDPLAYERACTION:
                SendPlayerActionHandler(&deserialized_data, client);
                break;
            case SENDSERVERACTION:
                SendServerActionHandler(&deserialized_data, client);
                break;
            case UNITY:
                UnityHandler(&deserialized_data, client);
                break;
            default:
                std::cout << "Received unknown packet of type " << packetType << std::endl;
                break;
        }
    }
    shell.join();
    return;
}


// Returns the ip address and port number of the socket
std::string Server::GetIpAndPortFromSocket(sockaddr_in *socket){
    char host[100];
    char service[100];
    getnameinfo((sockaddr *)socket, sizeof(sockaddr), host, sizeof(host), service, sizeof(service), NI_NUMERICHOST);
    std::stringstream ss;
    ss << host << ":" << ntohs(socket->sin_port);
    return ss.str();
}


// return PTYPE or 0 on error
uint8_t Server::ReceiveDataFromClient(msgpack::object *data_out, sockaddr_in *client){
    char packet[PACKET_MAX_SIZE];
    int n = recvfrom(sockfd, packet, PACKET_MAX_SIZE, 0, (struct sockaddr *)client, &CLIENT_LEN);

    std::cout << "Received packet from " << GetIpAndPortFromSocket(client) << std::endl;

    uint8_t packetType = utils::GetPacketTypeFromPacket(packet);
    uint16_t msgpckSize = utils::GetMsgpckSizeFromPacket(packet);

    std::cout << "Packet type: " << (unsigned int) packetType << std::endl;
    std::cout << "Msgpack Size: " << msgpckSize << std::endl;

    // Check to make sure we don't accidentally access data outside the packet!
    if(msgpckSize > MSGPCK_MAX_PAYLOAD_SIZE){
        std::cout << "Msgpack Size is too large to be correct! Ignoring packet and continuing to avoid buffer overflow..." << std::endl;
        return false;
    }

    // Get msgpack data
    std::string msgpack_data = utils::GetMsgpckDataFromPacket(packet);
    std::cout << "Msgpack data: ";
    utils::PrintStringHex(&msgpack_data);

    // Use MessagePack to deserialize the payload, and return it in data_out
    *data_out = msgpack::unpack(msgpack_data.data(), msgpack_data.size()).get();
    std::cout << "Msgpack deserialized: ";
    std::cout << *data_out << std::endl;

    return packetType;
}


// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::GenericHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketGeneric packet;
    deserialized_data->convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::AckHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketAck packet;
    deserialized_data->convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.
void Server::ConnectHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketConnect packet;
    deserialized_data->convert(packet);

    // No need to check for session validity with connect requests

    PacketConnect returnPacket;
    returnPacket.sessionId = gameState->GenerateSession(packet.sessionId);
    // Use MessagePack to serialize data
    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);
    buffer.seekg(0);
    std::string str(buffer.str());
    // Add in header info - prepend the packet type and messagepack data size
    utils::PrependPacketHeader(&str, CONNECT);

    // Send the packet
    sendto(sockfd,(void*)str.data(),str.size(),0,(struct sockaddr *)&client,sizeof(client));
    std::cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << std::endl;
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::DisconnectHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketDisconnect packet;
    deserialized_data->convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    gameState->DisconnectSession(packet.sessionId);
}

void Server::ListCharactersHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketListcharacters packet;
    deserialized_data->convert(packet);
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
    buffer.seekg(0);
    std::string str(buffer.str());
    std::cout << "ListCharacters returnPacket msgpack data:" << std::endl;
    utils::PrintStringHex(&str);
    // Add in header info - prepend the packet type and messagepack data size
    utils::PrependPacketHeader(&str, LISTCHARACTERS);
    std::cout << "ListCharacters returnPacket header + msgpack data:" << std::endl;
    utils::PrintStringHex(&str);
    sendto(sockfd,str.data(),str.size(),0,(struct sockaddr *)&client,sizeof(client));
}

void Server::SelectCharacterHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketSelectcharacter packet;
    deserialized_data->convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    std::cout << "TODO: Need to select character " << packet.character << std::endl;
    // TODO: Select the requested character
    gameState->SelectPlayer(packet.sessionId);
}

void Server::DeleteCharacterHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "TODO: Delete Character handler!" << std::endl;
}

void Server::CreateCharacterHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketCreatecharacter packet;
    deserialized_data->convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }

    // TODO:
    std::cout << "TODO: Create character " << packet.lastName << ", " <<  packet.firstName << std::endl;
}

void Server::InitializeGameHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "InitializeGameHandler!" << std::endl;
}

void Server::UpdatePcHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "UpdatePcHandler!" << std::endl;
}

void Server::UpdateNpcHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "UpdateNpcHandler!" << std::endl;
}

void Server::SendPlayerCommandHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    PacketSendplayercommand packet;
    deserialized_data->convert(packet);
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

    // strcpy(returnPacket.command, temp.c_str());
    // sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_SENDSERVERCOMMAND), 0, (struct sockaddr *)&client, sizeof(client));

    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);
    buffer.seekg(0);
    std::string str(buffer.str());
    // Add in header info - prepend the packet type and messagepack data size
    utils::PrependPacketHeader(&str, SENDSERVERCOMMAND);
    sendto(sockfd,str.data(),str.size(),0,(struct sockaddr *)&client,sizeof(client));
}

void Server::SendPlayerActionHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "SendPlayerActionHandler!" << std::endl;
}

void Server::SendServerActionHandler(msgpack::object * deserialized_data, sockaddr_in client) {
    std::cout << "SendServerActionHandler!" << std::endl;
}


void Server::UnityHandler(msgpack::object * deserialized_data, sockaddr_in client) {
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
//     sendto(sockfd, (void *)&retPacket, sizeof(PACKET_UNITY), 0, (struct sockaddr *)&client, sizeof(client));
}