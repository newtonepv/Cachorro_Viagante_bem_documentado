#ifndef NO_H
    #define NO_H
    #include <stdlib.h>
    #include "conexao.h"
    typedef struct _no NO;
    NO* criar_no(int id, int num_conexoes);
    void apagar_no(NO** no);
    int no_get_id(NO* no);
    void no_add_conexao(NO* no, int dist);
    CONEXAO** no_get_conexoes(NO* no);

#endif