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
