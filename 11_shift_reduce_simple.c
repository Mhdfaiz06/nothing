/*Mohammed Faiz
S7 CSB 23
Exp 11
Shift Reduce Parser (short version)*/
#include <stdio.h>
#include <string.h>

char st[100];
int n = 0;

char *rule[] = {"id", "E+E", "E*E", "(E)"};

int reduce() {
    for (int r = 0; r < 4; r++) {
        int len = strlen(rule[r]);
        if (n >= len && strncmp(st + n - len, rule[r], len) == 0) {
            n -= len;
            st[n++] = 'E';
            st[n] = '\0';
            printf("%-20s REDUCE\n", st);
            return 1;
        }
    }
    return 0;
}

int main() {
    char in[100];
    printf("Enter the input string: ");
    scanf("%99s", in);
    printf("%-20s %s\n", "Stack", "Action");
    for (int i = 0; in[i] != '\0'; i++) {
        st[n++] = in[i];
        st[n] = '\0';
        printf("%-20s SHIFT\n", st);
        while (reduce());
    }
    if (n == 1 && st[0] == 'E')
        printf("\nInput string is ACCEPTED.\n");
    else
        printf("\nInput string is REJECTED.\n");
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
id+id*id

Expected output:
Stack                Action
i                    SHIFT
id                   SHIFT
E                    REDUCE
E+                   SHIFT
E+i                  SHIFT
E+id                 SHIFT
E+E                  REDUCE
E                    REDUCE
E*                   SHIFT
E*i                  SHIFT
E*id                 SHIFT
E*E                  REDUCE
E                    REDUCE

Input string is ACCEPTED.
*/
