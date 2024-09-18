#ifndef CONEXAO_H
    #define CONEXAO_H
    #include <stdio.h>
    typedef struct _conexao CONEXAO;
    CONEXAO* conexao_criar(int dist, int no1, int no2);
    int conexao_get_dist(CONEXAO* conexao);
    void conexao_apagar(CONEXAO** conexao);
    int conexao_get_no(CONEXAO* conexao, int index);
    void conexao_apagar(CONEXAO** conexao);

#endif