// Filename:    TestClient.cpp
// Author:      Joseph DeVictoria
// Date:        2_10_2013
// Purpose:     Act as an intermediate test platform for proving server functionality.

#include "Packets.h"
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include "LoginManager.h"
#include "Utils.h"

using namespace std;

int main(int argc, char * argv[]){

    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    char * server_address;
    char * names[10];
    int session = 0;
    int packetNumber = 1;
    bool running = true;

    // TODO: Parameter checking
    // Have parameter checking and exit gracefully if server address and port aren't specified
    if(argc != 3){
        cout << "Invalid number of arguments passed to " << argv[0] << "; Exiting..." << endl;
        return 1;
    }

    // Read in server address.
    server_address = argv[1];
    int port = atoi(argv[2]);
    cout << server_address << endl;
    cout << port << endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(port);

    int clientState = 0;

    while (running){
        switch (clientState){
            // Initial State.
            case 0: {
                cout << "Connect? (Y/N) " << endl;
                string response;
                getline (cin, response);
                if ((response.compare("y") == 0) || (response.compare("Y") == 0)){
                    PACKET_CONNECT packet;
                    packet.packetId = packetNumber;
                    packetNumber++;
                    packet.sessionId = session;
                    sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_CONNECT * returnPacket = (PACKET_CONNECT*) malloc(sizeof(PACKET_CONNECT));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&servret, &len);
                    cout << "Connected! Given the session id: " << returnPacket->sessionId << endl;
                    session = returnPacket->sessionId;
                    free(returnPacket);
                    clientState = 1;
                }
                else {
                    cout << "Shutting down!" << endl;
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
                cout << "Account: ";
                cin.getline(packetSalt.account, sizeof(packetSalt.account));
                if(!Utils::sanitize_account_name(packetSalt.account)){
                    cout << "Invalid account name!" << endl;
                    break;
                }
                sendto(sockfd,(void*)&packetSalt,sizeof(packetSalt),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                PACKET_GETSALT *returnPacketSalt = (PACKET_GETSALT*) malloc(sizeof(PACKET_GETSALT));
                sockaddr_in servretSalt;
                socklen_t lenSalt = sizeof(servretSalt);
                int n = recvfrom(sockfd, (void *)returnPacketSalt, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&servretSalt, &lenSalt);
                cout << "Account retrieved from get salt:" << returnPacketSalt->account << endl;
                cout << "Account on hand:" << packetSalt.account << endl;
                if ((strcmp(returnPacketSalt->account, packetSalt.account)) == 0) {
                    cout << "Account exists! Recieved salt, calculating key..." << endl;
                    // Second packet - calculate key from salt and send key and account name
                    PACKET_LOGIN packetLogin;
                    packetLogin.packetId = packetNumber;
                    packetLogin.sessionId = session;
                    strcpy(packetLogin.account, packetSalt.account);
                    cout << "Password: ";
                    // TODO: Get a system-wide define for max password length
                    // TODO: Is there any way to allocate only what is needed?
                    // TODO: How to make password size match the length of the password?
                    char password[1000];
                    cin.getline(password, sizeof(password));
                    if(!Utils::check_password_length(password)){
                        break;
                    }
                    // TODO: Salt here is not showing up sometimes! Get it to reliably show up!!
                    cout << "Salt used in login generating key: " << returnPacketSalt->saltStringHex << endl;
                    // TODO: keyStringHex is not being correctly passed from generate_key() to keyStringHex!
                    LoginManager::generate_key((char *)password, (char *)returnPacketSalt->saltStringHex, (char *) packetLogin.keyStringHex);
                    //strcpy(packetLogin.keyStringHex, generated_key_string_hex);
                    cout << "Generated key used for login: " << packetLogin.keyStringHex << endl;
                    sendto(sockfd,(void*)&packetLogin,sizeof(packetLogin),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_LOGIN * returnPacket = (PACKET_LOGIN*) malloc(sizeof(PACKET_LOGIN));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                    if ((strcmp(returnPacket->account, packetLogin.account)) == 0) {
                        cout << "Logged in as " << returnPacket->account << "!" << endl;
                        cout << "(" << packetLogin.account << ")" << endl;
                        //clientState = 2;
                    }
                    else {
                        cout << "Login Failed! Please try again." << endl;
                    }
                    free(returnPacket);
                }
                else {
                    cout << "Account doesn't exist..." << endl;
                    cout << "Did you want to create a new account called " << packetSalt.account << "? (Y/N) " << endl;
                    string response;
                    getline (cin, response);
                    if ((response.compare("y") == 0) || (response.compare("Y") == 0)){
                        char password[1000];
                        char password2[1000];
                        bool repeat_try; 
                        do {
                            repeat_try = false;
                            cout << "Enter password, or press c to cancel: ";
                            // TODO: Get a system-wide define for max password length
                            // TODO: Is there any way to allocate only what is needed?
                            // TODO: How to make password size match the length of the password?
                            cin.getline(password, sizeof(password));
                            if(strcmp(password, "c") == 0){
                                continue;
                            }
                            cout << "Repeat password: ";
                            cin.getline(password2, sizeof(password2));
                            if(strcmp(password, password2) != 0){
                                cout << "Passwords were not the same... Please retype the password" << endl;                                repeat_try = true;
                                continue; 
                            }
                            if(!Utils::check_password_length(password)){
                                cout << "Password needs to be at least 8 characters... Please choose a different password" << endl;
                                repeat_try = true;
                                continue;
                            }
                            // If user made it this far, then password must be good
                            // Start assembling the create account packet
                            PACKET_CREATEACCOUNT packetCreate;
                            packetCreate.packetId = packetNumber;
                            packetCreate.sessionId = session;
                            strcpy(packetCreate.account, packetSalt.account);
                            LoginManager::generate_salt_and_key(password, packetCreate.saltStringHex, packetCreate.keyStringHex);
                            sendto(sockfd,(void*)&packetCreate,sizeof(packetCreate),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                            cout << "New account created (hopefully)" << endl;
                            // TODO: Print success if account was successfully created
                            //PACKET_LOGIN * returnPacket = (PACKET_LOGIN*) malloc(sizeof(PACKET_LOGIN));
                            //sockaddr_in servret;
                            //socklen_t len = sizeof(servret);
                            //int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                            // END Create account
                        }
                        while(repeat_try);
                    }
                }
                free(returnPacketSalt);
                break;
            }
            // Logged In.
            case 2: {
                running = false;
                break;
            }
            // 
            case 3: {
            }
        }
    }
}
