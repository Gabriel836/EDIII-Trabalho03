#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDES_strings.h"

int criaListaStrings(ListaString *li) {
    li = (ListaString*)malloc(sizeof(ListaString));

    if(li != NULL) {
        li->inicio = NULL;
        li->n_elem = 0;
        return 0;
    }
    else return -1;
}

//Inserção ordenada na lista encadeada
int insereNoStrings(ListaString *li, char *string) {

    //Ponteiro da lista Nulo
    if(li == NULL) return -1;

    //Criando no
    NoString *ptr_no = (NoString*)malloc(sizeof(NoString));
    ptr_no->prox = NULL;
    strcpy(ptr_no, string);

    //Ponteiros auxiliares
    NoString *ant, *prox;

    //Lista Vazia
    if(li->inicio == NULL) li->inicio = ptr_no;

    else {
        ant = li->inicio;
        prox = ant->prox;

        if(strcmp(ptr_no->string, ant->string) < 0) {
            li->inicio = ptr_no;
            ptr_no->prox = ant;
        }
        else {
            while(1) {
                if(strcmp(ant->string, ptr_no->string) < 0) {
                    if(prox == NULL || strcmp(ptr_no->string, prox->string) < 0) {
                        ant->prox = ptr_no;
                        ptr_no->prox = prox;
                        break;
                    }
                }
                ant = prox;
                prox = prox->prox;
            }
        }
    }
    li->n_elem += 1;
    return 0;
}

//Remoção da lista
int removeListaStrings(ListaString *li) {
    //Ponteiro da lista Nulo
    if(li == NULL) return -1;
    if(li->inicio == NULL) {
        free(li);
        return 0;
    }

    NoString *atual, *prox;
    atual = li->inicio;
    prox = atual->prox;

    do {
        free(atual);
        atual = prox;
        if(atual != NULL) prox = atual->prox;
    }
    while(atual != NULL);

    free(li);
    return 0;
}

//Printa Lista
int imprimeListaStrings(ListaString *li) {
    //Ponteiro de lista Nulo
    if(li == NULL) return -1;
    if(li->inicio == NULL) {
        printf("ERRO: LISTA VAZIA\n");
        return 0;
    }

    NoString *atual = li->inicio;
    while(atual->prox != NULL) {
        printf("%s, ", atual->string);
        atual = atual->prox;
    }
    printf("%s\n", atual->string);

    return 0;
}
