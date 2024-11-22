#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "DFS.h"
#include "kosaraju.h"

int contaComponentes(Grafo *g) {
    int lixo, comp = 0, *inf, *counter, *ciclos;

    inf = (int*)calloc(1, sizeof(int));
    counter = (int*)calloc(1, sizeof(int));
    ciclos = (int*)calloc(1, sizeof(int));

    NoString *no;
    Vertice *vAtual;

    ListaString *li = criaListaStrings();
    ListaString *extra = criaListaStrings();
    Grafo *invG = inverteGrafo(g);

    // Busca DFS no grafo, gera lista de tempo de morte dos vertices
    contagemCiclos(g, li, &lixo);

    li = inverteLista(li);


    for(no = li->inicio; no != NULL; no=no->prox) {
        buscarVerticePorNome(invG, no->string, &vAtual);

        if(vAtual->visitado) continue;

        comp++;
        *inf = *counter;
        DFS(vAtual, extra, counter, inf, ciclos);
    }

    deletaListaStrings(li);
    deletaListaStrings(extra);
    deletaGrafo(invG);

    return comp;
}
