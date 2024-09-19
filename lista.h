#ifndef LISTA_H
    #define LISTA_H
    #include "item.h"
    typedef struct _lista LISTA;
    LISTA* lista_criar();
    void lista_apagar(LISTA** lista);
    void lista_adicionar(LISTA* lista, ITEM* item);
    ITEM* lista_remover(LISTA* lista);
    ITEM* lista_recuperar(int index);

#endif