/*Mohammed Faiz
S7 CSB 23
Exp 3
Counter*/
%{
#include <stdio.h>

int lines = 0, words = 0, chars = 0;
%}

%%

\n          { lines++; chars++; }
[ \t]+      { chars += yyleng; }
[^ \t\n]+   { words++; chars += yyleng; }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the text (Press Ctrl+D in Linux"
           " / Ctrl+Z in Windows to end):\n");
    yylex();

    printf("\nNumber of Lines : %d\n", lines);
    printf("Number of Words : %d\n", words);
    printf("Number of Characters : %d\n", chars);

    return 0;
}
