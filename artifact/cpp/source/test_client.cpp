
/* Sample UDP client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char * argv[]){

    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    char sendline[1000];
    char recvline[1000];
    ifstream servera;
    char * server_address;

    // Read in server address from /text/server.txt
    string line;
    servera.open("text/server.txt");
    getline(servera, line);
    server_address = (char*)line.c_str();
    cout << server_address << endl;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(server_address);//argv[1]);
    servaddr.sin_port=htons(32000);

    while (fgets(sendline, 10000,stdin) != NULL){
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      fputs(recvline,stdout);
    }
}
