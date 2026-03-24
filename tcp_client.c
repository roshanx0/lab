#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock, port;
    struct sockaddr_in server;
    char msg[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));
    printf("\nClient connected\n");

    printf("Enter message: ");
    scanf("%s", msg);

    write(sock, msg, strlen(msg));

    read(sock, msg, sizeof(msg));
    printf("From server: %s\n", msg);

    close(sock);
    return 0;
}
