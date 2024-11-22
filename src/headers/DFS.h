#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>
#include "LDES_strings.h"

//O uso da Lista de String é justificado na implementacao do algoritmo de Kosaraju
int contagemCiclos(Grafo *grafo, ListaString *li, int *comp);
void DFS(Vertice *v, ListaString *li, int *counter, int *inf, int *ciclos);