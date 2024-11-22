#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DFS.h"
#include "grafo.h"

//DFS e contagem de ciclos

int contagemCiclos(Grafo *grafo, ListaString *li, int *comp) {
    int *counter, *pos, *inf, *ciclos, i = 0;

    *comp = 0;

    counter = (int*)calloc(1, sizeof(int));
    ciclos = (int*)calloc(1, sizeof(int));

    *ciclos = 0;
    *counter = 0;

    inf = (int*)calloc(1, sizeof(int));

    Vertice *v;

    for(v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->visitado) continue;

        i++;
        *inf = *counter;

        DFS(v, li, counter, inf, ciclos);
    }

    return *ciclos;
}


// Função recursiva DFS.
void DFS(Vertice *v, ListaString *li, int *counter, int *inf, int *ciclos) {
    Aresta* prox;
    (*counter)++;

    v->visitado = 1;
    v->tempo = *counter;

    // Vertice sem descendentes, retorna.
    if(v->listaArestas == NULL) {
        insereNoStringsDireto(li, v->animal->nome);
        return;
    } 

    for(prox = v->listaArestas; prox != NULL; prox = prox->prox) {
        // Verifica se o vértice descendente ja foi visitado nessa iterção da sub-arvore
        if(prox->destino->visitado && prox->destino->tempo > *inf) {
            (*ciclos)++;
            continue;
        }
        else if(prox->destino->visitado == 0) {
            DFS(prox->destino, li, counter, inf, ciclos);
        }
    }
    // Todos os descendentes verificados, retorna
    insereNoStringsDireto(li, v->animal->nome);
    return;
}