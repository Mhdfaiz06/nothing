/*Mohammed Faiz
S7 CSB 23
Exp 5
Lex-yacc*/
%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token ID

%%

S : ID
    {
        printf("Valid Identifier\n");
    }
  ;

%%

void yyerror(const char *s)
{
    printf("Invalid Identifier\n");
}

int main()
{
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}
