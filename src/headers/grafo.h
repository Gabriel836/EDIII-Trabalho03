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

struct Vertice; //Declaração prévia de Vertice

//Estrutura para representar uma aresta (conexão)
typedef struct Aresta {
    struct Vertice* destino;
    int peso;
    struct Aresta* prox;
} Aresta;

//Estrutura para representar um vértice
typedef struct Vertice {
    Animal* animal;
    int grauEntrada;
    int grauSaida;
    int visitado;
    int tempo;
    int custoCaminho;
    struct Vertice* predecessor;
    Aresta* listaArestas; //Lista encadeada de arestas
    struct Vertice* prox;
} Vertice;

//Estrutura para representar um grafo
typedef struct Grafo {
    Vertice* listaVertices; //Lista encadeada de vértices
} Grafo;

/// @brief Cria um grafo vazio.
/// @return Retorna um ponteiro para o grafo alocado.
Grafo* criarGrafo();

/// @brief Inverte todas as arestas do grafo fornecido.
/// @param g Ponteiro para o grafo original que será invertido.
/// @return Retorna um ponteiro para o novo grafo com as arestas invertidas.
Grafo* inverteGrafo(Grafo* g);

/// @brief Cria um novo registro de animal com os dados fornecidos.
/// @param nome Nome do animal.
/// @param especie Espécie do animal.
/// @param habitat Habitat do animal.
/// @param dieta Dieta do animal.
/// @param tipo Tipo do animal (carnívoro, herbívoro, etc.).
/// @param populacao População do animal.
/// @return Retorna um ponteiro para o animal criado.
Animal* criarAnimal(char* nome, char* especie, char* habitat, char* dieta, char* tipo,int populacao);

/// @brief Cria uma cópia de um registro de animal.
/// @param original Ponteiro para o registro do animal a ser copiado.
/// @return Retorna um ponteiro para a cópia do animal.
Animal* copiaAnimal(Animal* original);

/// @brief Cria um vértice a partir de um registro de animal.
/// @param animal Ponteiro para o animal associado ao vértice.
/// @return Retorna um ponteiro para o vértice criado.
Vertice* criarVertice(Animal* animal);

/// @brief Adiciona um novo vértice ao grafo em ordem alfabética, baseado no nome do animal.
/// @param grafo Ponteiro para o grafo onde o vértice será adicionado.
/// @param animal Ponteiro para o animal que será associado ao vértice.
/// @return Retorna um ponteiro para o vértice adicionado.
Vertice* adicionarVertice(Grafo* grafo, Animal* animal);

/// @brief Adiciona uma aresta entre dois vértices do grafo.
/// @param grafo Ponteiro para o grafo onde a aresta será adicionada.
/// @param predador Ponteiro para o vértice de origem (predador).
/// @param presa Ponteiro para o vértice de destino (presa).
/// @param peso Peso da aresta (representa a intensidade da relação entre predador e presa).
void adicionarAresta(Grafo* grafo, Vertice* predador, Vertice* presa, int peso);

/// @brief Imprime uma representação simplificada do grafo, listando conexões e atributos dos vértices e arestas.
/// @param grafo Ponteiro para o grafo a ser impresso.
void imprimirGrafoSintetico(Grafo *grafo);

/// @brief Busca um vértice no grafo pelo nome do animal associado.
/// @param grafo Ponteiro para o grafo onde será feita a busca.
/// @param nome Nome do animal a ser buscado.
/// @param ptr_vert Ponteiro de saída que será atualizado com o vértice encontrado (ou NULL se não for encontrado).
void buscarVerticePorNome(Grafo* grafo, char* nome, Vertice **ptr_vert);

/// @brief Libera toda a memória associada ao grafo, incluindo vértices, arestas e registros de animais.
/// @param grafo Ponteiro para o grafo a ser deletado.
/// @return Retorna 0 após a exclusão do grafo.
int deletaGrafo(Grafo *grafo);

#endif