/*
Start.
Define the token NUMBER in the LEX specification.
Read the arithmetic expression.
Convert the numbers into integer values.
Pass the tokens to the YACC parser.
Parse the expression according to the grammar rules.
Perform addition, subtraction, multiplication and division.
Check whether the divisor is zero before division.
Display the calculated result.
Display an error message for an invalid expression.
Stop.

yacc -d calc.y
lex calc.l
gcc y.tab.c lex.yy.c -o calc -ll
./calc
*/

//calc.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUMBER 

%left '+' '-'
%left '*' '/'

%%

input:
    | input line
    ;
line:
    expr '\n' { printf("Result: %d",$1);}
    ;
expr:
    NUMBER { $$ = $1;}
    | expr '+' expr { $$ = $1 + $3;}
    | expr '-' expr { $$ = $1 - $3;}
    | expr '*' expr { $$ = $1 * $3;}
    | expr '/' expr 
     { if($3 == 0){
        printf("err division by zero");
        $$ = 0;
       } else {
         $$ = $1 / $3;} }
    | '(' expr ')' { $$ = $2; }
    ;

%%

void yyerror(char *s){
    printf("inavlid expression");
}
int main(){
    printf("enter expr:");
    yyparse();
    return 0;
}

//calc.l
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[ \t] ;
\n { return '\n';}
. { return yytext[0];}

%%

int yywrap(){
    return 1;
}
