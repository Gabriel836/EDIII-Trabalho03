// Lista Encadeada Dinamica Simples para Strings.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

typedef struct Lista_strings {
    int n_elem;
    NoString *inicio;
} ListaString;

typedef struct no_string {
    char string[MAX_CHAR];
    NoString *prox;
} NoString;

int criaListaStrings(ListaString *li);
int insereNoStrings(ListaString *li, char *string);
int deletaListaStrings(ListaString *li);
int imprimeListaStrings(ListaString *li);
int listaVazia(ListaString *li);