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

    ret = 0;
    while(ret == 0 || ret == -1) //while there is registers (-1 if removed or 0 if not removed)
    {
        Reg* registro;
        //Print registers and increment RRN
        ret = readRegisterSaveVertex(fp, &registro, RRN);
        //imprimirRegistro(registro);
        
        char* nomeProcurado = registro->data.name;
        Vertice* verticeEncontrado = buscarVerticePorNome(g, nomeProcurado);
        
        if(verticeEncontrado == NULL) {
            Animal* animal = criarAnimal(registro->data.name, registro->data.species, registro->data.habitat, registro->data.diet, registro->data.type, registro->data.population);
            //imprimirAnimal(animal);
            adicionarVertice(g, animal);
        }
        RRN++;
    }

    ret = 0;
    RRN = 0;
    while(ret == 0 || ret == -1)
    {
        Reg* registro;

        ret = readRegisterSaveVertex(fp, &registro, RRN);

        char* predadorProcurado = registro->data.name;
        char* presaProcurada = registro->data.food;
        Vertice* predadorEncontrado = buscarVerticePorNome(g, predadorProcurado);
        printf("predador encontrado. nome: %s end: %p", predadorEncontrado->animal->nome, predadorEncontrado);
        Vertice* presaEncontrada = buscarVerticePorNome(g, presaProcurada);
        printf("presa encontrada. nome: %s end: %p", presaEncontrada->animal->nome, presaEncontrada);

        if(predadorEncontrado != NULL && presaEncontrada != NULL) {
            adicionarAresta(g, predadorEncontrado, presaEncontrada);
        }
        RRN++;
    }

    return 0;
}