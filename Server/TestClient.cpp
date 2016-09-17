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
#include "LoginManager.h"
#include "Utils.h"
#include <thread>
#include <chrono>

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

    while (running) {
        switch (clientState) {
            // Initial State.
            case 0: {
                std::cout << "Connect? (Y/N) " << std::endl;
                string response;
                getline (cin, response);
                if ((response.compare("y") == 0) || (response.compare("Y") == 0)) {
                    PACKET_CONNECT packet;
                    packet.packetId = packetNumber;
                    packetNumber++;
                    packet.sessionId = session;
                    sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_CONNECT * returnPacket = (PACKET_CONNECT*) malloc(sizeof(PACKET_CONNECT));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&servret, &len);
                    std::cout << "Connected! Given the session id: " << returnPacket->sessionId << std::endl;
                    session = returnPacket->sessionId;
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
                // First packet - check if account exists and get salt
                PACKET_GETSALT packetSalt;
                packetSalt.packetId = packetNumber;
                packetSalt.sessionId = session;
                std::cout << "Account: ";
                cin.getline(packetSalt.account, sizeof(packetSalt.account));
                if (!utils::SanitizeAccountName(packetSalt.account)) {
                    std::cout << "Invalid account name!" << std::endl;
                    break;
                }
                sendto(sockfd,(void*)&packetSalt,sizeof(packetSalt),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                PACKET_GETSALT *returnPacketSalt = (PACKET_GETSALT*) malloc(sizeof(PACKET_GETSALT));
                sockaddr_in servretSalt;
                socklen_t lenSalt = sizeof(servretSalt);
                int n = recvfrom(sockfd, (void *)returnPacketSalt, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&servretSalt, &lenSalt);
                std::cout << "Account retrieved from get salt:" << returnPacketSalt->account << std::endl;
                std::cout << "Account on hand:" << packetSalt.account << std::endl;
                if ((strcmp(returnPacketSalt->account, packetSalt.account)) == 0) {
                    std::cout << "Account exists! Recieved salt, calculating key..." << std::endl;
                    // Second packet - calculate key from salt and send key and account name
                    PACKET_LOGIN packetLogin;
                    packetLogin.packetId = packetNumber;
                    packetLogin.sessionId = session;
                    strcpy(packetLogin.account, packetSalt.account);
                    std::cout << "Password: ";
                    // TODO: Get a system-wide define for max password length
                    // TODO: Is there any way to allocate only what is needed?
                    // TODO: How to make password size match the length of the password?
                    char password[1000];
                    cin.getline(password, sizeof(password));
                    if (!utils::CheckPasswordLength(password)) {
                        break;
                    }
                    std::cout << "Salt used in login generating key: " << returnPacketSalt->saltStringHex << std::endl;
                    LoginManager::GenerateKey((char *)password, (char *)returnPacketSalt->saltStringHex, (char *) packetLogin.keyStringHex);
                    std::cout << "Generated key used for login: " << packetLogin.keyStringHex << std::endl;
                    sendto(sockfd,(void*)&packetLogin,sizeof(packetLogin),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_LOGIN * returnPacket = (PACKET_LOGIN*) malloc(sizeof(PACKET_LOGIN));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                    if ((strcmp(returnPacket->account, packetLogin.account)) == 0) {
                        std::cout << "Logged in as " << returnPacket->account << "!" << std::endl;
                        userAccount = returnPacket->account;
                        std::cout << "(" << packetLogin.account << ")" << std::endl;
                        // Now that user is logged in, start up client console
                        clientState = 2;
                    }
                    else {
                        std::cout << "Login Failed! Please try again." << std::endl;
                    }
                    free(returnPacket);
                }
                else {
                    std::cout << "Account doesn't exist..." << std::endl;
                    std::cout << "Did you want to create a new account called " << packetSalt.account << "? (Y/N) " << std::endl;
                    string response;
                    getline(cin, response);
                    if ((response.compare("y") == 0) || (response.compare("Y") == 0)) {
                        char password[1000];
                        char password2[1000];
                        bool repeat_try;
                        do {
                            repeat_try = false;
                            std::cout << "Enter password, or press c to cancel: ";
                            // TODO: Get a system-wide define for max password length
                            // TODO: Is there any way to allocate only what is needed?
                            // TODO: How to make password size match the length of the password?
                            cin.getline(password, sizeof(password));
                            if (strcmp(password, "c") == 0) {
                                continue;
                            }
                            std::cout << "Repeat password: ";
                            cin.getline(password2, sizeof(password2));
                            if (strcmp(password, password2) != 0) {
                                std::cout << "Passwords were not the same... Please retype the password" << std::endl;                                
                                repeat_try = true;
                                continue;
                            }
                            if (!utils::CheckPasswordLength(password)) {
                                std::cout << "Password needs to be at least 8 characters... Please choose a different password" << std::endl;
                                repeat_try = true;
                                continue;
                            }
                            // If user made it this far, then password must be good
                            // Start assembling the create account packet
                            PACKET_CREATEACCOUNT packetCreate;
                            packetCreate.packetId = packetNumber;
                            packetCreate.sessionId = session;
                            strcpy(packetCreate.account, packetSalt.account);
                            LoginManager::GenerateSaltAndKey(password, packetCreate.saltStringHex, packetCreate.keyStringHex);
                            sendto(sockfd,(void*)&packetCreate,sizeof(packetCreate),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                            // Print success if account was successfully created
                            PACKET_CREATEACCOUNT *returnPacket = (PACKET_CREATEACCOUNT*) malloc(sizeof(PACKET_CREATEACCOUNT));
                            sockaddr_in servret;
                            socklen_t len = sizeof(servret);
                            int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                            if ((strcmp(returnPacket->account, packetCreate.account)) == 0) {
                                std::cout << "New account \"" << returnPacket->account << "\" successfully created!" << std::endl;
                            }
                            else {
                                std::cout << "New account \"" << packetCreate.account << "\" failed to create..." << std::endl;
                            }
                            free(returnPacket);
                        }
                        while(repeat_try);
                    }
                }
                free(returnPacketSalt);
                break;
            }
            // Logged In.
            case 2: {
                std::cout << "Selecting a character would happen here..." << std::endl;
                PACKET_SELECTCHARACTER selectCharacter;
                selectCharacter.sessionId = session;
                strcpy(selectCharacter.character, "Poopymouth");
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
