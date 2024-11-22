#ifndef __DFS__
#define __DFS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "LDES_strings.h" //O uso da Lista de String é justificado na implementação do algoritmo de Kosaraju

/// @brief Executa uma busca em profundidade (DFS - Depth-First Search) a partir de um vértice.
/// @param v Ponteiro para o vértice inicial da busca.
/// @param li Ponteiro para uma lista de strings onde os nomes dos vértices visitados serão armazenados.
/// @param counter Ponteiro para um contador usado para marcar o tempo de visitação dos vértices.
/// @param inf Ponteiro para o limite inferior de tempo usado para identificar ciclos.
/// @param ciclos Ponteiro para o contador de ciclos detectados no grafo.
/// @return Não possui retorno explícito; a função modifica os parâmetros passados por referência.
void DFS(Vertice *v, ListaString *li, int *counter, int *inf, int *ciclos);

#endif