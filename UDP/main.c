#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>

// Server

// error: display an error message and exit     
void error(char *msg)
{
    perror(msg);
    exit(0);
}


int main(int argc, char *argv[])
{
    int sock, length, fromlen, n;
    struct sockaddr_in server; // server address structure
    struct sockaddr_in from;  // source address structure
    char buf[1024];

    // Port number must be passed as parameter 
    if(argc < 2){
        fprintf(stderr, "ERROR. No port provided\n");
        exit(0);
    }

    // Create a Datagram (UDP) socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        error("Opening socket...");
    }

    length = sizeof(server);

    bzero(&server, length);
    
    // Set the server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port=htons(atoi(argv[1]));

    // Bind the socket to the address
    if(bind(sock,(struct sockaddr *)&server,length)<0){

        error("Binding...");
    }
    fromlen = sizeof(struct sockaddr_in);

    // Infinite loop, receiving data and sending response
    while(1){
        
        /* Receive data from socket (recvfrom). Parameters are:
           - server socket
           - buffer to read data into
           - maximum buffer size
           - flags to control the receive operation
           - structure to store source address
           - source address length */ 
        
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        if(n<0){
            error("Recvfrom");
        }

        write(1, "Received a datagram: ",21);
        write(1,buf,n);
        
         /* Write data to socket (sendto). Parameters are:
          - server socket
          - data to write
          - length of data
          - flags to control send operation
          - destination address
          - length of destination address
          */
        
        n=sendto(sock, "Got your message\n",17,0,(struct sockaddr *)&from,fromlen);

        if(n<0){
            error ("Sendto");
        }

    }


    return 0;
}
