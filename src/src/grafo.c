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

    // Insere na lista de vértices
    novoVertice->prox = grafo->listaVertices;
    grafo->listaVertices = novoVertice;
}

// Função para adicionar uma aresta entre dois vértices
void adicionarAresta(Grafo* grafo, char* origem, char* destino, int peso) {
    Vertice* vOrigem = NULL;
    Vertice* vDestino = NULL;

    // Busca os vértices de origem e destino
    for (Vertice* v = grafo->listaVertices; v != NULL; v = v->prox) {
        if (strcmp(v->animal->nome, origem) == 0) {
            vOrigem = v;
        }
        if (strcmp(v->animal->nome, destino) == 0) {
            vDestino = v;
        }
    }

    if (vOrigem == NULL || vDestino == NULL) {
        printf("Erro: Vértice de origem ou destino não encontrado.\n");
        return;
    }

    // Cria a nova aresta
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = vDestino; // Aponta para o vértice
    novaAresta->peso = peso;
    novaAresta->prox = vOrigem->listaArestas;

    // Insere na lista de adjacências do vértice de origem
    vOrigem->listaArestas = novaAresta;

    // Atualiza os graus
    vOrigem->grauSaida++;
    vDestino->grauEntrada++;
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
