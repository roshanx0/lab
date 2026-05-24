/*
Start
Create UDP socket using socket()
Fill server address structure:
AF_INET
IP address
Port number
Bind socket to server address using bind()
Wait for message from client using recvfrom()
Receive string from client
Reverse the string
Send reversed string back using sendto()
Repeat steps 5–8 continuously (optional using while(1))
Close socket
Stop

*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 43454

int main() {
    int sfd;
    char buf[2048];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // Create UDP socket
    sfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Fill server address structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    // Bind socket
    bind(sfd, (struct sockaddr *)&server, sizeof(server));

    printf("Server listening...\n");

    while (1) {

        // Receive string from client
        int n = recvfrom(sfd, buf, sizeof(buf), 0,
                         (struct sockaddr *)&client, &len);

        if (n <= 0)
            continue;

        printf("Received: %s\n", buf);

        // Reverse string
        int i = 0, j = strlen(buf) - 1;

        while (i < j) {
            char temp = buf[i];
            buf[i] = buf[j];
            buf[j] = temp;

            i++;
            j--;
        }

        // Send reversed string back
        sendto(sfd, buf, n, 0,
               (struct sockaddr *)&client, len);
    }

    close(sfd);

    return 0;
}
