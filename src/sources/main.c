#include <stdio.h>
#include "grafo.h"
#include "funcoesAuxiliares.h"
#include "funcoesAnalise.h"

int main() {
    char nomeArq[MAX_STR], str[MAX_STR];
    int cmd, n;
    Grafo *grafo;

    scanf("%s %d", nomeArq, &cmd);

    switch(cmd) {
        case 10:
            //codigo
        
        case 11:
            //gerar grafo
            grafo = criarGrafo();
            scanf("%d", &n);

            for(int i = 0; i < n; i++) {
                fgets(str, MAX_STR, stdin);
                removequotes(str);
                
            }
    }

    return 0;
}
