#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DFS.h"
#include "grafo.h"

//DFS e contagem de ciclos

int contagemCiclos(Grafo *grafo) {
    int *counter, *inf, *ciclos;

    counter = (int*)calloc(1, sizeof(int));
    ciclos = (int*)calloc(1, sizeof(int));
    *ciclos = 0;
    *counter = 0;
    inf = (int*)calloc(1, sizeof(int));

    Vertice *v;

    for(v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->visitado) continue;

        *inf = *counter;

        DFS(v, counter, inf, ciclos);
    }

    return *ciclos;
}


// Função recursiva DFS.
void DFS(Vertice *v, int *counter, int *inf, int *ciclos) {
    Aresta* prox;
    (*counter)++;

    v->visitado = 1;
    v->tempo = *counter;

    if(v->listaArestas == NULL) return;

    for(prox = v->listaArestas; prox != NULL; prox = prox->prox) {
        if(prox->destino->visitado && prox->destino->tempo > *inf) {
            (*ciclos)++;
            continue;
        }
        else if(v->visitado == 0) {
            DFS(prox->destino, counter, inf, ciclos);
        }
    }
    return;
}