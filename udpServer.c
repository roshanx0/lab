#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 43454

int main() {
    int sfd;
    char buf[2048];
    struct sockaddr_in serv, cli;
    socklen_t len = sizeof(cli);

    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    bind(sfd, (struct sockaddr *)&serv, sizeof(serv));
    printf("Server listening...\n");

    while (1) { // Keeps server alive for multiple requests
        // 1. Receive the string directly (includes \0)
        int n = recvfrom(sfd, buf, sizeof(buf), 0, (struct sockaddr *)&cli, &len);
        if (n <= 0) continue;

        printf("Received: %s\n", buf);

        // 2. Reverse the string in-place
        int i = 0, j = strlen(buf) - 1;
        while (i < j) {
            char temp = buf[i];
            buf[i++] = buf[j];
            buf[j--] = temp;
        }

        // 3. Send reversed string back
        sendto(sfd, buf, n, 0, (struct sockaddr *)&cli, len);
    }

    close(sfd);
    return 0;
}