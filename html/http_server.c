#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

//HTTP SERVER

int main()
{
    //create and open a file pointer to hold the data
    FILE *html_data;
    html_data = fopen("index.html", "r");

    //store html file
    char response_data[1024];
    fgets(response_data, 1024, html_data); // REMEMBER to have html code in one line because fgets reads only one line at the time

    //create http header with a response
    char http_header[2048] = "HTTP/1.1 200 OK \r\n\n";
    strcat(http_header, response_data); // <-- to read the data


    //create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // same as in TCP version

    //define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    while(1){
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }


    return 0;
}
