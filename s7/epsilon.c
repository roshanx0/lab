/*
Start.
Read the number of states in the NFA.
Read the epsilon transition matrix.
Select each state one by one.
Mark the selected state as visited.
Add the selected state to its epsilon closure.
Check all epsilon transitions from the current state.
If an unvisited state is reachable through an epsilon transition, visit that state recursively.
Repeat until all reachable states have been visited.
Display the epsilon closure of the selected state.
Repeat the process for all states.
Stop.
0 1 1 0
0 0 1 0
0 0 0 1
0 0 0 0
*/

#include <stdio.h>

int n;
int e[20][20];   // epsilon transition matrix
int visited[20];

void epsilonClosure(int state)
{
    int i;

    visited[state] = 1;
    printf("q%d ", state);

    for(i = 0; i < n; i++)
    {
        if(e[state][i] && !visited[i])
            epsilonClosure(i);
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &e[i][j]);
        }
    }

    printf("\nEpsilon Closures:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            visited[j] = 0;

        printf("e-closure(q%d) = { ", i);
        epsilonClosure(i);
        printf("}\n");
    }

    return 0;
}
