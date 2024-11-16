#ifndef __GRAFO__
#define __GRAFO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

//Estrutura para representar um animal
typedef struct Animal {
    char nome[MAX_STR];
    char especie[MAX_STR];
    char habitat[MAX_STR];
    char dieta[MAX_STR];
    char tipo[MAX_STR];
    int populacao;
} Animal;

//Estrutura para representar uma aresta (conexão)
typedef struct Aresta {
    Animal* destino;
    int peso;
    struct Aresta* prox;
} Aresta;

//Estrutura para representar um vértice
typedef struct Vertice {
    Animal* animal;
    int grauEntrada;
    int grauSaida;
    Aresta* listaArestas; //Lista encadeada de arestas
    struct Vertice* prox;
} Vertice;

//Estrutura para representar um grafo
typedef struct Grafo {
    Vertice* listaVertices; //Lista encadeada de vértices
} Grafo;

Grafo* criarGrafo();
Animal* criarAnimal(const char* nome, const char* especie, const char* habitat, const char* dieta, const char* tipo, const int populacao);
Vertice* criarVertice(Animal* animal);
void adicionarVertice(Grafo* grafo, Animal* animal);
void adicionarAresta(Grafo* grafo, const char* origem, const char* destino, int peso);
void imprimirGrafo(Grafo* grafo);

#endif