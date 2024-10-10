#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

#define MAX 100

struct pilha_{
    int dados[MAX];
    int topo;
};

PILHA* pilha_criar(void){
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));
    if (p == NULL) return NULL;
    p->topo=-1;
    return p;
}

bool pilha_vazia(PILHA* p){
    if (p->topo == -1) return true;
    return false;
}

bool pilha_cheia(PILHA* p){
    if(p->topo == MAX - 1) return true;
    return false;
}

void pilha_empilhar(PILHA* p, int x){
    if (p == NULL || pilha_cheia(p)) return;
    p->dados[++p->topo] = x;
}

int pilha_desempilhar(PILHA* p){
    if (p == NULL || pilha_vazia(p)) return -1;
    return p->dados[(p->topo)--];
}

void pilha_apagar(PILHA** p){
    if(p == NULL) return;
    free(*p);
    *p = NULL;
}