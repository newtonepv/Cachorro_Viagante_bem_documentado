#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "cidade.h"
#include "lista.h"
#include "item.h"

void troca(LISTA *r, int i, int j) {
    ITEM *itemI = lista_busca(r, i);
    ITEM *itemJ = lista_busca(r, j);
    if(itemI && itemJ) {
        int chaveI = item_get_chave(itemI);
        int chaveJ = item_get_chave(itemJ);
        item_set_chave(itemI, chaveJ);
        item_set_chave(itemJ, chaveI);
    }
}

int distancia_calcular(LISTA *cidades, LISTA *rota, int n) {
    int totalDist = 0;

    for(int i = 0; i < n; i++) {
        ITEM *a = lista_busca(rota, i);
        ITEM *b = lista_busca(rota, (i + 1) % n);
        if (a && b) {
            CIDADE* auxA = (CIDADE*)item_get_dados(a);
            CIDADE* auxB = (CIDADE*)item_get_dados(b);
            if (auxA && auxB) {
                int dist = cidade_dist(auxA, cidade_id(auxB));
                if(dist == -1) {
                    return -1;
                }
                totalDist += dist;
            }
        }
    }
    return totalDist;
}

void permuta(LISTA *cidades, LISTA *rota, int ini, int fim, int *minDist, LISTA *minRota, int n) {
    if (ini == fim) {
        int dist = distancia_calcular(cidades, rota, n);
        if (dist != -1 && dist < *minDist) {
            *minDist = dist;
            lista_apagar(&minRota);
            for (int i = 0; i < n; i++) {
                ITEM *item = lista_busca(rota, i);
                if (item) {
                    ITEM *clone = item_criar(item_get_chave(item), item_get_dados(item));
                    lista_inserir(minRota, clone);
                }
            }
        }
    } else {
        for (int i = ini; i <= fim; i++) {
            troca(rota, ini, i);
            permuta(cidades, rota, ini + 1, fim, minDist, minRota, n);
            troca(rota, ini, i);
        }
    }
}

void tsp(LISTA *cidades, int n, int origem) {
    LISTA *rota = lista_criar(false);
    LISTA *minRota = lista_criar(false);
    int minDist = INT_MAX;

    for (int i = 0; i < n; i++) {
        ITEM *cidade = lista_busca(cidades, i);
        if (cidade) {
            ITEM *item = item_criar(i + 1, item_get_dados(cidade));
            lista_inserir(rota, item);
        }
    }

    permuta(cidades, rota, 1, n - 1, &minDist, minRota, n);

    printf("Rota: ");
    for (int i = 0; i < lista_tamanho(minRota); i++) {
        ITEM *item = lista_busca(minRota, i);
        if (item) {
            CIDADE *cidade = (CIDADE*)item_get_dados(item);
            if (cidade) {
                printf("%d -> ", cidade_id(cidade));
            }
        }
    }
    printf("%d\n", origem);
    printf("Distância: %d\n", minDist);

    lista_apagar(&rota);
    lista_apagar(&minRota);
}

int main(void) { 
    int cidades; 
    LISTA *l = lista_criar(false);
    scanf("%d", &cidades);

    for (int i = 0; i < cidades; i++) {
        CIDADE *cidade = cidade_criar(i + 1);
        ITEM *item = item_criar(i + 1, cidade);
        lista_inserir(l, item);
    }

    int a, b, dist;
    for (int i = 0; i < cidades * (cidades - 1) / 2; i++) {
        scanf("%d %d %d", &a, &b, &dist);
        CIDADE *cA = (CIDADE*)item_get_dados(lista_busca(l, a - 1));
        CIDADE *cB = (CIDADE*)item_get_dados(lista_busca(l, b - 1));
        if (cA && cB) {
            cidade_con(cA, cB, dist);
        }
    }

    tsp(l, cidades, 1);

    for (int i = 0; i < cidades; i++) {
        ITEM *item = lista_busca(l, i);
        CIDADE *cidade = (CIDADE*)item_get_dados(item);
        cidade_apagar(&cidade);
    }
    lista_apagar(&l);
    return 0;
}
