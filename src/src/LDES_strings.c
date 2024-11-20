#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDES_strings.h"

ListaString* criaListaStrings() {
    ListaString *li;
    li = (ListaString*)malloc(sizeof(ListaString));

    li->inicio = NULL;
    li->n_elem = 0;
    return li;
}

//Inserção ordenada na lista encadeada
int insereNoStrings(ListaString *li, char *string) {

    //Ponteiro da lista Nulo
    if(li == NULL) return -1;

    if(presenteNaLista(li, string) != NULL) return 0;

    //Criando no
    NoString *ptr_no = (NoString*)malloc(sizeof(NoString));
    ptr_no->prox = NULL;
    strcpy(ptr_no->string, string);
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
                if(prox == NULL || strcmp(ptr_no->string, prox->string) < 0) {
                    ant->prox = ptr_no;
                    ptr_no->prox = prox;
                    break;
                }
                ant = ant->prox;
                prox = prox->prox;
            }
        }
    }
    li->n_elem += 1;
    return 0;
}

//Remoção da lista
int deletaListaStrings(ListaString *li) {
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


//Verifica se a lista esta vazia
int listaVazia(ListaString *li) {
    //Ponteiro de lista Nulo
    if(li == NULL) return -1;

    //Lista vazia
    if(li->n_elem == 0) return 1;
    else return 0;
}

//Verifica se a string esta na lista
NoString* presenteNaLista(ListaString *li, char *str) {
    NoString *atual = li->inicio;

    while(atual != NULL) {
        if(!strcmp(atual->string, str)) return atual;
        atual = atual->prox;
    }
    return NULL;
}