// Filename:    TestClient.cpp
// Author:      Joseph DeVictoria
// Date:        2_10_2013
// Purpose:     Act as an intermediate test platform for proving server functionality.

#include "Packets.h"
#include <arpa/inet.h>
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

    // Read in server address.
    server_address = argv[1];
    int port = atoi(argv[2]);
    cout << server_address << endl;
    cout << port << endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(port);

    while (1){
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
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 1: {
                PACKET_ACK packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 2: {
                PACKET_CONNECT packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 3: {
                PACKET_DISCONNECT packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 4: {
                PACKET_LOGIN packet;
                cout << "Account: ";
                cin >> packet.account;
                cout << "Password: ";
                cin >> packet.password;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 5: {
                PACKET_LISTCHARACTERS packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 6: {
                PACKET_SELECTCHARACTER packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 7: {
                PACKET_DELETECHARACTER packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 8: {
                PACKET_CREATECHARACTER packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 9: {
                PACKET_INITIALIZEGAME packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 10: {
                PACKET_UPDATEPC packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 11: {
                PACKET_UPDATENPC packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 12: {
                PACKET_SENDPLAYERCOMMAND packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 13: {
                PACKET_SENDPLAYERACTION packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
            case 14: {
                PACKET_SENDSERVERACTION packet;
                sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                break;
            }
        }
    }
}
