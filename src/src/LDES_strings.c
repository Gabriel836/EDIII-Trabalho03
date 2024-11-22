#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDES_strings.h"

ListaString* criaListaStrings() {
    ListaString *li;
    li = (ListaString*)malloc(sizeof(ListaString));

    li->inicio = NULL; //Inicializa a lista vazia
    li->n_elem = 0; // efine o número de elementos como 0
    return li;
}

int insereNoStringsOrdenado(ListaString *li, char *string) {
    //Verifica se a lista é válida
    if(li == NULL) return -1;

    if(presenteNaLista(li, string) != NULL) return 0; //Verifica se a string já está na lista

    //Cria um novo nó
    NoString *ptr_no = (NoString*)malloc(sizeof(NoString));
    ptr_no->prox = NULL;
    strcpy(ptr_no->string, string);

    //Ponteiros auxiliares para percorrer a lista
    NoString *ant, *prox;

    //Caso a lista esteja vazia
    if(li->inicio == NULL) li->inicio = ptr_no; //Insere no ínicio
    else {
        ant = li->inicio;
        prox = ant->prox;

        //Caso a string seja menor que o primeiro elemento
        if(strcmp(ptr_no->string, ant->string) < 0) {
            li->inicio = ptr_no;
            ptr_no->prox = ant;
        }
        else {
            //Insere a string na posição correta
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
    li->n_elem += 1; //Incrementa o número de elementos na lista
    return 0;
}

int insereNoStringsDireto(ListaString *li, char *string) {
    if(li == NULL) return -1; //Verifica se a lista é válida

    if(presenteNaLista(li, string) != NULL) return 0; //Verifica se a string já está na lista

    //Cria um novo nó
    NoString *ptr_no = (NoString*)malloc(sizeof(NoString));
    ptr_no->prox = NULL;
    strcpy(ptr_no->string, string);

    //Ponteiros auxiliares
    NoString *ant, *prox;

    //Caso a lista esteja vazia
    if(li->inicio == NULL) li->inicio = ptr_no; //Insere no íncio
    else {
        //Percorre a lista até o último elemento
        for(ant = li->inicio; ant->prox != NULL; ant = ant->prox) continue;
        ant->prox = ptr_no; //Adiciona o novo nó no final
    }
    li->n_elem += 1; //Incrementa o número de elementos na lista
    return 0;
}

// Modifica a lista passada por parametro
ListaString* inverteLista(ListaString *li) {
    if(li == NULL) return NULL; //Verifica se a lista é válida

    int i, j;
    ListaString *invertida = criaListaStrings(); //Cria uma nova lista para armazenar os elementos invertidos
    invertida->inicio = NULL;
    invertida->n_elem = li->n_elem;

    NoString *atual = li->inicio;

    for(i = li->n_elem-1; i >= 0; i--) {
        //Percorre a lista até o elemento atual
        for(j = 0; j < i; j++) {
            atual = atual->prox;
        }
        //Insere o elemento no início da nova lista
        insereNoStringsDireto(invertida, atual->string);
        atual = li->inicio;
    }
    return invertida;
}

//Remoção da lista
int deletaListaStrings(ListaString *li) {
    // Verifica se a lista é válida
    if(li == NULL) return -1;
    if(li->inicio == NULL) {
        free(li);
        return 0;
    }

    NoString *atual, *prox;
    atual = li->inicio;
    prox = atual->prox;

    do { //Libera cada nó da lista
        free(atual);
        atual = prox;
        if(atual != NULL) prox = atual->prox;
    }
    while(atual != NULL);

    free(li); //Libera a estrutura principal da lista

    return 0;
}

int imprimeListaStrings(ListaString *li) {
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

int listaVazia(ListaString *li) {
    //Ponteiro de lista Nulo
    if(li == NULL) return -1;

    //Lista vazia
    if(li->n_elem == 0) return 1;
    else return 0;
}

NoString* presenteNaLista(ListaString *li, char *str) {
    NoString *atual = li->inicio;

    while(atual != NULL) {
        if(!strcmp(atual->string, str)) return atual; //Compara as strings
        atual = atual->prox;
    }
    return NULL; //Retorna NULL se a string não for encontrada
}