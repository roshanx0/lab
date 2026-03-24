/*
1. Start
2. Input number of frames
3. For each frame:
   a) Send the frame
   b) Generate random number
   c) If random is EVEN (ACK lost):
        - Wait 1, 2, 3 seconds (timeout simulation)
        - Print "Missing ACK"
        - Resend frame
        - Receive ACK, print ACK number
   d) If random is ODD (ACK received):
        - Directly receive ACK
        - Print ACK number
   e) Move to next frame
4. Print "End of Stop and Wait Protocol"
5. Stop
    
    */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    int i = 0, j = 0, noframes, x, x2, n;

    printf("Enter number of frames: ");
    scanf("%d", &noframes);

    n = noframes;
    srand(time(NULL));

    while (noframes > 0) {

        printf("\nSending frame %d", i);

        x = rand() % 10;

        if (x % 2 == 0) {
            for (x2 = 1; x2 <= 3; x2++) {
                printf("\nWaiting for %d seconds", x2);
                sleep(x2);
            }
            printf("\nMissing Acknowledgement for frame %d", i);
            printf("\nResending frame %d", i);
            printf("\nACK received for frame %d", i);
            if (j < n) {
                printf("\nACK number %d", j);  // ✅ print before increment
            }
            j++;

        } else {
            printf("\nACK received for frame %d", i);
            if (j < n) {
                printf("\nACK number %d", j);  // ✅ print before increment
            }
            j++;
        }

        noframes--;
        i++;
    }

    printf("\nEnd of stop and wait protocol\n");
    return 0;
}
