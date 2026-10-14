/*Mohammed Faiz
S7 CSB 23
Exp 4
Vowels and Consonants*/
%{
#include <stdio.h>

int vowels = 0, consonants = 0;
%}

%%

[AEIOUaeiou]    { vowels++; }
[B-DF-HJ-NP-TV-Zb-df-hj-np-tv-z] {
                    consonants++;
                }
\n              { return 0; }
.               ;

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("\nTotal Vowels : %d\n", vowels);
    printf("Total Consonants : %d\n", consonants);

    return 0;
}

/*
Commands to run:
flex <file_name>.l
gcc lex.yy.c -o <file_name> -ll
./<file_name>

Sample input:
Hello World
(press Enter)

Expected output:
Total Vowels : 3
Total Consonants : 7
*/
