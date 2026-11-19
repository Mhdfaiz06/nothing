#include <stdio.h>

int n, sym, e[10][10], c[10][10], t[10][10][10];

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
    int i, j, k, p, q, s, m, a, b;
    char ch;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &sym);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            e[i][j] = c[i][j] = 0;
            for (s = 0; s < sym; s++)
                t[i][s][j] = 0;
        }

    printf("Enter number of transitions: ");
    scanf("%d", &m);
    printf("Enter transitions (from symbol to, use e for epsilon, 0/1/.. for symbols):\n");
    for (i = 0; i < m; i++) {
        scanf("%d %c %d", &a, &ch, &b);
        if (ch == 'e')
            e[a][b] = 1;
        else
            t[a][ch - '0'][b] = 1;
    }

    /* Compute epsilon-closure for all states */
    for (i = 0; i < n; i++)
        closure(i, i);

    /* 3-Step NFA Transition: e* -> symbol -> e* */
    printf("\nNFA Transitions:\n");
    for (i = 0; i < n; i++) {
        for (s = 0; s < sym; s++) {
            int res[10] = {0};

            for (k = 0; k < n; k++)
                if (c[i][k])                     /* Step 1: e* from i to k */
                    for (p = 0; p < n; p++)
                        if (t[k][s][p])          /* Step 2: symbol s from k to p */
                            for (q = 0; q < n; q++)
                                if (c[p][q])     /* Step 3: e* from p to q */
                                    res[q] = 1;

            printf("d(%d, %d) = { ", i, s);
            for (q = 0; q < n; q++)
                if (res[q])
                    printf("%d ", q);
            printf("}\n");
        }
    }

    return 0;
}
