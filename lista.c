#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição das estruturas (especialmente lista e nó, sendo que a definição do tipo nó fica no arquivo .c pois o cliente não precisa se preocupar com o mesmo.)

struct lista_{
    struct no_* inicio;
    struct no_* fim;
    int tamanho;
    bool ordenada;
};

typedef struct no_{
    ITEM* i;
    struct no_* proximo;
} NO;

// Cria os nós utilizados na lista recebendo o item armazenado;

NO* criar_no(ITEM *i){
    NO* n = (NO*) malloc(sizeof(NO));
    if (n != NULL){
        n->i = i;
        n->proximo = NULL;
        return n;
    }
    return NULL;
}

//Apaga os nós

void apagar_no(NO** n){
    if((*n) != NULL){
        item_apagar(&((*n)->i));
        free(*n);
        *n = NULL;
    }
}

LISTA* lista_criar(bool ord){
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));
    if(l != NULL){
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        l->ordenada = ord;
        return l;
    }
    return NULL;
}

bool lista_inserir(LISTA* l, ITEM* i){
    NO* n = criar_no(i);

    if(l != NULL && n != NULL){
        if (l->inicio == NULL){
            l->inicio = n;
            l->fim = n;
            l->fim->proximo = NULL;
        } else if (l->ordenada){
            NO* aux = l->inicio;
            NO* ant = NULL;
            int chave = item_get_chave(n->i);
            int chave_busca = item_get_chave(aux->i);

            while(aux != NULL && chave > chave_busca){
                ant = aux;
                aux = aux->proximo;
                if(aux != NULL){
                    chave_busca = item_get_chave(aux->i);
                }
            }
            if(ant == NULL){
                n->proximo = l->inicio;
                l->inicio = n;
            } else {
                n->proximo = aux;
                ant->proximo = n;
            }
            if(aux == NULL){
                l->fim = n;
                l->fim->proximo = NULL;
            }

        } else {
            l->fim->proximo = n;
            l->fim = n;
            l->fim->proximo = NULL;
        }
        l->tamanho++;
        return true;
    }
    return false;
}

ITEM* lista_remover(LISTA* l, int chave){
    if(l != NULL && l->inicio != NULL){
        NO* aux = criar_no(lista_busca(l, chave));
        if(aux != NULL){
            ITEM* i = aux->i;
            if(aux == l->inicio){
                l->inicio = aux->proximo;
            } else {
                NO* ant = l->inicio;
                while(ant->proximo != aux){
                    ant = ant->proximo;
                }
                ant->proximo = aux->proximo;
            }
            if(aux->proximo == NULL){
                l->fim = aux;
            }
            apagar_no(&aux);
            l->tamanho--;
            return i;
        }
    }
    return NULL;
}

void apagar_recursivo(NO** n){
    if((*n) != NULL){
        apagar_recursivo(&((*n)->proximo));
        apagar_no(n);
    }
}

bool lista_apagar(LISTA **l){
    if((*l) != NULL){
        apagar_recursivo(&((*l)->inicio));
        free(*l);
        (*l) = NULL;
        return true;
    }
    return false;
}

ITEM* lista_busca(LISTA* l, int chave){
    NO* n = l->inicio;
    while(n != NULL){
        if(item_get_chave(n->i) == chave){
            return n->i;
        }
        n = n->proximo;
    }
    return NULL;
}

int lista_tamanho(LISTA* l) {
    return (l != NULL) ? l->tamanho : ERRO;
}

bool lista_vazia(LISTA* l) {
    return (l != NULL) && (l->tamanho == 0);
}

bool lista_cheia(LISTA* l) {
    return (l != NULL) && (l->tamanho == MAX_TAM);
}


void lista_imprimir(LISTA* l){
    if(l != NULL){
        NO* aux = l->inicio;
        int* d;
        while(aux != NULL){
            d = ((int*)item_get_dados(aux->i));
            printf("%d ", *d);
            aux = aux->proximo;
        }
    }
}

/*void lista_inverter(LISTA* l) {
    if (l == NULL || l->inicio == NULL) return;

    NO* anterior = NULL;
    NO* atual = l->inicio;
    NO* proximo = NULL;

    l->fim = l->inicio;

    while (atual != NULL) {
        proximo = atual->proximo;
        atual->proximo = anterior
        anterior = atual;
        atual = proximo;
    }
    l->inicio = anterior;
}

bool lista_comparar(LISTA* l1, LISTA* l2) {
    if (l1 == NULL && l2 == NULL) return true;
    if (l1 == NULL || l2 == NULL) return false;

    if (l1->tamanho != l2->tamanho) return false;

    NO* n1 = l1->inicio;
    NO* n2 = l2->inicio;

    while (n1 != NULL && n2 != NULL) {
        if (item_get_chave(n1->i) != item_get_chave(n2->i)) {
            return false;
        }
        n1 = n1->proximo;
        n2 = n2->proximo;
    }
    return true;
} */