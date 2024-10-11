#include "cidade.h"
#include "lista.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct cidade_{
    int id;
    LISTA* adj;
};

CIDADE* cidade_criar(int id){
    CIDADE* c = (CIDADE*) malloc(sizeof(CIDADE));
    if(c != NULL){
        c->id = id;
        c->adj = lista_criar(false);
        return c;
    }
    return NULL;
}
bool cidade_con(CIDADE* origem, CIDADE* destino, int *dist){
    if(origem != NULL && destino != NULL){
        ITEM *i = item_criar(destino->id, dist);
        lista_inserir(origem->adj, i);
        return true;
    }
    return false;
}
void cidade_apagar(CIDADE **c){
    if((*c) != NULL){
        NO* aux = lista_inicio((*c)->adj);
        while(aux != NULL){
            ITEM* it = no_item(aux);
            item_apagar_dados(it);
            aux = no_proximo(aux);
        }
        lista_apagar(&((*c)->adj));
        free(*c);
        *c = NULL;
    }
}

void cidade_apagar2(CIDADE **c) {
    if ((*c) != NULL) {
        NO* aux = lista_inicio((*c)->adj);
        while (aux != NULL) {
            ITEM* it = no_item(aux);
            item_apagar_dados(it); // Liberar os dados do item
            aux = no_proximo(aux);
        }
        lista_apagar(&((*c)->adj)); // Libera a lista de adjacências
        free(*c);
        *c = NULL;
    }
}


int cidade_dist(CIDADE* cidade, int destino){
    ITEM* con = lista_busca(cidade->adj, destino);
    if (con != NULL){
        int dist = *((int*) item_get_dados(con));
        return dist;
    }
    return INT_MAX;
}

int cidade_id(CIDADE* cidade){
    return cidade->id;
}