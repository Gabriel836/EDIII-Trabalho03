#include <stdio.h>

#include "grafo.h"
#include "funcoesPrincipais.h"
#include "funcoesAuxiliares.h"

int preencherGrafo(Grafo* g, FILE* fp) {
    
    char *ptrStr, stat;
    int diskP, RRN = 0, ret;

    //Check if the file exists
    int fCheck = checkFileExistence(fp);
    if (fCheck == -1)
        return fCheck;
    
    //Check if the file is consistent
    fCheck = checkFileConsistency(fp);
    if (fCheck == -1)
        return fCheck;

    //Read the number of disk pages
    fseek(fp, 13, SEEK_SET);
    fread(&diskP, sizeof(int), 1, fp);
    if(diskP == 1) { //If there is only the header page (0 registers), return
        printRegNotFoundMessage(); //OU PRINTAR A MENSAGEM DE ERRO DE ARQUIVO
        //printFileErrorMessage();
        return -1;
    }

    Reg* registro;
    ret = 0;
    while(ret == 0 || ret == -1) //while there is registers (-1 if removed or 0 if not removed)
    {
        //Print registers and increment RRN
        ret = readRegisterSaveVertex(fp, &registro, RRN);
        if(ret == -1) {
            RRN++;
            continue;
        }
        else if(ret == 2) break;
        //imprimirRegistro(registro);
        
        char* nomeProcurado = registro->data.name;
        Vertice* verticeEncontrado;
        buscarVerticePorNome(g, nomeProcurado, &verticeEncontrado);
        
        if(verticeEncontrado == NULL) {
            Animal* animal = criarAnimal(registro->data.name, registro->data.species, registro->data.habitat, registro->data.diet, registro->data.type, registro->data.population);
            //imprimirAnimal(animal);
            adicionarVertice(g, animal);
        }
        RRN++;
    }

    //imprimeVertices(g);

    ret = 0;
    RRN = 0;
    char predadorProcurado[MAX_STR], presaProcurada[MAX_STR];
    Vertice *predadorEncontrado, *presaEncontrada;

    printf("arestas\n");
    while(ret == 0 || ret == -1)
    {

        predadorEncontrado = NULL;
        presaEncontrada = NULL;

        ret = readRegisterSaveVertex(fp, &registro, RRN);

        printf("\nimprimindo registro\n");
        imprimirRegistro(registro);

        if(ret == -1) {
            RRN++;
            continue;
        }
        strcpy(predadorProcurado, registro->data.name);
        strcpy(presaProcurada, registro->data.food);

        printf("valores strcpy: predador: %s, presa: %s\n", predadorProcurado, presaProcurada);

        buscarVerticePorNome(g, predadorProcurado, &predadorEncontrado);
        buscarVerticePorNome(g, presaProcurada, &presaEncontrada);

        printf("Predador encontrado. nome %s\n", predadorEncontrado->animal->nome);

        // Caso a presa não possua registro no binario
        if(presaEncontrada == NULL) {
            Animal* presa = criarAnimal(presaProcurada, "\0", "\0", "\0", "\0", 0);
            adicionarVertice(g, presa);
            buscarVerticePorNome(g, presaProcurada, &presaEncontrada);
        }
        printf("Presa encontrada. nome %s\n", presaEncontrada->animal->nome);

        if(predadorEncontrado != NULL && presaEncontrada != NULL) {
            adicionarAresta(g, predadorEncontrado, presaEncontrada);
        }
        RRN++;
    }

    return 0;
}