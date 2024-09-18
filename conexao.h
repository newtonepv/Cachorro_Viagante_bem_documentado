#ifndef CONEXAO_H
    #define CONEXAO_H
    #include <stdio.h>
    #include "no.h"
    typedef struct _conexao CONEXAO;
    CONEXAO* conexao_criar(int dist, NO*no1, NO* no2);
    int conexao_get_dist(CONEXAO* conexao);
    NO* conexao_get_no1(CONEXAO* conexao);
    NO* conexao_get_no2(CONEXAO* conexao);
    

#endif