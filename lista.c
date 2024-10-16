#include "lista.h"
#include "cidade.h"
#include "item.h"
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

struct no_{
    ITEM* i;
    struct no_* proximo;
};

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

NO* lista_inicio(LISTA *l){
    if (l == NULL) return NULL;
    return l->inicio;
}

NO* no_proximo(NO* n){
    if (n == NULL) return NULL;
    return n->proximo;
}

ITEM* no_item(NO* n){
    if (n == NULL) return NULL;
    return n->i;
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

void lista_pop(LISTA* l){//sem testar
    if(lista_vazia(l)){
        return;
    }else if(l->tamanho==1){
        NO* unico = l->inicio;
        l->fim=NULL; l->inicio==NULL;
        free(unico);
        unico =NULL;
        l->tamanho -= 1;
        return;
    }
    NO* penultimo = l->inicio;
    int i=2;
    while(1+1==2){
        if(i==l->tamanho){
            free(penultimo->proximo);
            penultimo->proximo = NULL;
            l->fim=penultimo;
            l->tamanho -= 1;
            break;
        }else{
            penultimo = penultimo->proximo;
        }
        i++;
    }

}

ITEM* lista_remover(LISTA* l, int chave){// pega o no que tem essa chave e apaga, mas antes ajeita os ponteiros da lista
    if(l != NULL && l->inicio != NULL){
        NO* aux = criar_no(lista_busca(l, chave));
        if(aux != NULL){
            ITEM* i = aux->i;
            if(aux == l->inicio){// se for o começo da lista
                l->inicio = aux->proximo;// caso for o unico da lista (aux->proximo=NULL) nao tem problema, l-> proximo ficaria como NULL mesmo
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
ITEM* lista_get_index(LISTA* l, int index) {
    if (index < 0 || index >= l->tamanho) {
        // Índice fora do intervalo da lista
        return NULL;
    }

    struct no_* atual = l->inicio;
    for (int i = 0; i < index; i++) {
        if (atual == NULL) {
            // Algo deu errado, não deveria ocorrer
            return NULL;
        }
        atual = atual->proximo;
    }

    return atual != NULL ? atual->i : NULL;
}

LISTA* lista_copiar(LISTA* original) {
    if (original == NULL) {
        return NULL;
    }

    // Cria uma nova lista
    LISTA* copia = lista_criar(original->ordenada);
    if (copia == NULL) {
        return NULL;
    }

    // Itera sobre a lista original e copia os itens
    NO* atual = original->inicio;
    while (atual != NULL) {
        ITEM* item_copia = item_criar(item_get_chave(atual->i), item_get_dados(atual->i));

        if (item_copia == NULL) {
            lista_apagar(&copia);
            return NULL;
        }

        // Insere o item copiado na nova lista
        lista_inserir(copia, item_copia);
        
        atual = atual->proximo;
    }

    return copia;
}
