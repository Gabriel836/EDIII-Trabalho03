#ifndef __PRINCIPAIS__
#define __PRINCIPAIS__

#include "grafo.h"
#include "LDES_strings.h"

/// @brief Lê registros de um arquivo binário e cria um grafo baseado nos dados.
/// @param g Ponteiro para um grafo a ser preenchido.
/// @param fp Ponteiro para um arquivo de entrada com os dados para inserção.
void preencherGrafo(Grafo* g, FILE* fp);

/// @brief Imprime a lista de predadores de uma presa específica no grafo.
/// @param grafo Ponteiro para o grafo a ser analisado.
/// @param presa Nome da presa (sem aspas) para a qual os predadores serão listados.
/// @return Não possui retorno explícito; imprime os resultados no terminal.
void listaPredadores(Grafo *grafo, char* presa);

/// @brief Conta o número de ciclos existentes em um grafo utilizando busca em profundidade (DFS).
/// @param grafo Ponteiro para o grafo a ser analisado.
/// @param li Ponteiro para uma lista de strings que armazenará os vértices na ordem de visita.
/// @param comp Ponteiro para o número de componentes conexas (inicializado fora da função).
/// @return Retorna o número de ciclos encontrados no grafo.
int contagemCiclos(Grafo *grafo, ListaString *li, int *comp);

/// @brief Conta o número de componentes fortemente conexas em um grafo orientado.
/// @param g Ponteiro para o grafo a ser analisado.
/// @return Retorna o número de componentes fortemente conexas do grafo.
int contaComponentes(Grafo* g);

/// @brief Calcula o custo do camnho mínimo de um vértice origem até um de destino.
/// @param grafo Ponteiro para um grafo.
/// @param predador Nome do vertíce de origem.
/// @param presa Nome do vertíce de destino.
/// @return Custo do caminho mínimo entre origem e destino.
int dijkstra(Grafo* grafo, char* predador, char* presa);

#endif