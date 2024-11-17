#include <stdio.h>
#include <string.h>
#include "grafo.h"

// Função para criar um novo grafo
Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->listaVertices = NULL;
    return grafo;
}

// Função para criar um novo animal
Animal* criarAnimal(char* nome, char* especie, char* habitat,
                    char* dieta, char* tipo, int populacao) {
    Animal* novoAnimal = (Animal*)malloc(sizeof(Animal));
    strcpy(novoAnimal->nome, nome);
    strcpy(novoAnimal->especie, especie);
    strcpy(novoAnimal->habitat, habitat);
    strcpy(novoAnimal->dieta, dieta);
    strcpy(novoAnimal->tipo, tipo);
    novoAnimal->populacao = populacao;
    return novoAnimal;
}

// Função para criar um novo vértice
Vertice* criarVertice(Animal* animal) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    novoVertice->animal = animal;
    novoVertice->grauEntrada = 0;
    novoVertice->grauSaida = 0;
    novoVertice->listaArestas = NULL;
    novoVertice->prox = NULL;
    return novoVertice;
}

// Função para adicionar um vértice ao grafo
void adicionarVertice(Grafo* grafo, Animal* animal) {
    // Cria o novo vértice
    Vertice* novoVertice = criarVertice(animal);
    Vertice *prox, *ant;

    ant = grafo->listaVertices;
    //Grafo vazio  
    if(ant == NULL) {
        grafo->listaVertices = novoVertice;
        novoVertice->prox = NULL;
        return;
    }
    prox = ant->prox;
    //Mudanca no primeiro nó da lista
    if(strcmp(novoVertice->animal->nome, ant->animal->nome) <= 0) {
        grafo->listaVertices = novoVertice;
        novoVertice->prox = ant;
        return;
    }
    //Inserção do vértice, em ordem alfabética
    while(1) {
        if(strcmp(ant->animal->nome, novoVertice->animal->nome) < 0) {
            if(prox == NULL || strcmp(novoVertice->animal->nome, prox->animal->nome) < 0) {
                ant->prox = novoVertice;
                novoVertice->prox = prox;
                return;
            }
        }
        ant = ant->prox;
        prox = prox->prox;
    }
}

//Função para adicionar uma aresta entre dois vértices
void adicionarAresta(Grafo* grafo, Vertice* predador, Vertice* presa) {
    //Cria uma nova aresta e inicializa os campos
    Aresta* novaAresta = (Aresta*)calloc(1, sizeof(Aresta));

    novaAresta->destino = presa;
    novaAresta->peso = presa->animal->populacao;

    // Atualiza os graus de entrada e saída
    predador->grauSaida++;
    presa->grauEntrada++;

    Aresta *prox, *ant;

    ant = predador->listaArestas;
    //Vertice sem arestas
    if(ant == NULL) {
        predador->listaArestas = novaAresta;
        novaAresta->prox = NULL;
        return;
    }

    prox = ant->prox;
    //Mudanca no primeiro nó da lista (comp nome da nova aresta e nome do primeiro nó)
    if(strcmp(novaAresta->destino->animal->nome, ant->destino->animal->nome) <= 0) {
        predador->listaArestas = novaAresta; //novaAresta vira inicio da lista
        novaAresta->prox = ant; //prox de novaAresta recebe ant (antigo inicio da lista)
        return;
    }

    //Inserção do vértice, em ordem alfabética
    while(1) {
        if(strcmp(ant->destino->animal->nome, novaAresta->destino->animal->nome) < 0) {
            if(prox == NULL || strcmp(novaAresta->destino->animal->nome, prox->destino->animal->nome) < 0) {
                ant->prox = novaAresta;
                novaAresta->prox = prox;
                return;
            }
        }
        ant = ant->prox;
        prox = prox->prox;
    }

    return;
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    for (Vertice* v = grafo->listaVertices; v != NULL; v = v->prox) {
        printf("Animal: %s\n", v->animal->nome);
        printf("  Arestas:");
        for (Aresta* a = v->listaArestas; a != NULL; a = a->prox) {
            printf(" -> %s (peso: %d)", a->destino->animal->nome, a->peso);
        }
        printf("\n");
    }
}

//Função para buscar um vértice pelo nome do animal
Vertice* buscarVerticePorNome(Grafo* grafo, char* nome) {
    if (grafo == NULL || grafo->listaVertices == NULL) {
        return NULL; //Grafo vazio ou inválido
    }

    //Percorre a lista de vértices
    for (Vertice* v = grafo->listaVertices; v != NULL; v = v->prox) {
        if (strcmp(v->animal->nome, nome) == 0) {
            return v; //Retorna o endereço do vértice se encontrou
        }
    }

    return NULL; // Não encontrou o vértice
}

void imprimirAnimal(const Animal* animal) {
    if (animal == NULL) {
        printf("Animal não encontrado ou é nulo.\n");
        return;
    }

    printf("=== Dados do Animal ===\n");
    printf("Nome: %s\n", animal->nome);
    printf("Espécie: %s\n", animal->especie);
    printf("Habitat: %s\n", animal->habitat);
    printf("Dieta: %s\n", animal->dieta);
    printf("Tipo: %s\n", animal->tipo);
    printf("População: %d\n", animal->populacao);
    printf("========================\n");
}
