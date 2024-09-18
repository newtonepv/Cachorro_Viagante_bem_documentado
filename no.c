#include "no.h"

#include <stdlib.h>
#include "conexao.h"

    struct _no{
        int num_max_conexoes;
        int num_conexoes;
        int id;
        CONEXAO** conexoes;
    };

    NO* criar_no(int id, int num_max_conexoes){
        NO* no = (NO*)malloc(sizeof(NO));
        CONEXAO** conexoes = (CONEXAO**)malloc(sizeof(CONEXAO*)*num_max_conexoes);
        if(no&&conexoes){
            no->conexoes=conexoes;
            no->num_max_conexoes=num_max_conexoes;
            no->num_conexoes=0;
            no->id=id;
            return no;
        }
        return NULL;
    }
    void apagar_no(NO** no){
        if(*no){
            while((*no)->num_conexoes!=0){
            (*no)->conexoes
            }
        }
    }
    int no_get_id(NO* no){
        if(no){
            return no->id;
        }
        return NULL;
    }
    void no_add_conexao(NO* no, int dist){
        if(no){
            no->conexoes
        }
    }
    CONEXAO** no_get_conexoes(NO* no);
