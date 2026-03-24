/*SERVER:                        CLIENT:
1. Create UDP socket           1. Create UDP socket
2. Setup server address        2. Setup server address
3. Bind socket to port         3. Setup client address
4. Receive length from client  4. Enter string
5. Receive string from client  5. Send length to server
6. Reverse the string          6. Send string to server
7. Send length back            7. Receive length from server
8. Send reversed string back   8. Receive reversed string
9. Close socket                9. Print result
                               10. Close socket
💻 Full Program
🖥️ SERVER (server.c)*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define S_PORT 43454
#define ERROR -1

void strrev(char *str, int len) {
    int i, j;
    char temp;
    for (i = 0, j = len - 1; i < j; ++i, --j) {
        temp  = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int sfd, len;
    char str_buf[2048];
    struct sockaddr_in servaddr, clientaddr;
    socklen_t addrlen;

    // Create UDP socket
    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sfd == ERROR) {
        perror("Socket creation failed");
        return 1;
    }

    // Setup server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(S_PORT);

    // Bind
    if (bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("Bind failed");
        return 2;
    }

    printf("Server running...\n");

    addrlen = sizeof(clientaddr);

    // Receive length first
    recvfrom(sfd, &len, sizeof(len), 0,
             (struct sockaddr *)&clientaddr, &addrlen);

    // Receive string
    recvfrom(sfd, str_buf, len, 0,
             (struct sockaddr *)&clientaddr, &addrlen);

    str_buf[len] = '\0';
    printf("Received: %s\n", str_buf);

    // Reverse
    strrev(str_buf, len);

    // Send length back
    sendto(sfd, &len, sizeof(len), 0,
           (struct sockaddr *)&clientaddr, addrlen);

    // Send reversed string back
    sendto(sfd, str_buf, len, 0,
           (struct sockaddr *)&clientaddr, addrlen);

    close(sfd);
    return 0;
}
/*💻 CLIENT (client.c)*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define S_PORT 43454
#define C_PORT 43455
#define ERROR -1
#define IP_STR "127.0.0.1"

int main() {
    int sfd, len;
    char str_buf[2048];
    struct sockaddr_in servaddr, clientaddr;
    socklen_t addrlen;

    // Create UDP socket
    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sfd == ERROR) {
        perror("Socket creation failed");
        return 1;
    }

    // Setup client address
    memset(&clientaddr, 0, sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr(IP_STR);
    clientaddr.sin_port = htons(C_PORT);

    // Setup server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP_STR);
    servaddr.sin_port = htons(S_PORT);

    // Bind client
    if (bind(sfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) != 0) {
        perror("Bind failed");
        return 2;
    }

    // Enter string
    printf("Enter a string: ");
    scanf("%[^\n]%*c", str_buf);

    len = strlen(str_buf);

    // Send length first
    sendto(sfd, &len, sizeof(len), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Send string
    sendto(sfd, str_buf, len, 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    addrlen = sizeof(servaddr);

    // Receive length
    recvfrom(sfd, &len, sizeof(len), 0,
             (struct sockaddr *)&servaddr, &addrlen);

    // Receive reversed string
    recvfrom(sfd, str_buf, len, 0,
             (struct sockaddr *)&servaddr, &addrlen);

    str_buf[len] = '\0';
    printf("Server replied: %s\n", str_buf);

    close(sfd);
    return 0;
}
