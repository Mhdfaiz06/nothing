/*Mohammed Faiz
S7 CSB 23
Exp 10
Recursive Descent Parser (short version)*/
#include <stdio.h>
#include <stdlib.h>

char s[100];
int p = 0;

void E();

void rej() {
    printf("String is rejected.\n");
    exit(1);
}

void F() {
    if (s[p] == '(') {
        p++;
        E();
        if (s[p] != ')') rej();
        p++;
    }
    else if (s[p] == 'i' && s[p+1] == 'd')
        p += 2;
    else
        rej();
}

void T() {
    F();
    while (s[p] == '*') {
        p++;
        F();
    }
}

void E() {
    T();
    while (s[p] == '+') {
        p++;
        T();
    }
}

int main() {
    printf("Enter the expression: ");
    scanf("%99s", s);
    E();
    if (s[p] == '\0')
        printf("String is accepted.\n");
    else
        printf("String is rejected.\n");
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
id+id*id      (try also: (id+id)*id  and  id+*id)

Expected output:
id+id*id    -> String is accepted.
(id+id)*id  -> String is accepted.
id+*id      -> String is rejected.
*/
