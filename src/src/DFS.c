#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DFS.h"
#include "grafo.h"

//DFS e contagem de ciclos

int contagemCiclos(Grafo *grafo, int *comp) {
    int *counter, *pos, *inf, *ciclos, i = 0, ant;

    *comp = 0;

    counter = (int*)calloc(1, sizeof(int));
    ciclos = (int*)calloc(1, sizeof(int));
    pos = (int*)calloc(1, sizeof(int));

    *ciclos = 0;
    *counter = 0;
    *pos = 0;

    inf = (int*)calloc(1, sizeof(int));

    Vertice *v;

    for(v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->visitado) continue;

        i++;
        *inf = *counter;
        ant = *ciclos;

        DFS(v, counter, pos, inf, ciclos);

        if(*ciclos > ant) {
            (*comp)++;
        }
    }

    return *ciclos;
}


// Função recursiva DFS.
void DFS(Vertice *v, int *counter, int *pos, int *inf, int *ciclos) {
    Aresta* prox;
    (*counter)++;
    (*pos)++;

    v->visitado = 1;
    v->tempo[0] = *counter;

    if(v->listaArestas == NULL) return;

    for(prox = v->listaArestas; prox != NULL; prox = prox->prox) {
        if(prox->destino->visitado && prox->destino->tempo > *inf) {
            (*ciclos)++;

            printf("ciclo: %s -- %s\n", v->animal->nome, prox->destino->animal->nome);
            continue;
        }
        else if(v->visitado == 0) {
            printf("avanco: %s -> %s\n", v->animal->nome, prox->destino->animal->nome);
            DFS(prox->destino, counter, pos, inf, ciclos);
        }
    }
    (*pos)++;
    v->tempo[1] = *pos;
    return;
}