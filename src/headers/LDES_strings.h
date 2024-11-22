//Lista Encadeada Dinâmica Simples para Strings.
#ifndef __LISTA__
#define __LISTA__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

//Estrutura para representar um elemento da lista
typedef struct no_string {
    char string[MAX_CHAR];
    struct no_string *prox;
} NoString;

//Estrutura para representar a lista de strings
typedef struct Lista_strings {
    int n_elem;
    NoString *inicio;
} ListaString;

/// @brief Cria uma nova lista encadeada de strings.
/// @return Retorna um ponteiro para a nova lista criada.
ListaString* criaListaStrings();

/// @brief Insere uma string na lista em ordem alfabética.
/// @param li Ponteiro para a lista onde a string será inserida.
/// @param string String a ser inserida.
/// @return Retorna 0 em caso de sucesso, -1 se a lista for inválida ou 0 se a string já estiver presente.
int insereNoStringsOrdenado(ListaString *li, char *string);

/// @brief Insere uma string no final da lista, sem se preocupar com ordenação.
/// @param li Ponteiro para a lista onde a string será inserida.
/// @param string String a ser inserida.
/// @return Retorna 0 em caso de sucesso, -1 se a lista for inválida ou 0 se a string já estiver presente.
int insereNoStringsDireto(ListaString *li, char *string);

/// @brief Libera toda a memória associada a uma lista encadeada de strings.
/// @param li Ponteiro para a lista que será deletada.
/// @return Retorna 0 em caso de sucesso ou -1 se a lista for inválida.
int deletaListaStrings(ListaString *li);

/// @brief Imprime todos os elementos da lista de strings.
/// @param li Ponteiro para a lista a ser impressa.
/// @return Retorna 0 em caso de sucesso ou -1 se a lista for inválida.
int imprimeListaStrings(ListaString *li);

/// @brief Verifica se uma lista está vazia.
/// @param li Ponteiro para a lista a ser verificada.
/// @return Retorna 1 se a lista está vazia, 0 caso contrário e -1 se a lista for inválida.
int listaVazia(ListaString *li);

/// @brief Inverte a ordem dos elementos de uma lista encadeada de strings.
/// @param li Ponteiro para a lista que será invertida.
/// @return Retorna um ponteiro para uma nova lista invertida.
ListaString* inverteLista(ListaString *li);

/// @brief Verifica se uma string está presente na lista.
/// @param li Ponteiro para a lista onde a string será buscada.
/// @param str String a ser buscada.
/// @return Retorna um ponteiro para o nó que contém a string ou NULL se a string não for encontrada.
NoString* presenteNaLista(ListaString *li, char *str);

#endif