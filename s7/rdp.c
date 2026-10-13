/*
Start.
Read the input string.
Initialize the input pointer i to zero, pointing to the first character.
Call E() to parse the expression.
In E(), call T().
Check whether the current symbol is +. If yes, move the pointer and recursively call E().
In T(), call F().
Check whether the current symbol is *. If yes, move the pointer and recursively call T().
In F(), check whether the current symbol is a lowercase alphabet. If valid, move the pointer to the next character.
After parsing, check whether the complete input string has been consumed.
If the entire string is consumed, display String Accepted; otherwise, display String Rejected.
Stop.
*/

#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;

void E();
void T();
void F();

void E()
{
    T();

    if(input[i] == '+')
    {
        i++;
        E();
    }
}

void T()
{
    F();

    if(input[i] == '*')
    {
        i++;
        T();
    }
}

void F()
{
    if(input[i] >= 'a' && input[i] <= 'z')
    {
        i++;
    }
}

int main()
{
    printf("Enter the string: ");
    scanf("%99s", input);

    E();

    if(input[i] == '\0')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
