#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DFS.h"
#include "grafo.h"

void DFS(Vertice *v, ListaString *li, int *counter, int *inf, int *ciclos) {
    Aresta* prox; //Ponteiro para percorrer as arestas do vértice atual
    (*counter)++; //Incrementa o contador de tempo

    v->visitado = 1; //Marca o vértice como visitado
    v->tempo = *counter; //Define o tempo de visitação do vértice

    //Caso o vértice não tenha arestas descendentes, insere seu nome na lista e retorna
    if(v->listaArestas == NULL) {
        insereNoStringsDireto(li, v->animal->nome);
        return;
    } 

    //Percorre todas as arestas do vértice
    for(prox = v->listaArestas; prox != NULL; prox = prox->prox) {
        //Se o destino já foi visitado nesta iteração da sub-árvore e está dentro do intervalo de tempo, detecta um ciclo
        if(prox->destino->visitado && prox->destino->tempo > *inf) {
            (*ciclos)++; //Incrementa o contador de ciclos
            continue; //Ignora a aresta e segue para a próxima
        }
        //Caso o vértice destino ainda não tenha sido visitado, realiza a DFS recursivamente
        else if(prox->destino->visitado == 0) {
            DFS(prox->destino, li, counter, inf, ciclos);
        }
    }
    // Após visitar todos os descendentes, insere o nome do vértice na lista e retorna
    insereNoStringsDireto(li, v->animal->nome);
    return;
}