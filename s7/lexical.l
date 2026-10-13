//lex lexical.l
//gcc lex.yy.c -o lexical -ll
//./lexical

%{
#include <stdio.h>
%}

%%
int|float|char|if|else|while|return    { printf("%s : Keyword\n", yytext); }
[0-9]+                                 { printf("%s : Number\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                { printf("%s : Identifier\n", yytext); }
[+\-*/=]                               { printf("%s : Operator\n", yytext); }
[(){};,]                               { printf("%s : Special Symbol\n", yytext); }
[ \t\n]+                               ;
.                                      { printf("%s : Unknown\n", yytext); }
%%

int main()
{
    printf("Enter the input:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
