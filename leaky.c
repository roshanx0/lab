/*
1. Start
2. Initialize bucket_size, output_pkt_size
3. storage = 0
4. For each query (iteration):
   a) Get input_pkt_size
   b) size_left = bucket_size - storage
   c) If input fits (input <= size_left):
        storage += input_pkt_size  ✅
   d) Else (bucket overflow):
        add only what fits
        print packet loss        ❌
        storage = bucket_size
   e) Print current buffer size
   f) Drain: storage -= output_pkt_size
   g) If storage < 0 → storage = 0
   h) Print remaining after drain
5. Stop
*/
#include <stdio.h>

int main() {
    int no_of_queries, storage, output_pkt_size;
    int bucket_size, size_left;

    printf("Enter the number of queries: ");
    scanf("%d", &no_of_queries);

    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);

    printf("Enter the output packet size: ");
    scanf("%d", &output_pkt_size);

    storage = 0;

    for (int i = 0; i < no_of_queries; i++) {
        int input_pkt_size;
        printf("\nEnter the input packet size for iteration %d: ", i + 1);
        scanf("%d", &input_pkt_size);

        size_left = bucket_size - storage;

        if (input_pkt_size <= size_left) {
            // Packet fits in bucket
            storage += input_pkt_size;
        } else {
            // Bucket overflow — only partial packets added
            int packets_added = bucket_size - storage;
            printf("Bucket full! Only %d packets added. Packet loss = %d\n",
                   packets_added, input_pkt_size - packets_added);
            storage = bucket_size;
        }

        printf("Buffer size = %d out of bucket size = %d\n",
               storage, bucket_size);

        // Drain output at constant rate
        storage -= output_pkt_size;

        if (storage < 0) {
            storage = 0;
        }

        printf("Remaining packets in the bucket after output removal: %d\n",
               storage);
    }

    return 0;
}
