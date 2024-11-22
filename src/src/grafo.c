#include <stdio.h>
#include <string.h>
#include "grafo.h"

Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo)); //Aloca um novo grafo
    grafo->listaVertices = NULL; //Lista de vertíces vazia
    return grafo;
}

Animal* criarAnimal(char* nome, char* especie, char* habitat,
                    char* dieta, char* tipo, int populacao) {
    Animal* novoAnimal = (Animal*)malloc(sizeof(Animal)); //Aloca um novo animal
    //Inicializa campos com os dados forecidos
    strcpy(novoAnimal->nome, nome);
    strcpy(novoAnimal->especie, especie);
    strcpy(novoAnimal->habitat, habitat);
    strcpy(novoAnimal->dieta, dieta);
    strcpy(novoAnimal->tipo, tipo);
    novoAnimal->populacao = populacao;
    return novoAnimal;
}

Animal* copiaAnimal(Animal* original) {
    Animal* copia; 
    copia = criarAnimal( //Copia dos dados de um animal
        original->nome,
        original->especie,
        original->habitat,
        original->dieta,
        original->tipo,
        original->populacao
    );

    return copia;
}

Vertice* criarVertice(Animal* animal) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice)); //Aloca um novo vertíce
    //Inicializa o campo com os dados do animal e demais campos nulos
    novoVertice->animal = animal;
    novoVertice->grauEntrada = 0;
    novoVertice->grauSaida = 0;
    novoVertice->visitado = 0;
    novoVertice->custoCaminho = 0;
    novoVertice->predecessor = NULL;
    novoVertice->listaArestas = NULL;
    novoVertice->prox = NULL;
    return novoVertice;
}

Vertice* adicionarVertice(Grafo* grafo, Animal* animal) {
    //Aloca um novo vértice para o grafo
    Vertice* novoVertice = criarVertice(animal);
    Vertice *prox, *ant;

    //Caso o grafo esteja vazio, o novo vértice se torna o primeiro
    ant = grafo->listaVertices;
    if(ant == NULL) { 
        grafo->listaVertices = novoVertice;
        novoVertice->prox = NULL; //Não há próximos elementos
    }
    //Caso o nome do novo vértice seja menor ou igual ao do primeiro vértice atual,
    //ele será inserido no início da lista
    else if(strcmp(novoVertice->animal->nome, ant->animal->nome) <= 0) {
        grafo->listaVertices = novoVertice; //Atualiza o início da lista
        novoVertice->prox = ant; //Aponta para o antigo primeiro vértice
    }
    //Caso contrário, o vértice será inserido em ordem alfabética na lista
    else {
        prox = ant->prox; //Inicializa o ponteiro para o próximo nó
        while(1) {
            //Verifica se encontrou a posição correta para inserção
            if(strcmp(ant->animal->nome, novoVertice->animal->nome) < 0) {
                if(prox == NULL || strcmp(novoVertice->animal->nome, prox->animal->nome) < 0) {
                    //Insere o novo vértice entre 'ant' e 'prox'
                    ant->prox = novoVertice;
                    novoVertice->prox = prox;
                    return novoVertice;
                }
            }
            //Avança para o próximo nó na lista
            ant = ant->prox;
            prox = prox->prox;
        }
    }
    return novoVertice;  //Retorna o vértice adicionado
}

void adicionarAresta(Grafo* grafo, Vertice* predador, Vertice* presa, int peso) {
    //Cria uma nova aresta e inicializa os campos
    Aresta* novaAresta = (Aresta*)calloc(1, sizeof(Aresta));
    novaAresta->destino = presa;
    novaAresta->peso = peso;

    //Atualiza os graus de entrada e saída
    predador->grauSaida++;
    presa->grauEntrada++;

    Aresta *prox, *ant;

    //Caso o vértice não possua arestas, adiciona como primeira aresta
    ant = predador->listaArestas; //Inicializa o ponteiro para a próxima aresta
    if(ant == NULL) {
        predador->listaArestas = novaAresta;
        novaAresta->prox = NULL; //Não há próximas arestas
        return;
    }

    prox = ant->prox; //Inicializa o ponteiro para a próxima aresta
    //Mudanca no primeiro nó da lista (comparação do nome da nova aresta e nome do primeiro nó)
    if(strcmp(novaAresta->destino->animal->nome, ant->destino->animal->nome) <= 0) {
        predador->listaArestas = novaAresta; //novaAresta vira inicio da lista
        novaAresta->prox = ant; //'prox' de 'novaAresta' recebe 'ant' (antigo inicio da lista)
        return;
    }

    //Inserção da aresta, em ordem alfabética
    while(1) {
        //Verifica se encontrou a posição correta para inserção
        if(strcmp(ant->destino->animal->nome, novaAresta->destino->animal->nome) < 0) {
            if(prox == NULL || strcmp(novaAresta->destino->animal->nome, prox->destino->animal->nome) < 0) {
                //Insere a nova aresta entre 'ant' e 'prox'
                ant->prox = novaAresta;
                novaAresta->prox = prox;
                return;
            }
        }
        //Avança para a próxima aresta
        ant = ant->prox;
        prox = prox->prox;
    }

    return;
}

