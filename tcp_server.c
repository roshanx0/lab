/*
SERVER:                          CLIENT:
1. Create socket                 1. Create socket
2. Bind to port                  2. Enter port number
3. Listen for connections        3. Connect to server (127.0.0.1)
4. Accept client                 4. Enter message
5. Read message from client      5. Send message
6. Reverse the string            6. Read reversed message
7. Send reversed back            7. Print result
8. Close sockets                 8. Close socket
*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int serversocket, clientsocket, port, n;
    struct sockaddr_in server, client;
    socklen_t len;

    char msg[100];

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;

    printf("Enter port number: ");
    scanf("%d", &port);

    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr *)&server, sizeof(server));

    listen(serversocket, 5);

    printf("Waiting for client...\n");

    len = sizeof(client);

    clientsocket = accept(serversocket,
                          (struct sockaddr *)&client,
                          &len);

    printf("Client connected\n");

    n = read(clientsocket, msg, sizeof(msg) - 1);
    msg[n] = '\0';

    printf("Message from client: %s\n", msg);

    int start = 0;
    int end = strlen(msg) - 1;

    while(start < end)
    {
        char temp = msg[start];
        msg[start] = msg[end];
        msg[end] = temp;

        start++;
        end--;
    }

    write(clientsocket, msg, strlen(msg));

    printf("Reversed string sent\n");

    close(clientsocket);
    close(serversocket);

    return 0;
}
}
