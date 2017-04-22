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


using namespace std;

int main(int argc, char * argv[]) {

    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    char * server_address;
    char * names[10];
    int session = 0;
    int packetNumber = 1;
    bool running = true;
    string userAccount;

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

    int test_counter = 1337;
    std::string test_string("Test!");

    while (running) {
        switch (clientState) {
            // Initial State.
            case 0: {
                std::cout << "Connect? (Y/n) " << std::endl;
                string response;
                getline (cin, response);
                if ((response.compare("y") == 0) || (response.compare("Y") == 0) || (response.compare("") == 0)) {
                    PACKET_CONNECT packet;
                    packet.packetId = packetNumber;
                    packetNumber++;
                    packet.sessionId = session;


                    // Test out with a class of data (a struct)
                    TestData test = TestData{test_string, test_counter};
                    test_counter++;
                    test_string.append(1, '!');


                    // Use MessagePack to serialize data
                    std::stringstream buffer;
                    // msgpack::pack(buffer, packet);
                    msgpack::pack(buffer, test);
                    buffer.seekg(0);
                    std::string str(buffer.str());


                    utils::PrintStringHex(&str);

                    // Check to make sure that the msgpck data isn't too big
                    if(str.size() > PACKET_MAX_SIZE){
                        std::cout << "ERROR: Packet is larger than " << PACKET_MAX_SIZE << " bytes!!!!" << std::endl;
                    }


                    // Add in header info - prepend the packet type and messagepack data size
                    utils::PrependPacketHeader(&str, ACK);
                    // See what the packet looks like now
                    utils::PrintStringHex(&str);

                    // Send the packet
                    sendto(sockfd,(void*)str.data(),str.size(),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                    continue;

                    PACKET_CONNECT * returnPacket = (PACKET_CONNECT*) malloc(sizeof(PACKET_CONNECT));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&servret, &len);


                    // Convert to std::string so we can use it with messagepack
                    // std::string str2((char *)returnPacket, sizeof(PACKET_CONNECT));
                    // Use MessagePack to Deserialize the data
                    // msgpack::unpack(str2.data(), str2.size()).get().convert(*returnPacket);

                    // std::cout << "Connected! Given the session id: " << returnPacket->sessionId << std::endl;
                    // session = returnPacket->sessionId;
                    free(returnPacket);
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
                break;
            }
            // Logged In.
            case 2: {
                bool hasNoCharacter = true;
                while(hasNoCharacter) {
                    PACKET_LISTCHARACTERS packetListCharacters;
                    packetListCharacters.packetId = packetNumber;
                    packetNumber++;
                    packetListCharacters.sessionId = session;
                    sendto(sockfd,(void*)&packetListCharacters,sizeof(packetListCharacters),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_LISTCHARACTERS *characterList = (PACKET_LISTCHARACTERS*) malloc(sizeof(PACKET_LISTCHARACTERS));

                    // std::cout << "Character 1: " << characterList->character1 << std::endl;
                    if (std::string(characterList->character1) == "") {
                        std::cout << "You do not have any characters selected on this account" << std::endl;
                        std::cout << "Please give me a first name for your new character: ";
                        char firstName[25];
                        cin.getline(firstName, sizeof(firstName));
                        std::cout << "Please give me a last name for your new character: ";
                        char lastName[25];
                        cin.getline(lastName, sizeof(lastName));
                        PACKET_CREATECHARACTER newCharacter;
                        newCharacter.packetId = packetNumber;
                        packetNumber++;
                        newCharacter.sessionId = session;
                        strcpy(newCharacter.firstName, firstName);
                        strcpy(newCharacter.lastName, lastName);
                        sendto(sockfd,(void*)&newCharacter,sizeof(newCharacter),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    }
                    else {
                        // TODO: I think this loop might be broken
                        int count = 0;
                        bool notEmpty = true;
                        while (count < 25) {
                            char name[25];
                            switch (count) {
                                case 0:
                                    strcpy(name, characterList->character1);
                                    break;
                                case 1:
                                    strcpy(name, characterList->character2);
                                    break;
                                case 2:
                                    strcpy(name, characterList->character3);
                                    break;
                                case 3:
                                    strcpy(name, characterList->character4);
                                    break;
                                case 4:
                                    strcpy(name, characterList->character5);
                                    break;
                                case 5:
                                    strcpy(name, characterList->character6);
                                    break;
                                case 6:
                                    strcpy(name, characterList->character7);
                                    break;
                                case 7:
                                    strcpy(name, characterList->character8);
                                    break;
                                case 8:
                                    strcpy(name, characterList->character9);
                                    break;
                                case 9:
                                    strcpy(name, characterList->character10);
                                    break;
                            }
                            if (name != "") {
                                std::cout << "Character " << count << ": " << name << std::endl;
                                count++;
                            }
                            else {
                                notEmpty = false;
                            }
                        }
                    }
                } // End has no character while loop
                std::cout << "Please select a character: ";
                char name[25];
                cin.getline(name, sizeof(name));
                PACKET_SELECTCHARACTER selectCharacter;
                selectCharacter.sessionId = session;
                strcpy(selectCharacter.character, name);
                sendto(sockfd,(void*)&selectCharacter,sizeof(selectCharacter),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                clientState = 3;
                break;
            }
            // In game...
            case 3: {
                std::cout << userAccount << ": ";
                string command;
                getline(cin, command);
                if (command.empty()) {
                    break;
                }
                if (utils::Tokenfy(command, ' ')[0] == "/stress") {
                    PACKET_SENDPLAYERCOMMAND PlayerCommand;
                    PlayerCommand.sessionId = session;
                    for (int i = 0; i < 10000; i++) {
                        strcpy(PlayerCommand.command, ("/s " + std::to_string(i)).c_str());
                        sendto(sockfd,(void*)&PlayerCommand,sizeof(PlayerCommand),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    }
                }
                if (utils::Tokenfy(command, ' ')[0] != "/s") {
                    std::cout << "Please use a valid command!" << std::endl;
                    break;
                };
                PACKET_SENDPLAYERCOMMAND PlayerCommand;
                PlayerCommand.sessionId = session;
                strcpy(PlayerCommand.command, command.c_str());
                sendto(sockfd,(void*)&PlayerCommand,sizeof(PlayerCommand),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
        }
    }
}