// Função para inversão do grafo
Grafo* inverteGrafo(Grafo* g) {
    //Ponteiros para percorrer o grafo original e construir o invertido
    Vertice *v, *novaOrigem, *novoDestino, *busca;
    Aresta *a;
    Animal *copia;
    Grafo* g_inv;
    g_inv = criarGrafo();
    g_inv->listaVertices = NULL;


    char nome[MAX_STR];

    //Copia todos os vértices do grafo original para o novo grafo
    for(v = g->listaVertices; v != NULL; v = v->prox) {
        copia = copiaAnimal(v->animal); //Cria uma cópia do animal associado ao vértice
        adicionarVertice(g_inv, copia); //Adiciona o vértice ao novo grafo
    }

    //Adicionamos arestas invertendo-as
    for(v = g->listaVertices; v != NULL; v = v->prox) {
        buscarVerticePorNome(g_inv, v->animal->nome, &novoDestino); //Localiza o vértice no novo grafo

        if(novoDestino != NULL) {
            for(a = v->listaArestas; a != NULL; a = a->prox) {
                buscarVerticePorNome(g_inv, a->destino->animal->nome, &novaOrigem); //Localiza o destino original
                adicionarAresta(g_inv, novaOrigem, novoDestino, novoDestino->animal->populacao); //Cria aresta invertida
            }
        }
    }
    return g_inv; //Retorna o grafo invertido
}

// Função para imprimir o grafo na forma sintética.
void imprimirGrafoSintetico(Grafo *grafo) {
    Vertice *v;
    Aresta *a;
    //Imprime informações sintéticas sobre o grafo
    for (v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->animal->populacao == -1) continue; // Ignora vértices com população inválida
        for(a = v->listaArestas; a != NULL; a = a->prox) {
            printf("%s %s %s %s %s %d %d %d %s %d\n",
            v->animal->nome,
            v->animal->especie,
            v->animal->habitat,
            v->animal->dieta,
            v->animal->tipo,
            v->grauEntrada,
            v->grauSaida,
            v->grauEntrada+v->grauSaida,
            a->destino->animal->nome,
            a->peso);
        }
    }
}

//Função para buscar um vértice pelo nome do animal
void buscarVerticePorNome(Grafo* grafo, char* nome, Vertice **ptr_vert) {
    if (grafo == NULL || grafo->listaVertices == NULL) {
        *ptr_vert = NULL; //Grafo vazio ou inválido
        return;
    }

    Vertice* v = grafo->listaVertices;
    //Percorre a lista de vértices
    while (v != NULL) {
        if (strcmp(v->animal->nome, nome) == 0) //ompara os nomes
        {
            *ptr_vert = v; //Se são iguais, retorna 'v'
            return;
        }
        v = v->prox;
    }

    *ptr_vert = NULL; //Não encontrou o vértice, retorna ponteiro nulo
    return;
}

int deletaGrafo(Grafo *grafo) {
    if(grafo == NULL) return 0;
    if(grafo->listaVertices == NULL) {
        free(grafo);
        return 0;
    }
    
    Vertice *vAtual, *vProx;
    Aresta *aAtual, *aProx;

    vAtual = grafo->listaVertices;
    while(vAtual != NULL) //Percorre a lista de vérticce
    {
        vProx = vAtual->prox;
        aAtual = vAtual->listaArestas;

        //Percorre a lista de arestas de um vertíce, liberando-as
        while(aAtual != NULL) {
            aProx = aAtual->prox;
            free(aAtual);
            aAtual = aProx;
        }

        //Libera a struct Animal e o vértice atual
        free(vAtual->animal);
        free(vAtual);
        vAtual = vProx;
    }
    free(grafo); //Libera o grafo
    return 0;
}