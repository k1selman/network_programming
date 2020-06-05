#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

void error(char *);

int main(int argc, char *argv[]){
    int sock, length, n;
    struct sockaddr_in server, from; //IP Addressing(ip, port, type) Stuff
    struct hostent *hp; //DNS stuff
    char buffer[256];

    if(argc!=3){
        printf("Usage: server port\n");
        exit(1);
    }
    
    // The socket() call creates a socket in the specified domain and of the specified type.
    // AF_INET is the protocol family for Internet domain
    // The following creates a datagram socket for intramachine use
    sock = socket(AF_INET, SOCK_DGRAM, 0); 
    //

    if(sock<0){
        error("Socket");
    }

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);

    if(hp == 0){
        error("Unknown host");
    }

    bcopy((char*)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    length = sizeof(struct sockaddr_in);

    printf("Please enter the message: ");

    bzero(buffer, 256);
    fgets(buffer, 256, stdin);
    n = sendto(sock, buffer, strlen(buffer), 0, &server, length);
    if(n<0){
        error ("Sendto");
    }
    n = recvfrom(sock,buffer,256,0,&from,&length);
    if(n<0){
        error("recvfrom");
    }

    write(1,"Got an ack: ",12);
    write(1,buffer,n);


    return 0;

}
