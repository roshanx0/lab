#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int seq_num;
    bool acked;
    bool sent;
} Packet;

int main() {
    int window_size, buffer_size;

    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);

    Packet packets[buffer_size];

    for (int i = 0; i < buffer_size; i++) {
        packets[i].seq_num = i;
        packets[i].acked = false;
        packets[i].sent = false;
    }

    int base = 0;
    int next_seq_num = 0;

    while (base < buffer_size) {

        /* Send packets within window */
        for (int i = base; i < base + window_size && i < buffer_size; i++) {
            if (!packets[i].sent) {
                printf("Sending packet with sequence number %d\n", i);
                packets[i].sent = true;
                next_seq_num++;
            }
        }

        /* Simulate ACK reception */
        for (int i = base; i < next_seq_num && i < buffer_size; i++) {
            if (!packets[i].acked) {
                double random_number = (double)rand() / RAND_MAX;

                if (random_number > 0.2) {
                    printf("Received acknowledgement for packet %d\n", i);
                    packets[i].acked = true;  // ← directly set here
                } else {
                    printf("Acknowledgement for packet %d lost\n", i);
                }
            }
        }

        /* Slide window */
        while (base < next_seq_num && packets[base].acked) {
            base++;
        }
    }

    printf("All packets have been acknowledged successfully\n");

    return 0;
}
