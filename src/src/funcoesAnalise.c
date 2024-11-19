#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesAnalise.h"
#include "LDES_strings.h"
#include "grafo.h"

//Imprime da lista de predadores de uma presa
//Recebe o nome da presa sem aspas
void listaPredadores(Grafo *grafo, char* presa) {
    //Grafo Nulo 
    if(grafo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    ListaString *lista_predadores;
    lista_predadores = criaListaStrings();

    Vertice* vert_atual = grafo->listaVertices;
    Aresta* aresta_atual;
    //Grafo vazio
    if(vert_atual == NULL) {
        printf("Registro inexistente.\n");
        return;
    }

    //Para cada animal do grafo
    while(vert_atual != NULL) {
        aresta_atual = vert_atual->listaArestas;

        //Verificamos se a presa esta na lista de presas de cada predador
        while(aresta_atual != NULL) {
            //Caso este seja um predador de "presa", é inserido em uma LDES
            if(!strcmp(aresta_atual->destino->animal->nome, presa)) {
                insereNoStrings(lista_predadores, vert_atual->animal->nome);
                break;
            }
            aresta_atual = aresta_atual->prox;
        }
        vert_atual = vert_atual->prox;
    }

    //Imprimindo resultados
    if(listaVazia(lista_predadores)) printf("Registro Inexistente.\n\n");
    else {
        printf("%s: ", presa);
        imprimeListaStrings(lista_predadores);
        printf("\n");
    }
    deletaListaStrings(lista_predadores);
}





