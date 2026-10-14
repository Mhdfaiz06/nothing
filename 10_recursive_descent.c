/*Mohammed Faiz
S7 CSB 23
Exp 10
Recursive Descent Parser*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("Invalid Expression\n");
    exit(0);
}

/* E -> T E' */
void E()
{
    T();
    Eprime();
}

/* E' -> + T E' | - T E' | epsilon */
void Eprime()
{
    if (input[pos] == '+' || input[pos] == '-')
    {
        pos++;
        T();
        Eprime();
    }
}

/* T -> F T' */
void T()
{
    F();
    Tprime();
}

/* T' -> * F T' | / F T' | epsilon */
void Tprime()
{
    if (input[pos] == '*' || input[pos] == '/')
    {
        pos++;
        F();
        Tprime();
    }
}

/* F -> (E) | i */
void F()
{
    if (input[pos] == 'i')
    {
        pos++;
    }
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error();
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Enter expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("Valid Expression\n");
    else
        error();

    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
i+i*i      (try also: (i+i)*i  and  i+*i)

Expected output:
i+i*i    -> Valid Expression
(i+i)*i  -> Valid Expression
i+*i     -> Invalid Expression
*/
