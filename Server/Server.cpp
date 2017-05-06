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
#include <queue>
#include <mutex>
#include <chrono>


Server::Server(int port) {
    sql = new SQLConnector();
    gameState = new GameState(sql);
    adminshell = new AdminShell(this, sql, gameState);

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

    // TODO: Do we want a limit on how many packets are in the queue?
    // Or at least emit a warning if the queue size surpasses a certain limit?
    // int MAX_PACKETS = 1000;
    int NUM_WORKER_THREADS = 10;

    // Initialize all the threads
    for (int i = 0; i < NUM_WORKER_THREADS; ++i) {
        // Start a thread on a Server member function
        // Funky syntax; server object needs to be second param
        // See http://stackoverflow.com/questions/10673585/start-thread-with-member-function
        std::thread t(&Server::WorkerThread, this, i);
        t.detach(); // Detach the threads so we don't need to join them manually
    }

    // // Set up a statistics thread, to monitor the server
    // std::thread statThread(&Server::StatisticsThread, this);
    // statThread.detach(); // Detach the threads so we don't need to join them manually


    bool listen = true;
    while(listen) {
        sockaddr_in client;
        packets::packet_t p;

        // Wait for a packet
        utils::ReceivePacketFrom(sockfd, p.data, &(p.source));

        // Put it in the packetQueue
        packetQueueMutex.lock();
        packetQueue.push(p);
        packetQueueMutex.unlock();
    }

    shell.join();
}


// TODO: This can be used to eventually log things to a file
// // Print out the size of the packetQueue every so often
// void Server::StatisticsThread() {
//     while(1){
//         // Get the size
//         int size = GetPacketQueueSize();
//         // Print out the size of the packet queue
//         std::cout << "packetQueue size: " << size << std::endl;
//         std::this_thread::sleep_for(std::chrono::milliseconds(200));
//     }
// }

int Server::GetPacketQueueSize() {
    packetQueueMutex.lock();
    int size = packetQueue.size();
    packetQueueMutex.unlock();
    return size;
}



void Server::WorkerThread(int id) {
    while(1){
        packets::packet_t packet;

        // Check to see if there are any packets to service
        packetQueueMutex.lock();
        if(packetQueue.size() > 0){
            // Retrieve a packet from the queue
            // std::cout << "Worker thread " << id << std::endl;
            // create a copy of the packet
            packet = packetQueue.front();
            packetQueue.pop();
            packetQueueMutex.unlock();
        }
        else{
            packetQueueMutex.unlock();
            // Since packetQueue is empty, try again in a few milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }


        msgpack::object_handle deserialized_data;
        uint8_t packetType;
        deserialized_data = utils::GetDataFromPacket(packet.data, &packetType);

        switch (packetType) {
            case false:
                std::cout << "Error receiving packet! Ignoring..." << std::endl;
                break;
            case packets::GENERIC:
                GenericHandler(&deserialized_data, &(packet.source));
                break;
            case packets::ACK:
                AckHandler(&deserialized_data, &(packet.source));
                break;
            case packets::CONNECT:
                ConnectHandler(&deserialized_data, &(packet.source));
                break;
            case packets::DISCONNECT:
                DisconnectHandler(&deserialized_data, &(packet.source));
                break;
            case packets::LISTCHARACTERS:
                ListCharactersHandler(&deserialized_data, &(packet.source));
                break;
            case packets::SELECTCHARACTER:
                SelectCharacterHandler(&deserialized_data, &(packet.source));
                break;
            case packets::DELETECHARACTER:
                DeleteCharacterHandler(&deserialized_data, &(packet.source));
                break;
            case packets::CREATECHARACTER:
                CreateCharacterHandler(&deserialized_data, &(packet.source));
                break;
            case packets::INITIALIZEGAME:
                InitializeGameHandler(&deserialized_data, &(packet.source));
                break;
            case packets::UPDATEPC:
                UpdatePcHandler(&deserialized_data, &(packet.source));
                break;
            case packets::UPDATENPC:
                UpdateNpcHandler(&deserialized_data, &(packet.source));
                break;
            case packets::SENDPLAYERCOMMAND:
                SendPlayerCommandHandler(&deserialized_data, &(packet.source));
                break;
            case packets::SENDPLAYERACTION:
                SendPlayerActionHandler(&deserialized_data, &(packet.source));
                break;
            case packets::SENDSERVERACTION:
                SendServerActionHandler(&deserialized_data, &(packet.source));
                break;
            case packets::UNITY:
                UnityHandler(&deserialized_data, &(packet.source));
                break;
            default:
                std::cout << "Received unknown packet of type " << packetType << std::endl;
                break;
        }
    }
}


// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::GenericHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Generic packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::AckHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Ack packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.
void Server::ConnectHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Connect packet;
    deserialized_data->get().convert(packet);

    // No need to check for session validity with connect requests

    packets::Connect returnPacket;
    returnPacket.sessionId = gameState->GenerateSession(packet.sessionId);
    returnPacket.packetId = 0;
    // Use MessagePack to serialize data
    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);

    // Send the packet
    utils::SendDataTo(sockfd, &buffer, packets::CONNECT, client);

    std::cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << std::endl;
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::DisconnectHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Disconnect packet;
    deserialized_data->get().convert(packet);
    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    gameState->DisconnectSession(packet.sessionId);
}

void Server::ListCharactersHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Listcharacters packet;
    // Wrap this is a try catch, so bad cast doesn't crash the whole server
    try {
        deserialized_data->get().convert(packet);
    } catch (const std::exception& e) {
        std::cout << "Failed to convert/cast msgpack object! Exiting... " << e.what() << std::endl;
        // Return error packet
        packets::Error returnPacket;
        // Since we couldn't convert/cast msgpack data, we don't know what sessionId or packetId it had
        returnPacket.sessionId = 0;
        returnPacket.packetId = 0;
        returnPacket.errorMsg = std::string("Failed to convert/cast msgpack object!");
        std::stringstream buffer;
        msgpack::pack(buffer, returnPacket);
        utils::SendDataTo(sockfd, &buffer, packets::ERROR, client);
        return;
    }

    if(!gameState->VerifySession(packet.sessionId)){
        // Quit early if invalid session
        std::cout << "Invalid session. Not doing anything" << std::endl;
        return;
    }
    std::string account = gameState->GetSessionAccountName(packet.sessionId);
    std::cout << "Account: " << account << " requested their character list." << std::endl;

    // TODO: Need to get an actual list of the player's characters

    packets::Listcharacters returnPacket;
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
    utils::SendDataTo(sockfd, &buffer, packets::LISTCHARACTERS, client);
}

void Server::SelectCharacterHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    packets::Selectcharacter packet;
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
    packets::Createcharacter packet;
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
    packets::Sendplayercommand packet;
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

    std::cout << server_response_s.str() << std::endl;


    packets::Sendservercommand returnPacket;
    returnPacket.sessionId = packet.sessionId;
    returnPacket.packetId = packet.packetId;
    returnPacket.command = server_response_s.str();

    std::stringstream buffer;
    msgpack::pack(buffer, returnPacket);
    utils::SendDataTo(sockfd, &buffer, packets::SENDSERVERCOMMAND, client);
}

void Server::SendPlayerActionHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "SendPlayerActionHandler!" << std::endl;
}

void Server::SendServerActionHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "SendServerActionHandler!" << std::endl;
}


void Server::UnityHandler(msgpack::object_handle * deserialized_data, sockaddr_in *client) {
    std::cout << "UnityHandler!" << std::endl;
}