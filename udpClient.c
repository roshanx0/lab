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
    struct sockaddr_in serv;
    socklen_t len = sizeof(serv);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(PORT);

    printf("Enter a string: ");
    scanf("%[^\n]%*c", buf);

    // Send string (including null terminator to keep it clean)
    sendto(sfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&serv, len);

    // Receive reversed string back
    recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&serv, &len);

    printf("Server replied: %s\n", buf);

    close(sfd);
    return 0;
}