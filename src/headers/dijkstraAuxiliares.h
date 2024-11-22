#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include <limits.h>
#include "grafo.h"

#define INFINITO INT_MAX //"INFINITO" é o valor máximo para um int

/// @brief Conta a quantidade de vertíces presentes em um grafo.
/// @param g Ponteiro para o grafo.
/// @return Número de vertíces no grafo.
int qtdVertices(Grafo* g);

/// @brief Em uma fila de vertíces, retorna aquele com menor custo de caminho e o exclui da fila.
/// @param fila Ponteiro para a fila de vertíces.
/// @param tamanho Tamanho da fila de vertíces.
/// @return Ponteiro para o vertíce de menor custo.
Vertice* extrairVerticeComMenorCusto(Vertice** fila, int tamanho);

/// @brief Atualiza os campos "custoCaminho" e "predecessor" para execução do algoritmo de Dijkstra.
/// @param grafo Ponteiro para o grafo.
/// @param origem Vertíce de origem da busca.
void inicilizarDijkstra(Grafo* grafo, Vertice* origem);

/// @brief Faz o relaxamento de vertíces/arestas (atualiza o custo do caminho da origema até a aresta analisada).
/// @param origem Ponteiro para vertíce de origem.
/// @param destino Ponteiro para vertíce de destino.
/// @param pesoAresta Peso da aresta (origem, destino).
void relaxamento(Vertice* origem, Vertice* destino, int pesoAresta);

#endif