#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "cidade.h"
#include "lista.h"
#include "item.h"

typedef int unsigned int;

void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int distancia_calcular(LISTA *cidades, int rota[], int n) {
    int totalDist = 0;
    for (int i = 0; i < n; i++){
        ITEM* item = lista_busca(cidades, rota[i]);
        if (item == NULL){
            return INT_MAX;
        }
        CIDADE* c = (CIDADE*) item_get_dados(item);
        int dist = cidade_dist(c, rota[(i+1) % n]);
        if (dist == INT_MAX) return INT_MAX;
        totalDist += dist;
    }
    return totalDist;
}

int copia_vetor(int origem[], int destino[], int dist){
    for(int i = 0; i < dist; i++){
        destino[i] = origem[i];
    }
}

void permuta(LISTA* cidades, int rota[], int ini, int fim, int minRota[], int *minDist, int n){
    if(ini == fim){
        int curDist = distancia_calcular(cidades, rota, n);
        if(curDist < *minDist){
            *minDist = curDist;
            copia_vetor(rota, minRota, n);
        }
    } else {
        for (int i = ini; i <= fim; i++){
            troca((rota+ini), (rota+i));
            permuta(cidades, rota, ini+1, fim, minRota, minDist, n);
            troca((rota+ini), (rota+i));
        }
    }
}

void tsp(LISTA *cidades, int n, int origem) {
    int rota[n];
    int minRota[n];
    int minDist = INT_MAX;

    for (int i = 0; i < n; i++) {
        ITEM *cidade = lista_busca(cidades, i + 1);
        if (cidade) {
            rota[i] = item_get_chave(cidade);
        }
    }

    permuta(cidades, rota, origem, n - 1, minRota, &minDist, n);

    printf("Rota: ");
    for (int i = 0; i < n; i++) {
        printf("%u -> ", minRota[i]);
    }
    printf("%u\n", origem);
    printf("Distância: %u\n", minDist);
}

int main(void) { 
    int n, ini, caminhos;
    scanf("%u", &n);
    scanf("%u", &ini);
    scanf("%u", &caminhos);

    LISTA* l = lista_criar(false);
    if (l == NULL) return 1;
    for(int i = 1; i <= n; i++){
        CIDADE* c = cidade_criar(i+1); 
        if (c == NULL) return 1;
        ITEM *item = item_criar(i+1, c); 
        if (item == NULL) return 1;
        lista_inserir(l, item);
    }
    for(int i = 1; i <= caminhos; i++){
        int a, b, dist;
        scanf("%u %u %u", &a, &b, &dist);
        CIDADE* cA = (CIDADE*) item_get_dados(lista_busca(l, a));
        CIDADE* cB = (CIDADE*) item_get_dados(lista_busca(l, b));
        cidade_con(cA, cB, dist);
    }

    tsp(l, n, ini);

    lista_apagar(&l);
}
