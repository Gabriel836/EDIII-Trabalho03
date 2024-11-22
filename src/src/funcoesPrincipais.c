#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include "funcoesPrincipais.h"
#include "funcoesAuxiliares.h"
#include "LDES_strings.h"
#include "DFS.h"
#include "dijkstraAuxiliares.h"

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

void listaPredadores(Grafo *grafo, char* presa) {
    //Retorna se o grafo não existe 
    if(grafo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    ListaString *lista_predadores;

    lista_predadores = criaListaStrings();

    Vertice* vert_atual = grafo->listaVertices;
    Aresta* aresta_atual;
    
    //Verifica se o grafo está vazio
    if(vert_atual == NULL) {
        printf("Registro inexistente.\n");
        return;
    }

    //Percorre todos os vértices do grafo
    while(vert_atual != NULL) {
        aresta_atual = vert_atual->listaArestas;

        //Verificamos se a presa esta na lista de presas de cada predador
        while(aresta_atual != NULL) {
            //Caso este seja um predador de "presa", é inserido em uma LDES
            if(!strcmp(aresta_atual->destino->animal->nome, presa)) {
                insereNoStringsOrdenado(lista_predadores, vert_atual->animal->nome);
                break;
            }
            aresta_atual = aresta_atual->prox;
        }
        vert_atual = vert_atual->prox;
    }

    //Imprimindo resultados
    if(listaVazia(lista_predadores)) printf("Registro Inexistente.\n\n");
    else {
        printf("%s: ", presa);
        imprimeListaStrings(lista_predadores);
        printf("\n");
    }
    deletaListaStrings(lista_predadores); //Libera memória da lista
}

int contagemCiclos(Grafo *grafo, ListaString *li, int *comp) {
    int *counter, *pos, *inf, *ciclos, i = 0;

    *comp = 0; //Inicializa o número de componentes conexas

    //Aloca memória para as variáveis de controle
    counter = (int*)calloc(1, sizeof(int));
    ciclos = (int*)calloc(1, sizeof(int));

    *ciclos = 0;
    *counter = 0;

    inf = (int*)calloc(1, sizeof(int));

    Vertice *v;

    //Percorre todos os vértices do grafo
    for(v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->visitado) continue; //Ignora vértices já visitados

        i++; //Incrementa o número de componentes conexas
        *inf = *counter; //Atualiza o limite inferior de tempo

        DFS(v, li, counter, inf, ciclos); //Realiza a busca em profundidade
    }

    return *ciclos;
}

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

    //Busca DFS no grafo, gera lista de tempo de morte dos vertices
    contagemCiclos(g, li, &lixo);

    li = inverteLista(li); //Inverte a ordem de morte para usar no grafo invertido

    //Percorre os vértices na ordem inversa no grafo invertido
    for(no = li->inicio; no != NULL; no=no->prox) {
        buscarVerticePorNome(invG, no->string, &vAtual);

        if(vAtual->visitado) continue; //Ignora vértices já visitados

        comp++; //Incrementa o contador de componentes conexas
        *inf = *counter; //Atualiza o limite inferior de tempo
        DFS(vAtual, extra, counter, inf, ciclos); //Executa DFS no grafo invertido
    }

    //Libera memória alocada e estruturas temporárias
    deletaListaStrings(li);
    deletaListaStrings(extra);
    deletaGrafo(invG);

    return comp;
}

int dijkstra(Grafo* grafo, char* predador, char* presa) {
    Vertice *origem, *destino;

    //Busca os vértices correspondentes ao predador e à presa
    buscarVerticePorNome(grafo, predador, &origem);
    buscarVerticePorNome(grafo, presa, &destino);

    //Retorna -1 se um dos vértices não for encontrado
    if (origem == NULL || destino == NULL) return -1;

    //Inicializa os valores necessários para o algoritmo de Dijkstra
    inicilizarDijkstra(grafo, origem);

    //Cria uma fila de vertíces
    int tamanhoFila = qtdVertices(grafo);
    Vertice* fila[tamanhoFila];

    //Adiciona todos os vértices à fila
    Vertice* v = grafo->listaVertices;
    int i = 0;
    while (v != NULL) {
        fila[i] = v;
        i++;
        v = v->prox;
    }

    //Processa os vértices enquanto houverem na fila
    while (1) {
        //Extrai o vértice com menor custo da fila
        Vertice* u = extrairVerticeComMenorCusto(fila, tamanhoFila);
        if (u == NULL) { //Se o vertíce é nulo
            break; //Fila vazia
        }

        if (u->custoCaminho == INFINITO) { //Se o custo é infinito
            //Não há mais caminhos viáveis
            break;
        }

        if (u == destino) {
            return u->custoCaminho; //Encontrado o caminho mínimo
        }

        //Relaxa todas as arestas do vertíce atual
        Aresta* aresta = u->listaArestas;
        while (aresta != NULL) {
            if (aresta->destino != NULL) { //Proteção contra ponteiros nulos
                relaxamento(u, aresta->destino, aresta->peso);
            }
            aresta = aresta->prox;
        }
    }

    return -1; //Não há caminho para o destino

}