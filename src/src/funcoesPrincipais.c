#include <stdio.h>

#include "grafo.h"
#include "funcoesPrincipais.h"
#include "funcoesAuxiliares.h"

void preencherGrafo(Grafo* g, FILE* fp) {
    
    int diskP = 0, RRN = 0, ret = 0;

    //Checa a existência do arquivo
    int fCheck = checkFileExistence(fp);
    if (fCheck == -1)
        return;
    
    //Checa a consistência do arquivo
    fCheck = checkFileConsistency(fp);
    if (fCheck == -1)
        return;

    //Lê o número de páginas de disco
    fseek(fp, 13, SEEK_SET);
    fread(&diskP, sizeof(int), 1, fp);
    if(diskP == 1) { //Se há apenas uma página (0 registros)
        printFileErrorMessage();
        return;
    }

    //Auxiliares para leitura de registros e inserção de vertíces
    Reg* registro;
    Vertice* verticeEncontrado;

    while(ret == 0 || ret == -1) //Enquanto há registros(-1 se removido ou 0 se não removido)
    {
        //Lê um registro e armazená-o
        ret = readRegisterSaveVertex(fp, &registro, RRN);
        if(ret == -1) //Se foi removido, incrementa o RRN e continua
        { 
            RRN++;
            continue;
        }
        else if(ret == 2) break; //Se chegou ao fim do arquivo, para
        
        //Verifica se o vertíce a ser inserido já está no grafo (para evitar vértices repetidos)
        char* nomeProcurado = registro->data.name;
        verticeEncontrado = NULL;
        buscarVerticePorNome(g, nomeProcurado, &verticeEncontrado);

        //Se não está, o adiciona no grafo
        if(verticeEncontrado == NULL) 
        {
            //Cria struct de dados do vertíce
            Animal* animal = criarAnimal(
                registro->data.name, 
                registro->data.species, 
                registro->data.habitat, 
                registro->data.diet, 
                registro->data.type, 
                registro->data.population);
            adicionarVertice(g, animal); //Cria o vertíce com dados e demais campos
        }
        RRN++;
    }

    ret = 0;
    RRN = 0;
    //Auxiliares para leitura de registros e inserção de arestas
    char predadorProcurado[MAX_STR], presaProcurada[MAX_STR];
    Vertice *predadorEncontrado, *presaEncontrada;

    while(ret == 0 || ret == -1)
    {
        predadorEncontrado = NULL;
        presaEncontrada = NULL;

        ret = readRegisterSaveVertex(fp, &registro, RRN); //Leitura de registro

        if(ret == -1) //Trata removidos e fim do arquivo
        {
            RRN++;
            continue;
        }
        else if(ret == 2) break;
        
        strcpy(predadorProcurado, registro->data.name);
        strcpy(presaProcurada, registro->data.food);

        //Busca pelo vertíce do predador e da presa
        buscarVerticePorNome(g, predadorProcurado, &predadorEncontrado);
        buscarVerticePorNome(g, presaProcurada, &presaEncontrada);
        
        //Caso a presa não possua registro no binário (e no grafo), cria um vertice para ela com o nome lido e demais campos nulos
        if(presaEncontrada == NULL) {
            Animal* presa = criarAnimal(presaProcurada, "\0", "\0", "\0", "\0", 0);
            adicionarVertice(g, presa);
            buscarVerticePorNome(g, presaProcurada, &presaEncontrada);
        }

        //Se ambos estão presentes no binário (e no grafo), é criada a aresta
        if(predadorEncontrado != NULL && presaEncontrada != NULL) {
            adicionarAresta(g, predadorEncontrado, presaEncontrada, registro->data.population);
        }
        RRN++;
    }

    return;
}