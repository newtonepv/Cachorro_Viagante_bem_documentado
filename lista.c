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
        (*n)->proximo = NULL;
        free(*n);
        *n = NULL;
    }
    return;
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
            l->fim = l->inicio;
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
                l->fim->proximo = n;
                l->fim = n;
                n->proximo = NULL;
            }

        } else {
            l->fim->proximo = n;
            l->fim = n;
            n->proximo = NULL;
        }
        l->tamanho++;
        return true;
    }
    return false;
}

ITEM* lista_remover(LISTA* l, int chave){
    NO* aux = l->inicio;
    NO* ant = NULL;
    int chave_busca = item_get_chave(aux->i);
    while(aux != NULL && chave != chave_busca){
        ant = aux;
        aux = aux->proximo;
        if(aux != NULL){
            chave_busca = item_get_chave(aux->i);
        }
    }

    if(aux != NULL){
        ITEM* i = aux->i;
        if(ant == NULL){
            l->inicio = aux->proximo;
        } else {
            ant->proximo = aux->proximo;
        }

        apagar_no(&aux);
        l->tamanho--;
        return i;
    }
    return NULL;
}

bool lista_apagar(LISTA **l){
    NO* aux;
    if((*l) != NULL){
        while((*l)->inicio != NULL){
            aux = (*l)->inicio;
            (*l)->inicio = (*l)->inicio->proximo;
            apagar_no(&aux);
        }
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

int lista_tamanho(LISTA* l){
    if(l != NULL){
        return l->tamanho;
    }
    return ERRO;
}

bool lista_vazia(LISTA* l){
    if(l != NULL){
        return l->tamanho == 0 ? true : false;
    }
    return false;
}

bool lista_cheia(LISTA* l){
    if(l != NULL){
        return l->tamanho == MAX_TAM ? true : false;
    }
    return false;
}

void lista_imprimir(LISTA* l){
    if(l != NULL){
        NO* aux = l->inicio;
        double* d;
        while(aux != NULL){
            d = ((double*)item_get_dados(aux->i));
            printf("%lf ", *d);
            aux = aux->proximo;
        }
    }
}

/*int lista_inverter(LISTA** lista){

}

bool lista_comparar(LISTA* l1, LISTA* l2){

}*/