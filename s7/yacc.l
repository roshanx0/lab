/*
Start.
Define the tokens required for the arithmetic expression.
Define the precedence and associativity of arithmetic operators.
Read the arithmetic expression from the user.
The LEX analyser identifies numbers, identifiers, and operators.
Pass the identified tokens to the YACC parser.
Check the input according to the defined grammar rules.
If the expression satisfies the grammar, display Valid arithmetic expression.
Otherwise, display Invalid arithmetic expression.
Stop.

lex yacc.l
yacc -d yacc.y
gcc lex.yy.c y.tab.c -o yacc
./yacc
*/

//yacc.l

%{
#include "y.tab.h"
%}

%%
[0-9]+      { return NUMBER; }
[a-zA-Z]+   { return ID; }
[ \t]       ;
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"("         { return '('; }
")"         { return ')'; }
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}

//yacc.y

%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUMBER ID

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    expr '\n' { printf("Valid arithmetic expression\n"); }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | '-' expr %prec UMINUS
    | NUMBER
    | ID
    ;
%%

void yyerror(char *s)
{
    printf("Invalid arithmetic expression\n");
}

int main()
{
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
