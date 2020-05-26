#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//TCP SERVER

int main()
{
    // create string to hold data

    char server_message[256] = "Witamy na serwerze!";

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //call bind function to bind socket to specified IP and port

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //call listen function to listen for connections

    listen(server_socket, 5);

    //create int to hold client socket

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    //send the message
    send(client_socket, server_message, sizeof(server_message), 0);

    //close socket
    close(server_socket);

    return 0;
}


