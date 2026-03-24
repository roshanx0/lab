/*
1. Start
2. Input number of frames (nf) and window size (N)
3. i = 1 (start from frame 1)
4. WHILE i <= nf:
   
   a) SEND all frames in window (i to i+N-1)
      count transmissions (tr++)
   
   b) CHECK ACK for each frame:
      - Generate random flag (0 or 1)
      - if flag == 0 → ACK received ✅ (x++)
      - if flag == 1 → Frame lost ❌
           Print "Not Received, Retransmitting Window"
           BREAK (resend whole window)
   
   c) Slide window: i += x
5. Print total transmissions
6. Stop
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int nf, N;
    int tr = 0;

    srand(time(NULL));

    printf("Enter the number of frames: ");
    scanf("%d", &nf);

    printf("Enter the Window Size: ");
    scanf("%d", &N);

    int i = 1;

    while (i <= nf) {
        int x = 0;

        // Send all frames in current window
        for (int j = i; j < i + N && j <= nf; j++) {
            printf("Sent Frame %d\n", j);
            tr++;
        }

        // Check ACK for each frame in window
        for (int j = i; j < i + N && j <= nf; j++) {
            int flag = rand() % 2;

            if (!flag) {
                // ACK received
                printf("%d: Acknowledged!\n", j);
                x++;
            } else {
                // Frame lost — resend entire window
                printf("Frame %d Not Received\n", j);
                printf("Retransmitting Window\n");
                break;
            }
        }

        printf("\n");
        i += x;  // slide window by successful ACKs
    }

    printf("Total number of transmissions: %d\n", tr);
    return 0;
}
  
