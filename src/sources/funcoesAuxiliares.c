#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoesAuxiliares.h>

void removequotes(char *str)
{
    int size;

    //Removes newline '\n' and carriage return '\r' characters if present.
    if(strchr(str, '\n') != NULL)
        str[strcspn(str, "\n")] = '\0';
    if(strchr(str, '\r') != NULL)
        str[strcspn(str, "\r")] = '\0';

    //Checks if the first character is a quote (ASCII 34), removes the starting and ending quotes from the string.
    if(str[0] == 34)
    {
        size = strlen(str) - 2; //Calculates the new size of the string without the quotes
        memmove(str, str + 1, size); //Moves the string 1 position to the left
        str[size] = '\0'; //Inserts the null terminator at the new end of the string
    }
    return;
}