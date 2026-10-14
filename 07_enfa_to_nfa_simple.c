/*Mohammed Faiz
S7 CSB 23
Exp 7
Epsilon to NFA transition (short version)*/
#include <stdio.h>

int n, e[10][10], t[10][10][10];
int c[10][10];

void closure(int s, int q)
{
    int i;
    if (c[s][q]) return;
    c[s][q] = 1;
    for (i = 0; i < n; i++)
        if (e[q][i])
            closure(s, i);
}

int main()
{
    int i, j, k, m, a, b, x;

    printf("Number of states: ");
    scanf("%d", &n);
    printf("Number of symbols (0 or 1): ");
    scanf("%d", &m);
    printf("Number of epsilon transitions: ");
    scanf("%d", &x);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            e[i][j] = c[i][j] = 0;
            for (k = 0; k < m; k++)
                t[k][i][j] = 0;
        }

    printf("Enter epsilon transitions (from to):\n");
    for (i = 0; i < x; i++) {
        scanf("%d%d", &a, &b);
        e[a][b] = 1;
    }

    for (i = 0; i < n; i++)
        closure(i, i);

    for (k = 0; k < m; k++) {
        printf("Number of transitions for symbol %d: ", k);
        scanf("%d", &x);
        printf("Enter transitions (from to):\n");
        for (i = 0; i < x; i++) {
            scanf("%d%d", &a, &b);
            t[k][a][b] = 1;
        }
    }

    printf("\nNFA transitions without epsilon:\n");
    for (k = 0; k < m; k++)
        for (i = 0; i < n; i++) {
            int r[10] = {0};
            for (j = 0; j < n; j++)
                if (c[i][j])
                    for (a = 0; a < n; a++)
                        if (t[k][j][a])
                            for (b = 0; b < n; b++)
                                if (c[a][b])
                                    r[b] = 1;
            printf("State %d, symbol %d -> { ", i, k);
            for (b = 0; b < n; b++)
                if (r[b]) printf("%d ", b);
            printf("}\n");
        }
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
Number of states: 3
Number of symbols: 3
Number of epsilon transitions: 2
0 1
1 2
Number of transitions for symbol 0: 1
0 0
Number of transitions for symbol 1: 1
1 1
Number of transitions for symbol 2: 1
2 2

Expected output:
NFA transitions without epsilon:
State 0, symbol 0 -> { 0 1 2 }
State 1, symbol 0 -> { }
State 2, symbol 0 -> { }
State 0, symbol 1 -> { 1 2 }
State 1, symbol 1 -> { 1 2 }
State 2, symbol 1 -> { }
State 0, symbol 2 -> { 2 }
State 1, symbol 2 -> { 2 }
State 2, symbol 2 -> { 2 }
*/
