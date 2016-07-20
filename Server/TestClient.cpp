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
                PACKET_LOGIN packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                cout << "Account: ";
                cin.getline(packet.account, sizeof(packet.account));
                cout << "Password: ";
                cin.getline(packet.password, sizeof(packet.password));
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                PACKET_LOGIN * returnPacket = (PACKET_LOGIN*) malloc(sizeof(PACKET_LOGIN));
                sockaddr_in servret;
                socklen_t len = sizeof(servret);
                int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                if ((strcmp(returnPacket->account, packet.account)) == 0) {
                    cout << "Logged in as " << returnPacket->account << "!" << endl;
                    clientState = 2;
                }
                else {
                    cout << "Login Failed! Please try again." << endl;
                }
                free(returnPacket);
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
