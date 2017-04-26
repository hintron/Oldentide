// Filename:    TestClient.cpp
// Author:      Joseph DeVictoria
// Date:        2_10_2013
// Purpose:     Act as an intermediate test platform for proving server functionality.

#include "Packets.h"
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include "Utils.h"
#include <msgpack.hpp>
#include <sstream>

int main(int argc, char * argv[]) {

    int sockfd;
    struct sockaddr_in servaddr;
    char * server_address;
    int session = 0;
    int packetNumber = 1;
    bool running = true;
    std::string userAccount;

    // TODO: Parameter checking
    // Have parameter checking and exit gracefully if server address and port aren't specified
    if (argc != 3) {
        std::cout << "Invalid number of arguments passed to " << argv[0] << "; Exiting..." << std::endl;
        return 1;
    }

    // Read in server address.
    server_address = argv[1];
    std::cout << "Trying to connect to: " << server_address << std::endl;

    // For debug....
    struct hostent * he = gethostbyname(server_address);
    struct in_addr ** addr_list;
    addr_list = (struct in_addr **)he->h_addr_list;
    server_address = inet_ntoa(*addr_list[0]);

    int port = atoi(argv[2]);
    std::cout << server_address << std::endl;
    std::cout << port << std::endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(port);

    int clientState = 0;

    while (running) {
        switch (clientState) {
            // Initial State.
            case 0: {
                std::cout << "Connect? (Y/n) " << std::endl;
                std::string response;
                getline (std::cin, response);
                if ((response.compare("y") == 0) || (response.compare("Y") == 0) || (response.compare("") == 0)) {
                    PacketConnect packet;
                    packet.packetId = packetNumber;
                    packetNumber++;
                    packet.sessionId = session;

                    // Use MessagePack to serialize data
                    std::stringstream buffer;
                    msgpack::pack(buffer, packet);
                    utils::SendDataTo(sockfd, &buffer, CONNECT, &servaddr);

                    // Wait for a response
                    // TODO: Implement a timer

                    sockaddr_in servret;
                    uint8_t packetType;
                    msgpack::object_handle returnData = utils::ReceiveDataFrom(sockfd, &packetType, &servret);

                    std::cout << "Msgpack deserialized: ";
                    std::cout << returnData.get() << std::endl;

                    //// Test if it still works with stringstream
                    // std::stringstream asdf;
                    // asdf << "!!!!!!!!!!!!!!!!!!!!";

                    // NOTE! Currently, if you create a new stringstream, it messes up the msgpack data!
                    // Probably because we used a stringstream as the messagepack buffer
                    std::cout << "Received a packet from " << utils::GetIpAndPortFromSocket(&servret) << std::endl;

                    // // We are assuming that the return packet will always be on type CONNECT
                    if(packetType != CONNECT){
                        std::cout << "ERROR: Received packet other than CONNECT!! " << std::endl;
                        break;
                    }

                    // Use MessagePack to Deserialize the data
                    PacketConnect returnConnectPacket;
                    returnData.get().convert(returnConnectPacket);

                    std::cout << "Connected! Given the session id: " << returnConnectPacket.sessionId << std::endl;
                    // Set the session for the client
                    session = returnConnectPacket.sessionId;
                    clientState = 1;
                }
                else {
                    std::cout << "Shutting down!" << std::endl;
                    running = false;
                }
                break;
            }
            // Connected.
            case 1: {
                clientState = 2;
                std::cout << "Client State 2..." << std::endl;
                break;
            }
            // Logged In.
            case 2: {
                bool hasNoCharacter = true;

                while(hasNoCharacter) {
                    // Request a list of characters
                    PacketListcharacters p;
                    p.packetId = packetNumber;
                    packetNumber++;
                    p.sessionId = session;
                    // Send it using msgpack
                    std::stringstream buffer;
                    msgpack::pack(buffer, p);
                    buffer.seekg(0);
                    std::string str(buffer.str());
                    utils::PrependPacketHeader(&str, LISTCHARACTERS);
                    sendto(sockfd,(void*)str.data(),str.size(),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                    // Wait for the response
                    char returnPacket[PACKET_MAX_SIZE];
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, returnPacket, PACKET_MAX_SIZE, 0, (struct sockaddr *)&servret, &len);

                    std::string returnMsgpackData = utils::GetMsgpckDataFromPacket(returnPacket);

                    std::cout << "ListChars MessagePack data:" << std::endl;
                    utils::PrintStringHex(&returnMsgpackData);

                    PacketListcharacters characterList;
                    // Use MessagePack to Deserialize the data
                    msgpack::object deserialized = msgpack::unpack(returnMsgpackData.data(), returnMsgpackData.size()).get();
                    std::cout << "ListChars MessagePack deserialized:" << deserialized << std::endl;
                    deserialized.convert(characterList);

                    std::cout << "Number of available characters: " << characterList.characters.size() << std::endl;
                    if (characterList.characters.size() == 0) {
                        std::cout << "You do not have any characters selected on this account" << std::endl;
                        std::cout << "Please give me a first name for your new character: ";
                        std::string firstName;
                        std::getline(std::cin, firstName);
                        std::cout << firstName << std::endl;
                        std::cout << "Please give me a last name for your new character: ";
                        std::string lastName;
                        std::getline(std::cin, lastName);

                        PacketCreatecharacter newCharacter;
                        newCharacter.packetId = packetNumber;
                        packetNumber++;
                        newCharacter.sessionId = session;
                        newCharacter.firstName = firstName;
                        newCharacter.lastName = lastName;

                        std::stringstream buffer2;
                        msgpack::pack(buffer2, newCharacter);
                        buffer2.seekg(0);
                        std::string str2(buffer2.str());
                        utils::PrependPacketHeader(&str2, CREATECHARACTER);
                        sendto(sockfd,str2.data(),str2.size(),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                        // After creating the new character, loop back to the top
                        // and send a new request for the list of players.
                        // If the create was successful, then there should be a haracter
                    }
                    else {
                        hasNoCharacter = false;
                        for (int i = 0; i < characterList.characters.size(); ++i) {
                            if(characterList.characters.at(i) != ""){
                                std::cout << "Character " << i << ": " << characterList.characters.at(i) << std::endl;
                            }
                        }
                    }
                } // End has no character while loop
                std::cout << "Please select a character: " << std::endl;

                std::string name;
                getline(std::cin, name);
                std::cout << "TODO: Attempting to select character " << name << ": " << std::endl;

                PacketSelectcharacter characterToSelect;
                characterToSelect.packetId = packetNumber;
                packetNumber++;
                characterToSelect.sessionId = session;
                characterToSelect.character = name;

                std::stringstream buffer;
                msgpack::pack(buffer, characterToSelect);
                buffer.seekg(0);
                std::string str(buffer.str());
                utils::PrependPacketHeader(&str, SELECTCHARACTER);
                sendto(sockfd,str.data(),str.size(),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                clientState = 3;
                break;
            }
            // In game...
            case 3: {
                std::cout << "Send commands to the server!" << std::endl;
                // TODO: Get user account value
                std::cout << userAccount << ": ";
                std::string command;
                getline(std::cin, command);
                if (command.empty()) {
                    break;
                }

                // if (utils::Tokenfy(command, ' ')[0] == "/stress") {
                // if (utils::Tokenfy(command, ' ')[0] == "/s") {
                // }

                PacketSendplayercommand PlayerCommand;
                PlayerCommand.packetId = packetNumber;
                packetNumber++;
                PlayerCommand.sessionId = session;
                // PlayerCommand.command = std::string("/s " + command);
                PlayerCommand.command = std::string(command);

                std::stringstream buffer;
                msgpack::pack(buffer, PlayerCommand);
                buffer.seekg(0);
                std::string str(buffer.str());
                utils::PrependPacketHeader(&str, SENDPLAYERCOMMAND);
                sendto(sockfd,str.data(),str.size(),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                break;
            }
        }
    }
}
