/*
1. Start

2. Input number of routers (n)

3. Input cost matrix (n x n)
   - If cost < 0 → replace with 1000 (infinity)

4. Input source router

5. Initialize:
   - dist[i]    = cost[src][i]  → direct costs from source
   - parent[i]  = src           → all parents set to source
   - visited[i] = 0             → all unvisited
   - visited[src] = 1           → mark source as visited

6. Repeat (n-1) times:
   a) Find unvisited node u with minimum dist
   b) Mark visited[u] = 1
   c) For every unvisited neighbor v:
      if dist[v] > dist[u] + cost[u][v]:
         dist[v]   = dist[u] + cost[u][v]
         parent[v] = u

7. For each router i:
   - Print path by tracing parent[] backwards
   - Print shortest path cost dist[i]

8. Stop

*/

#include <stdio.h>

int main() {

    int n, src;
    int cost[100][100];
    int dist[100];
    int visited[100];
    int parent[100];
    int i, j, u, v, min;

    // ---- INPUT ----
    printf("Enter the no. of routers: ");
    scanf("%d", &n);

    printf("Enter the cost matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if(cost[i][j] < 0)
                cost[i][j] = 1000;
        }
    }

    printf("Enter source router: ");
    scanf("%d", &src);

    // ---- INITIALIZATION ----
    for(i = 0; i < n; i++) {
        dist[i]    = cost[src][i];
        parent[i]  = src;
        visited[i] = 0;
    }
    visited[src] = 1;

    // ---- DIJKSTRA LOGIC ----
    for(i = 0; i < n - 1; i++) {

        min = 1000;

        // find nearest unvisited node
        for(j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        visited[u] = 1;

        // update distances through u
        for(v = 0; v < n; v++) {
            if(!visited[v] && dist[v] > min + cost[u][v]) {
                dist[v]   = min + cost[u][v];
                parent[v] = u;
            }
        }
    }

    // ---- OUTPUT ----
    for(i = 0; i < n; i++) {
        printf("\n%d ==> %d: Path taken: %d", src, i, i);

        v = i;
        while(v != src) {
            printf(" <-- %d", parent[v]);
            v = parent[v];
        }

        printf("\nShortest path cost: %d\n", dist[i]);
    }

    return 0;
}
