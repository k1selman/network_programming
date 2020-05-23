
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

//TCP CLIENT

int main()
{
    //create socket
    //create integer to hold socket descriptor - contains information about socket

    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // <-- this creates network socket

    //create address structure
    //specify an address for the socket

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; //family of the address
    server_address.sin_port = htons(9002); //specify the port

    //specify the address to connect to

    server_address.sin_addr.s_addr = INADDR_ANY; // same as 0.0.0.0

    int connection_status = connect(network_socket, (struct sockaddr * ) &server_address, sizeof(server_address)); //if 0 - ok, if -1 - cannot connect properly

    //check for error in the connection

    if(connection_status == -1)
    {
        printf("Wystapil blad polaczenia do socketu... \n");
    }

    //recieve data from the server

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out server response

    printf("Serwer wyslal dane %s\n", server_response);

    //close socket

    close(network_socket);

    return 0;
}
