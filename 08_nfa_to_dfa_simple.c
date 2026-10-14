/*Mohammed Faiz
S7 CSB 23
Exp 8
NFA to DFA transition (short version)*/
#include <stdio.h>
int n, t[2][10][10];
int d[100][2], sets[100][10];
int count = 1;

int find(int s[])
{
    int i, j, same;
    for (i = 0; i < count; i++) {
        same = 1;
        for (j = 0; j < n; j++)
            if (sets[i][j] != s[j]) same = 0;
        if (same) return i;
    }
    for (j = 0; j < n; j++)
        sets[count][j] = s[j];
    return count++;
}

int main()
{
    int i, j, k, m, a, b, cur, next[10];

    printf("Number of NFA states: ");
    scanf("%d", &n);

    for (i = 0; i < 2; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                t[i][j][k] = 0;

    for (i = 0; i < 2; i++) {
        printf("Number of transitions for symbol %d: ", i);
        scanf("%d", &m);
        printf("Enter transitions (from to):\n");
        for (j = 0; j < m; j++) {
            scanf("%d%d", &a, &b);
            t[i][a][b] = 1;
        }
    }

    sets[0][0] = 1;

    for (cur = 0; cur < count; cur++) {
        for (k = 0; k < 2; k++) {
            for (j = 0; j < n; j++) next[j] = 0;
            for (i = 0; i < n; i++)
                if (sets[cur][i])
                    for (j = 0; j < n; j++)
                        if (t[k][i][j])
                            next[j] = 1;
            d[cur][k] = find(next);
        }
    }

    printf("\nDFA transitions:\n");
    for (i = 0; i < count; i++) {
        printf("D%d = {", i);
        for (j = 0; j < n; j++)
            if (sets[i][j]) printf("q%d ", j);
        printf("}\n");
        for (k = 0; k < 2; k++)
            printf(" on %d -> D%d\n", k, d[i][k]);
    }
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
Number of NFA states: 3
Number of transitions for symbol 0: 3
0 0
0 1
1 2
Number of transitions for symbol 1: 1
0 0
(only 2 symbols: 0 and 1, start state is always q0)

Expected output:
DFA transitions:
D0 = {q0 }
 on 0 -> D1
 on 1 -> D0
D1 = {q0 q1 }
 on 0 -> D2
 on 1 -> D0
D2 = {q0 q1 q2 }
 on 0 -> D2
 on 1 -> D0
*/
