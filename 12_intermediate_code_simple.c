/*Mohammed Faiz
S7 CSB 23
Exp 12
Intermediate code generator (short version)*/
#include <stdio.h>

int main()
{
    char lhs, a, b, c, op1, op2, temp;
    int count = 1;

    printf("Enter expression (a=b+c*d): ");
    scanf(" %c=%c%c%c%c%c", &lhs, &a, &op1, &b, &op2, &c);

    if (op2 == '*' || op2 == '/')
    {
        printf("t%d = %c %c %c\n", count, b, op2, c);
        temp = '0' + count;
        count++;
        printf("t%d = %c %c t%c\n", count, a, op1, temp);
    }
    else
    {
        printf("t%d = %c %c %c\n", count, a, op1, b);
        temp = '0' + count;
        count++;
        printf("t%d = t%c %c %c\n", count, temp, op2, c);
    }

    printf("%c = t%d\n", lhs, count);
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
a=b+c*d
(must be exactly this form: x=y op z op w, single letters)

Expected output:
t1 = c * d
t2 = b + t1
a = t2
*/
