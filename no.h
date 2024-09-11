#ifndef NO_H
    #define NO_H
    #include <stdlib.h>
    #include "conexoes.h"
    typedef struct _no NO;
    NO* criar_no(int id);
    void no_set_id(NO* no, int id);
    int no_get_id(NO* no);
    void no_add_conexao(NO* no, int dist);
    CONEXAO** no_get_conexoes(NO* no);

#endif