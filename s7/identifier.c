/*
Start.
Write a LEX program to identify valid and invalid identifiers.
Define the pattern for a valid identifier: it must start with a letter or underscore, followed by letters, digits or underscores.
Return the token ID for a valid identifier.
Return the token INVALID for an invalid identifier.
Write a YACC program and declare the tokens ID and INVALID.
Define grammar rules to recognize valid and invalid identifiers.
Display Valid identifier if the input matches ID; otherwise, display Invalid identifier.
Compile and execute the LEX and YACC programs, then enter an identifier.
Stop.
*/
//identifier.l
%{
#include "y.tab.h"
%}
%%

[a-zA-Z_][A-Za-z_0-9]* { return ID;}
[^ \t\n] { return INVALID;}
[ \t] ;
\n { return '\n';}

%%

int yywrap(){
    return 1;
}

//identifier.y
%{
#include <stdio.h>
int yylex();
void yyerror(char *s);

%}

%token ID INVALID;

%%

S: ID '\n' { printf("valid identifier");}
  | INVALID '\n' {printf("invalid identifier");}
  ;

%%
void yyerror(char *s){
    printf("invalid identifier");
}

int main(){
    printf("enter input:");
    yyparse();
    return 0;
}
