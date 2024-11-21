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

// Estrutura para representar um vértice
struct Vertice; // Forward declaration

// Estrutura para representar uma aresta (conexão)
typedef struct Aresta {
    struct Vertice* destino; // Agora aponta para um vértice
    int peso;
    struct Aresta* prox;
} Aresta;

// Estrutura para representar um vértice
typedef struct Vertice {
    Animal* animal;
    int grauEntrada;
    int grauSaida;
    int visitado;
    int tempo[2];
    Aresta* listaArestas; // Lista encadeada de arestas
    struct Vertice* prox;
} Vertice;

// Estrutura para representar um grafo
typedef struct Grafo {
    Vertice* listaVertices; // Lista encadeada de vértices
} Grafo;

Grafo* criarGrafo();
Grafo* inverteGrafo(Grafo* g);
Animal* criarAnimal(char* nome, char* especie, char* habitat, char* dieta, char* tipo,int populacao);
Animal* copiaAnimal(Animal* original);
Vertice* criarVertice(Animal* animal);
Vertice* adicionarVertice(Grafo* grafo, Animal* animal);
void adicionarAresta(Grafo* grafo, Vertice* predador, Vertice* presa, int peso);
void imprimirGrafo(Grafo* grafo);
void imprimirGrafoSintetico(Grafo *grafo);
void imprimirAnimal(const Animal* animal);
void buscarVerticePorNome(Grafo* grafo, char* nome, Vertice **ptr_vert);

#endif