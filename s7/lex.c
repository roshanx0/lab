/*
If the file cannot be opened, display File not found and stop.
Read a character from the file.
Ignore spaces, tabs, and newlines.
If the character is #, display it as a symbol.
If the character is /, check whether it begins a single-line or multiline comment.
If it is a comment, skip the comment; otherwise, identify / as an operator.
If the character is a letter or underscore, read the complete word.
Check whether the word is a preprocessor keyword.
If not, check whether it is a C keyword; otherwise, classify it as an identifier.
If the character is a digit, read and display the complete number.
If the character is ", read and display the string literal.
If the character is an operator, check whether it forms a two-character operator such as >=, <=, ==, !=, ++, or --.
If the character is a special symbol, display it.
Otherwise, display it as an unknown character.
Repeat until the end of the file.
Close the file.
Stop.

input.c

#include <stdio.h>
int main() {
    int a = 10;
    float b = 20.5;

    if (a <= b)
        printf("Hello");

    return 0;
}

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *kw[] = {
    "int", "float", "char", "double", "if",
    "else", "while", "for", "return", "void"
};

char *ppkw[] = {
    "include", "define", "ifdef", "ifndef",
    "endif", "undef"
};

int isKeyword(char *s)
{
    int i;
    for(i = 0; i < 10; i++)
        if(strcmp(s, kw[i]) == 0)
            return 1;
    return 0;
}

int isPPKeyword(char *s)
{
    int i;
    for(i = 0; i < 6; i++)
        if(strcmp(s, ppkw[i]) == 0)
            return 1;
    return 0;
}

int main()
{
    FILE *fp = fopen("input.c", "r");
    char str[100], ch, next;
    int i;

    if(fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        if(isspace((unsigned char)ch))
            continue;

        /* Preprocessor symbol */
        if(ch == '#')
        {
            printf("Symbol : #\n");
        }

        /* Comments or division operator */
        else if(ch == '/')
        {
            next = fgetc(fp);

            if(next == '/')
            {
                while((ch = fgetc(fp)) != EOF && ch != '\n')
                    ;
            }
            else if(next == '*')
            {
                int prev = 0;

                while((ch = fgetc(fp)) != EOF)
                {
                    if(prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
            }
            else
            {
                printf("Operator : /\n");
                if(next != EOF)
                    fseek(fp, -1, SEEK_CUR);
            }
        }

        /* Keywords, identifiers and preprocessor words */
        else if(isalpha((unsigned char)ch) || ch == '_')
        {
            i = 0;

            do
            {
                if(i < 99)
                    str[i++] = ch;
                ch = fgetc(fp);
            }
            while(isalnum((unsigned char)ch) || ch == '_');

            str[i] = '\0';

            if(ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            if(isPPKeyword(str))
                printf("Preprocessor Keyword : %s\n", str);
            else if(isKeyword(str))
                printf("Keyword : %s\n", str);
            else
                printf("Identifier : %s\n", str);
        }

        /* Numbers */
        else if(isdigit((unsigned char)ch))
        {
            i = 0;

            do
            {
                if(i < 99)
                    str[i++] = ch;
                ch = fgetc(fp);
            }
            while(isdigit((unsigned char)ch) || ch == '.');

            str[i] = '\0';

            if(ch != EOF)
                fseek(fp, -1, SEEK_CUR);

            printf("Number : %s\n", str);
        }

        /* String literals */
        else if(ch == '"')
        {
            i = 0;
            str[i++] = ch;

            while((ch = fgetc(fp)) != EOF && ch != '"')
            {
                if(i < 98)
                    str[i++] = ch;

                if(ch == '\\')
                {
                    ch = fgetc(fp);
                    if(ch == EOF)
                        break;
                    if(i < 98)
                        str[i++] = ch;
                }
            }

            if(ch == '"')
                str[i++] = '"';

            str[i] = '\0';
            printf("String : %s\n", str);
        }

        /* Character literals */
        else if(ch == '\'')
        {
            printf("Symbol : '\n");

            while((ch = fgetc(fp)) != EOF && ch != '\'')
            {
                if(ch == '\\')
                    ch = fgetc(fp);
            }

            printf("Symbol : '\n");
        }

        /* Operators */
        else if(strchr("+-*=<>!%&|^", ch))
        {
            next = fgetc(fp);

            if((ch == '=' && next == '=') ||
               (ch == '!' && next == '=') ||
               (ch == '<' && (next == '=' || next == '<')) ||
               (ch == '>' && (next == '=' || next == '>')) ||
               (ch == '+' && (next == '+' || next == '=')) ||
               (ch == '-' && (next == '-' || next == '=')) ||
               (ch == '*' && next == '=') ||
               (ch == '/' && next == '=') ||
               (ch == '%' && next == '=') ||
               (ch == '&' && (next == '&' || next == '=')) ||
               (ch == '|' && (next == '|' || next == '=')) ||
               (ch == '^' && next == '='))
            {
                printf("Operator : %c%c\n", ch, next);
            }
            else
            {
                printf("Operator : %c\n", ch);
                if(next != EOF)
                    fseek(fp, -1, SEEK_CUR);
            }
        }

        /* Special symbols */
        else if(strchr("(){}[];,.:?", ch))
        {
            printf("Symbol : %c\n", ch);
        }

        else
        {
            printf("Unknown : %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
