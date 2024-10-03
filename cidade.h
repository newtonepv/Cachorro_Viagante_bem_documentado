#ifndef CIDADE_H
    #define CIDADE_H
    #include "lista.h"
    #include "item.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct cidade_ CIDADE;
    
    CIDADE* cidade_criar(int id);
    void cidade_apagar(CIDADE **cidade);
    bool cidade_con(CIDADE* origem, CIDADE* destino, int* dist);
    int cidade_dist(CIDADE* cidade, int destino);
    int cidade_id(CIDADE* cidade);
#endif