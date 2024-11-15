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

//Função para criar um novo grafo
Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->listaVertices = NULL;
    return grafo;
}

Animal* criarAnimal(const char* nome, const char* especie, const char* habitat,
                    const char* dieta, const char* tipo) {
    Animal* novoAnimal = (Animal*)malloc(sizeof(Animal));
    strncpy(novoAnimal->nome, nome, MAX_STR);
    strncpy(novoAnimal->especie, especie, MAX_STR);
    strncpy(novoAnimal->habitat, habitat, MAX_STR);
    strncpy(novoAnimal->dieta, dieta, MAX_STR);
    strncpy(novoAnimal->tipo, tipo, MAX_STR);
    return novoAnimal;
}

//Função para criar um novo vértice
Vertice* criarVertice(Animal* animal) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    novoVertice->animal = animal;
    novoVertice->grauEntrada = 0;
    novoVertice->grauSaida = 0;
    novoVertice->listaArestas = NULL;
    novoVertice->prox = NULL;
    return novoVertice;
}

//Função para adicionar um vértice ao grafo
void adicionarVertice(Grafo* grafo, Animal* animal) {
    //Cria o novo vértice
    Vertice* novoVertice = criarVertice(animal);

    //Insere na lista de vértices
    novoVertice->prox = grafo->listaVertices;
    grafo->listaVertices = novoVertice;
}

//Função para adicionar uma aresta entre dois vértices
void adicionarAresta(Grafo* grafo, const char* origem, const char* destino, int peso) {
    Vertice* vOrigem = NULL;
    Vertice* vDestino = NULL;

    //Busca os vértices de origem e destino
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

    //Cria a nova aresta
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = vDestino->animal;
    novaAresta->peso = peso;
    novaAresta->prox = vOrigem->listaArestas;

    //Insere na lista de adjacências do vértice de origem
    vOrigem->listaArestas = novaAresta;//Função para criar um novo animal

    //Atualiza os graus
    vOrigem->grauSaida++;
    vDestino->grauEntrada++;
}

void imprimirGrafo(Grafo* grafo) {
    for (Vertice* v = grafo->listaVertices; v != NULL; v = v->prox) {
        printf("Animal: %s\n", v->animal->nome);
        printf("  Arestas:");
        for (Aresta* a = v->listaArestas; a != NULL; a = a->prox) {
            printf(" -> %s (peso: %d)", a->destino->nome, a->peso);
        }
        printf("\n");
    }
}

int main() {
    Grafo* grafo = criarGrafo();

    Animal* leao = criarAnimal("leao", "gatinho gatus", "africa", "carnivoro", "gato");
    Animal* zebra = criarAnimal("zebra", "cavalo noir", "africa", "herbivoro", "juan");

    adicionarVertice(grafo, leao);
    adicionarVertice(grafo, zebra);

    adicionarAresta(grafo, "leao", "zebra", 30);

    imprimirGrafo(grafo);

    return 0;
}
