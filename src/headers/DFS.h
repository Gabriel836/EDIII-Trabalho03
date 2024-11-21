#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>
#include "LDES_strings.h"


int contagemCiclos(Grafo *grafo, int *comp);
void DFS(Vertice *v, int *counter, int *pos, int *inf, int *ciclos);