/*
1. Start
2. Input number of nodes (n)
3. Read cost matrix (n x n)
   - Initialize routing table with direct costs
   - Distance to itself = 0
4. Calculate routing table (Bellman-Ford):
   For each node i:
     For each destination j:
       For each intermediate node k:
         if cost(i→k) + distance(k→j) < distance(i→j):
             update distance(i→j) = cost(i→k) + dist(k→j)
             update next hop = k
5. Display routing table for each router
6. Stop
  */
#include <stdio.h>

int costMatrix[20][20];
int n;

struct routers {
    int distance[20];
    int adjNodes[20];
} node[20];

void readCostMatrix() {
    int i, j;
    printf("\nEnter cost matrix:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &costMatrix[i][j]);

            // Initialize routing table
            node[i].distance[j] = costMatrix[i][j];
            node[i].adjNodes[j] = j;
        }
        costMatrix[i][i] = 0; // distance to itself = 0
    }
}

void calcRoutingTable() {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                // Bellman-Ford: is i→k→j shorter than i→j?
                if (node[i].distance[j] > costMatrix[i][k] + node[k].distance[j]) {
                    node[i].distance[j] = costMatrix[i][k] + node[k].distance[j];
                    node[i].adjNodes[j] = k;
                }
            }
        }
    }
}

void displayRoutes() {
    int i, j;

    for (i = 0; i < n; i++) {
        printf("\nRouter %d\n", i + 1);
        for (j = 0; j < n; j++) {
            printf("Node %d via %d : Distance %d\n",
                j + 1,
                node[i].adjNodes[j] + 1,
                node[i].distance[j]);
        }
    }
}

int main() {
    printf("Number of nodes: ");
    scanf("%d", &n);

    readCostMatrix();
    calcRoutingTable();
    displayRoutes();

    return 0;
}
