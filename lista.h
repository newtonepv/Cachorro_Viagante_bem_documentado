#ifndef LISTA_H
	#define LISTA_H
	#define inicial 0
    #define MAX_TAM 999
	#define ERRO -32000
	#include "item.h"
          
	typedef struct lista_ LISTA;
	typedef struct no_ NO;

	ITEM* lista_get_index(LISTA* l, int index);
	LISTA *lista_criar(bool ordenada);
	bool lista_inserir(LISTA *lista, ITEM *item);
	ITEM *lista_remover(LISTA *lista, int chave);
	bool lista_apagar(LISTA **lista);
	ITEM *lista_busca(LISTA *lista, int chave);
	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);
	NO* lista_inicio(LISTA *l);
	NO* no_proximo(NO* n);
	ITEM* no_item(NO* n);
	LISTA* lista_copiar(LISTA* original);
#endif
