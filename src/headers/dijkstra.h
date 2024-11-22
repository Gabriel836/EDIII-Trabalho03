#include "grafo.h"

#define INFINITO INT_MAX

int qtdVertices(Grafo* g);
Vertice* extrairVerticeComMenorCusto(Vertice** fila, int tamanho);
void inicilizarDijkstra(Grafo* grafo, Vertice* origem);
void relaxamento(Vertice* origem, Vertice* destino, int pesoAresta);
int dijkstra(Grafo* grafo, char* predador, char* presa);

