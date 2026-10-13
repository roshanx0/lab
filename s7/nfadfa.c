/*
Start.
Read the number of NFA states.
Read the number of input symbols.
Read the NFA transition table.
Take q0 as the initial state.
Represent the initial DFA state as the set {q0}.
For each DFA state, find the transitions for every input symbol.
Combine the NFA destinations of all states included in the current DFA state.
Treat the resulting set as a new DFA state.
Check whether the new set already exists.
If it does not exist, add it to the DFA state list.
Repeat until every discovered DFA state has been processed.
Display the DFA transition table.
Stop.
*/


#include <stdio.h>

int main()
{
    int n, m, i, j;
    int trans[10][10][10];
    int dfa[20][10] = {0};
    int states = 1;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter NFA transition table:\n");
    printf("(Enter destination states as 0 or 1)\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("q%d on symbol %d:\n", i, j);

            for(int k = 0; k < n; k++)
            {
                scanf("%d", &trans[i][j][k]);
            }
        }
    }

    /* Initial DFA state is {q0} */
    dfa[0][0] = 1;

    printf("\nDFA Transition Table:\n");

    for(i = 0; i < states; i++)
    {
        for(j = 0; j < m; j++)
        {
            int result[10] = {0};
            int k, x, found = 0;

            /* Find all destinations */
            for(k = 0; k < n; k++)
            {
                if(dfa[i][k])
                {
                    for(x = 0; x < n; x++)
                    {
                        if(trans[k][j][x])
                            result[x] = 1;
                    }
                }
            }

            printf("{");
            for(k = 0; k < n; k++)
                if(dfa[i][k])
                    printf("q%d ", k);

            printf("} --%d--> {", j);

            for(k = 0; k < n; k++)
                if(result[k])
                    printf("q%d ", k);

            printf("}\n");

            /* Check whether this DFA state exists */
            for(x = 0; x < states; x++)
            {
                int same = 1;

                for(k = 0; k < n; k++)
                {
                    if(dfa[x][k] != result[k])
                        same = 0;
                }

                if(same)
                    found = 1;
            }

            /* Add a new DFA state if needed */
            if(!found && states < 20)
            {
                for(k = 0; k < n; k++)
                    dfa[states][k] = result[k];

                states++;
            }
        }
    }

    return 0;
}
