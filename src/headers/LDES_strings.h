#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 

typedef struct Lista_strings {
    int n_elem;
    NoString *inicio;
} ListaString;

typedef struct no_string {
    char *string;
    NoString *prox;
} NoString;

int criaLista(Lista_strings *li);