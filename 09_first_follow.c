/*Mohammed Faiz
S7 CSB 23
Exp 9
FIRST AND FOLLOW*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

char production[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
int n;

/* Add a character to a set if it is not
   already present */
void add(char set[], char c)
{
    int i;

    for (i = 0; set[i] != '\0'; i++)
        if (set[i] == c)
            return;

    set[i] = c;
    set[i + 1] = '\0';
}

/* Find FIRST of a symbol */
void findFirst(char c, char result[])
{
    int i, j;
    char temp[MAX];

    /* Terminal */
    if (!isupper(c))
    {
        add(result, c);
        return;
    }

    /* Non-terminal */
    for (i = 0; i < n; i++)
    {
        if (production[i][0] == c)
        {
            /* A -> # means epsilon */
            if (production[i][2] == '#')
            {
                add(result, '#');
            }
            else
            {
                for (j = 2; production[i][j] != '\0';
                     j++)
                {
                    temp[0] = '\0';
                    findFirst(production[i][j], temp);

                    int k;
                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            add(result, temp[k]);
                    }

                    /* If epsilon is not present,
                       stop */
                    int hasEpsilon = 0;
                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] == '#')
                            hasEpsilon = 1;
                    }

                    if (!hasEpsilon)
                        break;

                    /* If all symbols can produce
                       epsilon */
                    if (production[i][j + 1] == '\0')
                        add(result, '#');
                }
            }
        }
    }
}

/* Find FOLLOW sets */
void findFollow(char c)
{
    int i, j, k;
    char temp[MAX];

    /* Start symbol gets $ */
    if (c == production[0][0])
        add(follow[c - 'A'], '$');

    for (i = 0; i < n; i++)
    {
        for (j = 2; production[i][j] != '\0'; j++)
        {
            if (production[i][j] == c)
            {
                /* If symbol is at the end */
                if (production[i][j + 1] == '\0')
                {
                    if (production[i][0] != c)
                    {
                        findFollow(production[i][0]);

                        for (k = 0;
                             follow[production[i][0]
                                    - 'A'][k] != '\0';
                             k++)
                            add(follow[c - 'A'],
                                follow[production[i][0]
                                       - 'A'][k]);
                    }
                }
                else
                {
                    temp[0] = '\0';
                    findFirst(production[i][j + 1],
                              temp);

                    int hasEpsilon = 0;

                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] == '#')
                            hasEpsilon = 1;
                        else
                            add(follow[c - 'A'],
                                temp[k]);
                    }

                    /* If next symbol produces
                       epsilon */
                    if (hasEpsilon &&
                        production[i][0] != c)
                    {
                        findFollow(production[i][0]);

                        for (k = 0;
                             follow[production[i][0]
                                    - 'A'][k] != '\0';
                             k++)
                            add(follow[c - 'A'],
                                follow[production[i][0]
                                       - 'A'][k]);
                    }
                }
            }
        }
    }
}

int main()
{
    int i;
    char result[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("\nEnter productions:\n");
    printf("Example: E=TR\n");
    printf("Use # for epsilon.\n\n");

    for (i = 0; i < n; i++)
        scanf("%s", production[i]);

    /* FIRST */
    printf("\nFIRST sets:\n");

    for (i = 0; i < n; i++)
    {
        char c = production[i][0];

        result[0] = '\0';
        findFirst(c, result);

        printf("FIRST(%c) = { ", c);

        int j;
        for (j = 0; result[j] != '\0'; j++)
            printf("%c ", result[j]);

        printf("}\n");
    }

    /* FOLLOW */
    for (i = 0; i < n; i++)
    {
        char c = production[i][0];
        findFollow(c);
    }

    printf("\nFOLLOW sets:\n");

    for (i = 0; i < n; i++)
    {
        char c = production[i][0];
        printf("FOLLOW(%c) = { ", c);

        int j;
        for (j = 0; follow[c - 'A'][j] != '\0'; j++)
            printf("%c ", follow[c - 'A'][j]);

        printf("}\n");
    }

    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>
*/
