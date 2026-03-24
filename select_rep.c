#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int seq_num;
    bool acked;
    bool sent;
} Packet;

/* Function to send packet */
void send_packet(Packet *packet) {
    printf("Sending packet with sequence number %d\n", packet->seq_num);
    sleep(1);
}

/* Function to receive acknowledgement */
void receive_ack(Packet *packet) {
    printf("Received acknowledgement for packet with sequence number %d\n", packet->seq_num);
    packet->acked = true;
}

int main() {
    int window_size, buffer_size;

    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);

    Packet packets[buffer_size];

    /* Initialize packets */
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
                send_packet(&packets[i]);
                packets[i].sent = true;
                next_seq_num++;
            }
        }

        /* Simulate ACK reception */
        for (int i = base; i < next_seq_num && i < buffer_size; i++) {
            if (!packets[i].acked) {
                double random_number = (double)rand() / RAND_MAX;

                if (random_number > 0.2) {
                    receive_ack(&packets[i]);
                } else {
                    printf("Acknowledgement for packet %d lost\n", packets[i].seq_num);
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
