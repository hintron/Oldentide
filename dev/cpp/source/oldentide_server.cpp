// Server meant to control data flow between client players and the 
// overarching game.  Based on a simple UDP socket design.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "character.h"
#include "oldentide.h"
using namespace std;

int main(int argc, char * argv[]){

    // Variable Declarations.
    int sockfd, n;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char mesg[1000];

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Cannot create socket...");
        return 0;
    }
    
    // Create server address struct.
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32000);

    // Bind socket to a port.
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Main listening loop.
    while(true){
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *)&cliaddr, &len);
        sendto(sockfd, mesg, n, 0, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
        printf("%s", mesg);
    }
}
