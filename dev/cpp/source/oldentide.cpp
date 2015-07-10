/* A small project that I am starting to practice and learn better
 * c++ by trying to recreate the unique gameplay and system that was
 * used in Rubies of Eventide. -Joseph Lopez DeVictoria 2/9/2013 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include "oldentide.h"
#include "character.h"
#include "packet.h"
#define THANKSTOPBY "Thank you for stopping by, you are always welcome in Oldentide!"
#define PREVVORM "Have you previously entered the land of Vormis? (Yes/No)"
#define CACCNT "Would you like to create an Account? (Yes/No)"
using namespace std;


int main(){

    character* charLoad;
    int split1 = introPrint();
    switch (split1){
        case 0 : charLoad = goLogin(); 
	        break;
        case 1 : createCharacter("poop");
	        break;
        default : cout << THANKSTOPBY << endl << endl;
            return 0;
    }
    
    // Create first connection to the server and initialize session.
    int sockfd,n;
    char * server_address, * c_mesg;
    ifstream servera;
    struct sockaddr_in servaddr,cliaddr;
    
    // Read in server address from /text/server.txt
    string line;
    servera.open("text/server.txt");
    getline(servera, line);
    server_address = (char*)line.c_str();
    cout << server_address << endl;

    //Initialize socket connection
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(32000);

    packet start_packet("1", "test\r\n");
    string mesg = start_packet.returnPackedString();

    cout << mesg << endl;
    c_mesg = (char *)mesg.c_str();

    sendto(sockfd,c_mesg,strlen(c_mesg),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
    return 0;
}

string getFileContents (ifstream& File){
    string Lines = "";
    if (File){
	    while (File.good ()){
	        string TempLine;
	        getline (File , TempLine);
	        TempLine += "\n"; 
	        Lines += TempLine;
	    }
	    return Lines;
    }
    else{
	    return "ERROR File does not exist.";
    }
}

int introPrint(){
    string line = "empty";
    string previ;
    ifstream mainlogo;
    cout << endl << "               Hello, welcome to the world of:" << endl;
    mainlogo.open("text/mainlogo.txt");
    line = getFileContents(mainlogo);
    cout << line;
    mainlogo.close();
    cout << PREVVORM << endl;
    cin >> previ;
    previ[0] = toupper(previ[0]);
    while (previ != "Yes" && previ != "No"){
        cout << "Invalid option; " << PREVVORM << endl;
        cin >> previ;
        previ[0] = toupper(previ[0]);
    }
    if (previ == "Yes"){
        return 0;
    }
    else if (previ == "No"){
        previ = "empty";
        cout << CACCNT << endl;
        cin >> previ;
        previ[0] = toupper(previ[0]);
    }
    while (previ != "Yes" && previ != "No"){
        cout << "Invalid option; " << CACCNT << endl;
        cin >> previ;
        previ[0] = toupper(previ[0]);
    }
    if (previ == "Yes"){
        return 1;
    }
    else if (previ == "No"){
	    return 2; 
    }
    return 2;    
}

void createAccount(){

}

