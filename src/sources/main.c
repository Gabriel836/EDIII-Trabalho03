#include <stdio.h>
#include "grafo.h"

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
