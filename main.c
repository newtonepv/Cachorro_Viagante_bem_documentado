#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "cidade.h"
#include "lista.h"
#include "item.h"


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
            printf("Cidade com chave %d não encontrada\n", rota[i]);
            return INT_MAX;
        }
        CIDADE* c = (CIDADE*) item_get_dados(item);
        int prox = rota[(i + 1) % n];
        int dist = cidade_dist(c, prox);
        if (dist == INT_MAX) {
            return INT_MAX;
        }
        totalDist += dist;
    }
    return totalDist;
}


int copia_vetor(int origem[], int destino[], int dist){
    for(int i = 0; i < dist; i++){
        destino[i] = origem[i];
    }
}

void roda_vetor(int vetor[], int comprimento, int origem){
    while(vetor[0] != origem){
        int aux = vetor[0];
        for(int i = 1; i < comprimento; i++){
            vetor[i-1] = vetor[i];
        }
        vetor[comprimento-1] = aux;
    }
}

void permutar_cidades_calcula_min_rota(LISTA* cidades, int rota[], int ini, int fim, int minRota[], int *minDist, int n){
    if(ini == fim){
        int curDist = distancia_calcular(cidades, rota, n);
        if(curDist < *minDist){
            *minDist = curDist;
            copia_vetor(rota, minRota, n);
        }
    } else {
        for (int i = ini; i <= fim; i++){
            troca((rota + ini), (rota + i));
            permutar_cidades_calcula_min_rota
        (cidades, rota, ini+1, fim, minRota, minDist, n);
            troca((rota+ini), (rota+i));
        }
    }
}

void tsp(LISTA *cidades, int n, int origem) {
    int rota[n];
    int minRota[n];
    int minDist = INT_MAX;

    for (int i = 0; i < n; i++) {
        fflush(stdout);
        ITEM *cidade = lista_busca(cidades, i + 1);
        if (cidade) {
            rota[i] = item_get_chave(cidade);
            fflush(stdout);
        }
    }
    permutar_cidades_calcula_min_rota
(cidades, rota, 1, n - 1, minRota, &minDist, n);
    roda_vetor(minRota, n, origem);
    printf("Cidade Origem: %d\n", origem);
    printf("Rota: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", minRota[i]);
    }
    printf("%d\n", minRota[0]);
    printf("Distância: %d\n", minDist);
}

int main(int argc, char *argv[]) { 
    if(argc < 2){
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        return 1;
    }
    int n, ini, caminhos;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &ini);
    fscanf(fp, "%d", &caminhos);

    LISTA* l = lista_criar(false);
    if (l == NULL) return 1;
    for(int i = 1; i <= n; i++){
        CIDADE* c = cidade_criar(i); 
        if (c == NULL) return 1;
        ITEM *item = item_criar(i, c); 
        if (item == NULL) return 1;
        lista_inserir(l, item);
    }
    for(int i = 1; i <= caminhos; i++){
        int a, b;
        int *dist = (int*) malloc(sizeof(int));
        fscanf(fp, "%d %d %d", &a, &b, dist);
        CIDADE* cA = (CIDADE*) item_get_dados(lista_busca(l, a));
        CIDADE* cB = (CIDADE*) item_get_dados(lista_busca(l, b));
        cidade_con(cA, cB, dist);
        cidade_con(cB, cA, dist);
    }

    tsp(l, n, ini);

    lista_apagar(&l);
}
