/*
Matheus Cavalcanti de Santana - 13217506
Gabriel Dezejácomo Maruschi - 14571525
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "funcoesPrincipais.h"
#include "grafo.h"
#include "funcoesAnalise.h"
#include "funcoesAuxiliares.h"
#include "DFS.h"
#include "dijkstra.h"
#include "kosaraju.h"

#define MAX_INPUT 300

int main() {


    setlocale(LC_ALL, "Portuguese");
    FILE* dinoDataBin;

    //Leitura da string de entrada
    char buff[MAX_INPUT], secBuff[MAX_INPUT];
    fgets(buff, MAX_INPUT, stdin);
    buff[strcspn(buff, "\n")] = '\0';
    
    //Separação dos campos função e arquivo da string de entrada 
    char* cmdBuff;
    char* specsBuff;
    cmdBuff = strtok(buff, " ");
    specsBuff = strtok(NULL, " ");

    int k, comp, cmd = strtol(cmdBuff, NULL, 10);

    char* fileR = specsBuff;

    dinoDataBin = fopen(fileR, "rb"); //Abertura do arquivo

    //Variáveis auxiliares para leitura de entrada e retornos
    char* nBuff;
    char *value;
    int n;

    //Criação do grafo
    Grafo* g = criarGrafo();
    ListaString *li = criaListaStrings();
    preencherGrafo(g, dinoDataBin); 

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
            listaPredadores(g, value); //Lista os predadores de uma presa
            value = strtok(NULL, "#");
        }

        break;
    case 12:

        k = contagemCiclos(g, li, &comp);
        printf("Quantidade de ciclos: %d\n", k);

        break;
    case 13:

        k = contaComponentes(g);
        if(comp != 1) {
            printf("Não, o grafo não é fortemente conexo e possui %d componentes.\n", k);
        }
        else {
            printf("Sim, o grafo é fortemente conexo e possui %d componente.\n", k);
        }

        break;
    case 14:

        nBuff = strtok(NULL, " "); //Extrai número de inputs ("origem" "destino")
        n = strtol(nBuff, NULL, 10); //atoi

        //Retira aspas e substitui espaços por # da entrada
        char inputBuff[MAX_INPUT];
        extraiNomes(buff, inputBuff);

        char* origemBuff;
        char* destinoBuff;

        for(int i = 0; i < n; i++)
        {
            //Extrando o par de entradas "origem" "destino"
            if (i == 0) {
                origemBuff = strtok(inputBuff, "#");
                destinoBuff = strtok(NULL, "#");
            } 
            else {
                origemBuff = strtok(NULL, "#");
                destinoBuff = strtok(NULL, "#");
            }

            int custo = dijkstra(g, origemBuff, destinoBuff); //Cálculo do menor custo
            
            if (custo == -1) {
                printf("%s %s: CAMINHO INEXISTENTE\n", origemBuff, destinoBuff);
            } else {
                printf("%s %s: %d\n", origemBuff, destinoBuff, custo);
            }
        }   

        break;
    default:
        break;
    }

    deletaGrafo(g);
    fclose(dinoDataBin);
    deletaListaStrings(li);

    return 0;
}
