
/* Sample UDP client */

#include <stdlib.h>
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
    char * server_address;

    // Read in server address from /text/server.txt
    server_address = argv[1];
    int port = atoi(argv[2]);
    cout << server_address << endl;
    cout << port << endl;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(server_address);
    servaddr.sin_port=htons(port);

    while (1){
      cin >> sendline;
      sendto(sockfd,sendline,1000,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
      //n = recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      //cout << recvline;
    }
}
