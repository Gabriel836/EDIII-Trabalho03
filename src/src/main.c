/*
Matheus Cavalcanti de Santana - 13217506
Gabriel Dezejácomo Maruschi - 14571525
*/

#include <stdio.h>
#include <string.h>
#include "funcoesPrincipais.h"
#include "grafo.h"
#include "funcoesAnalise.h"
#include "funcoesAuxiliares.h"

#define MAX_INPUT 300

int main() {

    FILE* dinoDataBin;

    //Read and parse the input
    char buff[MAX_INPUT], secBuff[MAX_INPUT];
    fgets(buff, MAX_INPUT, stdin);
    buff[strcspn(buff, "\n")] = '\0';
    
    char* cmdBuff;
    char* specsBuff;
    cmdBuff = strtok(buff, " ");
    specsBuff = strtok(NULL, " ");

    int cmd = strtol(cmdBuff, NULL, 10);

    char* fileR = specsBuff;
    char* nBuff;
    char *field, *value;
    int n, size;

    dinoDataBin = fopen(fileR, "rb");
    Grafo* g = criarGrafo();
    n = preencherGrafo(g, dinoDataBin);

    switch (cmd)
    {
    case 10:

        imprimirGrafoSintetico(g);

        break;
    case 11:
        char conjuntoBuscas[MAX_INPUT];
        
        extraiNomes(buff, conjuntoBuscas);
        value = strtok(conjuntoBuscas, "#");
        while(value != NULL) {
            listaPredadores(g, value);
            value = strtok(NULL, "#");
        }

        break;
    case 12:

        break;
    case 13:

        break;
    case 14:

        break;
    default:
        break;
    }
    fclose(dinoDataBin);
/*
    Grafo* grafo = criarGrafo();

    Animal* leao = criarAnimal("leao", "gatinho gatus", "africa", "carnivoro", "gato", 20);
    Animal* zebra = criarAnimal("zebra", "cavalo noir", "africa", "herbivoro", "juan", 30);

    adicionarVertice(grafo, leao);
    adicionarVertice(grafo, zebra);

    adicionarAresta(grafo, "leao", "zebra", 30);

    const char* nomeProcurado = "leao";
    Vertice* verticeEncontrado = buscarVerticePorNome(grafo, nomeProcurado);

    if (verticeEncontrado != NULL) {
        printf("Vértice encontrado: %s\n", verticeEncontrado->animal->nome);
    } else {
        printf("Vértice com nome '%s' não encontrado.\n", nomeProcurado);
    }

    imprimirGrafo(grafo);
*/
    return 0;
}
