#include <stdio.h>
#include <ctype.h>
#define MAX 20

char prod[MAX][MAX];
int n;

void add(char set[], char c)
{
    int i;
    for (i = 0; set[i] != '\0'; i++)
        if (set[i] == c)
            return;

    set[i] = c;
    set[i + 1] = '\0';
}

void findFirst(char c, char res[])
{
    int i, j, k;
    char temp[MAX];

    if (!isupper(c)) {
        add(res, c);
        return;
    }

    for (i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (prod[i][2] == '#') {
                add(res, '#');
            } else {
                for (j = 2; prod[i][j] != '\0'; j++) {
                    temp[0] = '\0';
                    findFirst(prod[i][j], temp);

                    int hasEps = 0;
                    for (k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] == '#')
                            hasEps = 1;
                        else
                            add(res, temp[k]);
                    }

                    if (!hasEps)
                        break;

                    if (prod[i][j + 1] == '\0')
                        add(res, '#');
                }
            }
        }
    }
}

void findFollow(char c, char res[])
{
    int i, j, k;
    char temp[MAX];

    if (c == prod[0][0])
        add(res, '$');

    for (i = 0; i < n; i++) {
        for (j = 2; prod[i][j] != '\0'; j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] == '\0') {
                    if (prod[i][0] != c)
                        findFollow(prod[i][0], res);
                } else {
                    temp[0] = '\0';
                    findFirst(prod[i][j + 1], temp);

                    int hasEps = 0;
                    for (k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] == '#')
                            hasEps = 1;
                        else
                            add(res, temp[k]);
                    }

                    if (hasEps && prod[i][0] != c)
                        findFollow(prod[i][0], res);
                }
            }
        }
    }
}

int main()
{
    int i, j;
    char res[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g. E=TR, # for epsilon):\n");
    for (i = 0; i < n; i++)
        scanf("%s", prod[i]);

    printf("\nFIRST sets:\n");
    for (i = 0; i < n; i++) {
        res[0] = '\0';
        findFirst(prod[i][0], res);
        printf("FIRST(%c) = { ", prod[i][0]);
        for (j = 0; res[j] != '\0'; j++)
            printf("%c ", res[j]);
        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < n; i++) {
        res[0] = '\0';
        findFollow(prod[i][0], res);
        printf("FOLLOW(%c) = { ", prod[i][0]);
        for (j = 0; res[j] != '\0'; j++)
            printf("%c ", res[j]);
        printf("}\n");
    }

    return 0;
}
