#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "dijkstra.h"

int qtdVertices(Grafo* g) {
    int tam = 0;
    Vertice* v;

    for (v = g->listaVertices; v != NULL; v = v->prox)
        tam++;

    return tam; 
}

void inicilizarDijkstra(Grafo* grafo, Vertice* origem) {
    Vertice *v;

    for (v = grafo->listaVertices; v != NULL; v = v->prox) {
        if (strcmp(v->animal->nome, origem->animal->nome) == 0)
            v->custoCaminho = 0;
        else
            v->custoCaminho = INFINITO;
        v->predecessor = NULL;
    }

    return;
}

void relaxamento(Vertice* origem, Vertice* destino, int pesoAresta) {
    if (destino->custoCaminho > origem->custoCaminho + pesoAresta) {
        destino->custoCaminho = origem->custoCaminho + pesoAresta;
        destino->predecessor = origem;
    }

    return;
}

//Função auxiliar para encontrar o vértice com menor custo
Vertice* extrairVerticeComMenorCusto(Vertice** fila, int tamanho) {
    int menorIndice = -1;
    int menorCusto = INFINITO;

    for (int i = 0; i < tamanho; i++) {
        if (fila[i] != NULL && fila[i]->custoCaminho < menorCusto) {
            menorCusto = fila[i]->custoCaminho;
            menorIndice = i;
        }
    }

    if (menorIndice != -1) {
        Vertice* menorVertice = fila[menorIndice];
        fila[menorIndice] = NULL; //Remove da fila
        return menorVertice;
    }

    return NULL; //Nenhum vértice restante
}


int dijkstra(Grafo* grafo, char* predador, char* presa) {
    Vertice *origem, *destino;
    buscarVerticePorNome(grafo, predador, &origem);
    buscarVerticePorNome(grafo, presa, &destino);

    if (origem == NULL || destino == NULL) return -1;

    inicilizarDijkstra(grafo, origem);

    //Cria a fila
    int tamanhoFila = qtdVertices(grafo);
    Vertice* fila[tamanhoFila];

    //Adiciona todos os vértices à fila
    Vertice* v = grafo->listaVertices;
    int i = 0;
    while (v != NULL) {
        fila[i] = v;
        i++;
        v = v->prox;
    }

    while (1) {
        Vertice* u = extrairVerticeComMenorCusto(fila, tamanhoFila);
        if (u == NULL) {
            break; //Fila vazia
        }

        if (u->custoCaminho == INFINITO) {
            //Não há mais caminhos viáveis
            break;
        }

        if (u == destino) {
            return u->custoCaminho; //Encontrado o caminho mínimo
        }

        //Relaxa todas as arestas de u
        Aresta* aresta = u->listaArestas;
        while (aresta != NULL) {
            if (aresta->destino != NULL) { //Proteção contra ponteiros nulos
                relaxamento(u, aresta->destino, aresta->peso);
            }
            aresta = aresta->prox;
        }
    }

    return -1; //Não há caminho para o destino

}
