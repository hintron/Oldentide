// Filename:    TestClient.cpp
// Author:      Joseph DeVictoria
// Date:        2_10_2013
// Purpose:     Act as an intermediate test platform for proving server functionality.

#include "Packets.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

int main(int argc, char * argv[]){

    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    char * server_address;
    char * names[10];
    int session = 0;
    int packetNumber = 1;
    bool running = true;

    // Read in server address.
    server_address = argv[1];
    int port = atoi(argv[2]);
    cout << server_address << endl;
    cout << port << endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(port);

    while (running){
        cout << "Please choose a packet type to send:" << endl;
        cout << "0: GENERIC" << endl;
        cout << "1: ACK" << endl;
        cout << "2: CONNECT" << endl;
        cout << "3: DISCONNECT" << endl;
        cout << "4: LOGIN" << endl;
        cout << "5: LISTCHARACTERS" << endl;
        cout << "6: SELECTCHARACTER" << endl;
        cout << "7: DELETECHARACTER" << endl;
        cout << "8: CREATECHARACTER" << endl;
        cout << "9: INITIALIZEGAME" << endl;
        cout << "10: UPDATEPC" << endl;
        cout << "11: UPDATENPC" << endl;
        cout << "12: SENDPLAYERCOMMAND" << endl;
        cout << "13: SENDPLAYERACTION" << endl;
        cout << "14 SENDSERVERACTION" << endl;
        int packetType;
        cin >> packetType;
        switch (packetType){
            case 0: {
                PACKET_GENERIC packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 1: {
                PACKET_ACK packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 2: {
                PACKET_CONNECT packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                PACKET_CONNECT * returnPacket = (PACKET_CONNECT*) malloc(sizeof(PACKET_CONNECT));
                sockaddr_in servret;
                socklen_t len = sizeof(servret);
                int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&servret, &len);
                cout << "Given the session id: " << returnPacket->sessionId << endl;
                session = returnPacket->sessionId;
                free(returnPacket);
                break;
            }
            case 3: {
                PACKET_DISCONNECT packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 4: {
                PACKET_LOGIN packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                cout << "Account: ";
                cin.getline(packet.account, sizeof(packet.account));
                cout << "Password: ";
                cin.getline(packet.password, sizeof(packet.password));
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 5: {
                PACKET_LISTCHARACTERS packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 6: {
                PACKET_SELECTCHARACTER packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 7: {
                PACKET_DELETECHARACTER packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 8: {
                PACKET_CREATECHARACTER packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 9: {
                PACKET_INITIALIZEGAME packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 10: {
                PACKET_UPDATEPC packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 11: {
                PACKET_UPDATENPC packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 12: { 
                PACKET_SENDPLAYERCOMMAND packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                cin.getline(packet.command, sizeof(packet.command));
                cout << packet.command;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                running = false;
                break;
            }
            case 13: {
                PACKET_SENDPLAYERACTION packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 14: {
                PACKET_SENDSERVERACTION packet;
                packet.packetId = packetNumber;
                packet.sessionId = session;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
        }
    }
}
