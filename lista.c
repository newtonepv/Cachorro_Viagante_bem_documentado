#include "lista.h"
#include <stdlib.h>
    typedef struct _no NO;
    struct _no{
        NO* anterior;
        NO* proximo;
        ITEM* item;
    };
    struct _lista{
        NO* primeiro;
        NO* ultimo;
        int tamanho;
        bool ordenada;

    };

    LISTA* lista_criar(bool ordenada){
        LISTA* lista = malloc(sizeof(LISTA));
        if(lista){
            lista->tamanho=0;
            lista->ultimo=NULL;
            lista->ordenada = ordenada;
            return lista;
        }
        return NULL;
    }
    void lista_apagar(LISTA** lista){
        if(*lista){
            while((*lista)->ultimo!=NULL){
                item_apagar(lista_remover(*lista));

            }
        }
    }
    void lista_adicionar(LISTA* lista, ITEM* item){
        
        if(lista->ordenada){
            return lista_inserir_ordenado(lista, item);
        }
        return lista_inserir_fim(lista,item);
    }
    bool lista_inserir_fim(LISTA* lista, ITEM* item){
        if(!lista_cheia(lista)){
            NO* no = malloc(sizeof(NO));
            no->item = item;
            no->anterior = lista->ultimo->proximo;
            no->proximo = NULL;
            lista->ultimo->proximo = no;
            lista->ultimo = no;
            return true;
        }
        return true;
    }
    ITEM* lista_remover(LISTA* lista, int index);
    ITEM* lista_busca(LISTA* lista, int index);
    int lista_get_num_itens(LISTA* lista);
    bool lista_vazia(LISTA* lista);
    bool lista_cheia(LISTA* lista);