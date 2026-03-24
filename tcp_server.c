#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char message[100];

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 5);

    len = sizeof(clientaddr);
    printf("\nWaiting for client connection\n");
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);
    printf("\nClient connected\n");

    read(clientsocket, message, sizeof(message));
    printf("\nReceived from client: %s\n", message);

    // Reverse the string
    int start = 0, end = strlen(message) - 1;
    while (start < end) {
        char temp = message[start];
        message[start] = message[end];
        message[end] = temp;
        start++;
        end--;
    }

    write(clientsocket, message, sizeof(message));
    printf("\nReversed message sent to client\n");

    close(clientsocket);
    close(serversocket);

    return 0;
}
