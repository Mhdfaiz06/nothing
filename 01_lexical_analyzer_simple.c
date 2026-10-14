/*Mohammed Faiz
S7 CSB 23
Exp 1
Lexical analyzer (short version)*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *fp = fopen("input.c", "r");
    int ch;
    char str[50];
    int i;

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) continue;

        if (ch == '/') {
            int next = fgetc(fp);
            if (next == '/')
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            else
                ungetc(next, fp);
            continue;
        }

        if (isalpha(ch)) {
            i = 0;
            do {
                str[i++] = ch;
                ch = fgetc(fp);
            } while (isalnum(ch));
            str[i] = '\0';
            ungetc(ch, fp);

            if (!strcmp(str, "int") || !strcmp(str, "if") || !strcmp(str, "return"))
                printf("Keyword: %s\n", str);
            else
                printf("Identifier: %s\n", str);
        }
        else if (isdigit(ch)) {
            i = 0;
            do {
                str[i++] = ch;
                ch = fgetc(fp);
            } while (isdigit(ch));
            str[i] = '\0';
            ungetc(ch, fp);
            printf("Number: %s\n", str);
        }
        else if (strchr("+-*/=%<>", ch))
            printf("Operator: %c\n", ch);
        else if (strchr("(){};,", ch))
            printf("Symbol: %c\n", ch);
    }

    fclose(fp);
    return 0;
}

/*
Commands to run:
gcc <file_name>.c -o <file_name>
./<file_name>

Sample input:
input.c (create this file in the same folder):
int sum = a + 10;
// comment
if (sum > 5) return sum;

Expected output:
Keyword: int
Identifier: sum
Operator: =
Identifier: a
Operator: +
Number: 10
Symbol: ;
Keyword: if
Symbol: (
Identifier: sum
Operator: >
Number: 5
Symbol: )
Keyword: return
Identifier: sum
Symbol: ;
(only int, if, return are treated as keywords)
*/
