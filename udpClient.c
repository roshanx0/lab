/*
Start
Create UDP socket using socket()
Fill server address structure:
AF_INET
Server IP address
Port number
Read string from user
Send string to server using sendto()
Receive reversed string from server using recvfrom()
Display received string
Close socket
Stop
    */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 43454

int main() {
    int sfd;
    char buf[2048];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    printf("Enter a string: ");
    scanf("%[^\n]%*c", buf);

    // Send string (including null terminator to keep it clean)
    sendto(sfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&server, len);

    // Receive reversed string back
    recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&server, &len);

    printf("Server replied: %s\n", buf);

    close(sfd);
    return 0;
}
