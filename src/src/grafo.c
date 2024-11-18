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
    //Mudanca no primeiro nó da lista
    else if(strcmp(novoVertice->animal->nome, ant->animal->nome) <= 0) {
        grafo->listaVertices = novoVertice;
        novoVertice->prox = ant;
        return;
    }
    //Inserção do vértice, em ordem alfabética
    else {
        prox = ant->prox;
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

    //Inserção da aresta, em ordem alfabética
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
    Vertice *v;
    Aresta *a;
    for (v = grafo->listaVertices; v != NULL; v = v->prox) {
        printf("Animal: %s\n", v->animal->nome);
        printf("  Arestas:");
        for (a = v->listaArestas; a != NULL; a = a->prox) {
            printf(" -> %s (peso: %d)", a->destino->animal->nome, a->peso);
        }
        printf("\n");
    }
}

void imprimirGrafoSintetico(Grafo *grafo) {
    Vertice *v;
    Aresta *a;
    for (v = grafo->listaVertices; v != NULL; v = v->prox) {
        if(v->animal->populacao == -1) continue;
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
            v->animal->populacao);
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
        if (strcmp(v->animal->nome, nome) == 0) {
            *ptr_vert = v;
            return;
        }
        v = v->prox;
    }

    return; // Não encontrou o vértice
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
