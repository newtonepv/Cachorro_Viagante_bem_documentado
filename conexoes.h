#ifndef CONEXAO_H
    #define CONEXAO_H
    #include <stdio.h>
    #include "no.h";
    typedef struct _conexao CONEXAO;
    CONEXAO* conexao_criar(int dist, NO* no);
    int conexao_get_dist(CONEXAO* conexao);
    NO* conexao_get_no(CONEXAO* conexao);
    

#endif