#include <stdio.h>

int n, e[10][10], c[10][10];

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
    int i, j, m, a, b;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of epsilon transitions: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            e[i][j] = c[i][j] = 0;

    printf("Enter transitions (from to):\n");
    for (i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        e[a][b] = 1;
    }

    for (i = 0; i < n; i++) {
        closure(i, i);
        printf("Epsilon-closure(%d) = { ", i);
        for (j = 0; j < n; j++)
            if (c[i][j])
                printf("%d ", j);
        printf("}\n");
    }

    return 0;
}
