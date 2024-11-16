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
        ret = readRegisterSaveVertex(fp, registro, RRN);
        Animal* animal = criarAnimal(registro->data.name, registro->data.species, registro->data.habitat, registro->data.diet, registro->data.type, registro->data.population);
        //adicionarVertice(g, animal);

        RRN++;
    }

    return 0;
}