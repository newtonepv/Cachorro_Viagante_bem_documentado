#include <stdio.h>
#include <stdlib.h>

typedef struct pilha_ PILHA;

PILHA* pilha_criar(void);
bool pilha_vazia(PILHA* p);
bool pilha_cheia(PILHA* p);
void pilha_empilhar(PILHA* p, int x);
int pilha_desempilhar(PILHA* p);
void pilha_apagar(PILHA **p);