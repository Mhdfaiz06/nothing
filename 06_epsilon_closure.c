/*Mohammed Faiz
S7 CSB 23
Exp 6
Epsilon Transition*/
#include <stdio.h>
#define MAX 20

int n;
int e[MAX][MAX];    // Epsilon transition matrix
int visited[MAX];

// Function to find epsilon closure using DFS
void epsilonClosure(int state)
{
    int i;
    visited[state] = 1;
    printf("q%d ", state);

    for(i = 0; i < n; i++)
    {
        if(e[state][i] && !visited[i])
        {
            epsilonClosure(i);
        }
    }
}

int main()
{
    int i, j, m;
    int from, to;

    printf("Enter number of states: ");
    scanf("%d", &n);

    // Initialize transition matrix
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            e[i][j] = 0;

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &m);

    printf("Enter epsilon transitions (from to):\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d %d", &from, &to);
        e[from][to] = 1;
    }

    printf("\nEpsilon Closures:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            visited[j] = 0;

        printf("ε-Closure(q%d) = { ", i);
        epsilonClosure(i);
        printf("}\n");
    }

    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
Enter number of states: 4
Enter number of epsilon transitions: 3
Enter epsilon transitions (from to):
0 1
1 2
3 1

Expected output:
Epsilon Closures:
ε-Closure(q0) = { q0 q1 q2 }
ε-Closure(q1) = { q1 q2 }
ε-Closure(q2) = { q2 }
ε-Closure(q3) = { q3 q1 q2 }
*/
