/*Mohammed Faiz
S7 CSB 23
Exp 6
Epsilon Transition (short version)*/
#include <stdio.h>
int n, e[10][10], visited[10];

void closure(int s)
{
    int i;
    visited[s] = 1;
    for (i = 0; i < n; i++)
        if (e[s][i] && !visited[i])
            closure(i);
}

int main()
{
    int i, j, m, a, b;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of epsilon transitions: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            e[i][j] = 0;

    printf("Enter transitions (from to):\n");
    for (i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        e[a][b] = 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            visited[j] = 0;
        closure(i);
        printf("Epsilon-closure(%d) = { ", i);
        for (j = 0; j < n; j++)
            if (visited[j])
                printf("%d ", j);
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
Enter transitions (from to):
0 1
1 2
3 1

Expected output:
Epsilon-closure(0) = { 0 1 2 }
Epsilon-closure(1) = { 1 2 }
Epsilon-closure(2) = { 2 }
Epsilon-closure(3) = { 1 2 3 }
*/
