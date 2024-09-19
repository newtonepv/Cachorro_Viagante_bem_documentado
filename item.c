#include "item.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct _item{
    int chave;
    void* dados;
};

ITEM* item_criar(int chave, void* dados){
    ITEM* item = (ITEM*)malloc(sizeof(ITEM));
    if(item){
    item->dados = dados;
    item->chave = chave;
    return item;
    }
    return NULL;
}
bool item_apagar(ITEM** item){
    if(*item){
        free((*item)->dados);
        (*item)->dados = NULL;
        free(*item);
        *item=NULL;
        return true;
    }
    return false;
}
int item_get_chave(ITEM* item){
    if(item){
        return item->chave;
    }
    return -1;
}
bool item_set_chave(ITEM* item, int chave){
    if(item){
        item->chave = chave;
        return true;
    }
    return false;
}
void* item_get_dados(ITEM* item){
    if(item){
        return item->dados;
    }
    return NULL;
}
bool item_set_dados(ITEM* item, void* dados){
    if(item){
        item->dados = dados;
        return true;
    }
    return false;
}