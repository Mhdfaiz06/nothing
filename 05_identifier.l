/*Mohammed Faiz
S7 CSB 23
Exp 5
Lex-yacc*/
%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*    { return ID; }
.                       { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}

/*
Commands to run:
yacc -d <file_name>.y
flex <file_name>.l
gcc y.tab.c lex.yy.c -o <file_name> -ll
./<file_name>

Sample input:
count1      (run again with: 1count)

Expected output:
count1  -> Valid Identifier
1count  -> Invalid Identifier
*/
