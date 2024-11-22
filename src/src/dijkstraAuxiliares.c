#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstraAuxiliares.h"

int qtdVertices(Grafo* g) {
    int tam = 0;
    Vertice* v;

    //Percorre a lista de vértices do grafo e conta o número de vértices
    for (v = g->listaVertices; v != NULL; v = v->prox)
        tam++;

    return tam; 
}

void inicilizarDijkstra(Grafo* grafo, Vertice* origem) {
    Vertice *v;

    //Inicializa os custos e predecessores de todos os vértices
    for (v = grafo->listaVertices; v != NULL; v = v->prox) {
        if (strcmp(v->animal->nome, origem->animal->nome) == 0)
            v->custoCaminho = 0; //Define o custo do vértice origem como 0
        else
            v->custoCaminho = INFINITO; //Outros vértices começam com custo infinito
        v->predecessor = NULL; //Nenhum predecessor inicial
    }

    return;
}

void relaxamento(Vertice* origem, Vertice* destino, int pesoAresta) {
    //"Relaxa" a aresta (atualiza o custo do caminho até a origem) se encontrar um caminho mais curto para o destino
    if (destino->custoCaminho > origem->custoCaminho + pesoAresta) {
        destino->custoCaminho = origem->custoCaminho + pesoAresta;
        destino->predecessor = origem; // Atualiza o predecessor
    }

    return;
}

//Função auxiliar para encontrar o vértice com menor custo
Vertice* extrairVerticeComMenorCusto(Vertice** fila, int tamanho) {
    int menorIndice = -1;
    int menorCusto = INFINITO;

    //Percorre a fila para encontrar o vértice com menor custo
    for (int i = 0; i < tamanho; i++) {
        if (fila[i] != NULL && fila[i]->custoCaminho < menorCusto) {
            menorCusto = fila[i]->custoCaminho;
            menorIndice = i;
        }
    }

    //Remove e retorna o vértice com menor custo
    if (menorIndice != -1) {
        Vertice* menorVertice = fila[menorIndice];
        fila[menorIndice] = NULL; //Remove da fila
        return menorVertice;
    }

    return NULL; //Nenhum vértice restante
}