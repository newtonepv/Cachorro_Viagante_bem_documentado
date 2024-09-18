#include "conexao.h"
#include "no.h"
#include <stdlib.h>
    struct _conexao{
        NO* no1;
        NO* no2;
        int dist;
    };

    CONEXAO* conexao_criar(int dist,NO*no1, NO* no2){
        CONEXAO* conexao = (CONEXAO*)malloc(sizeof(CONEXAO));
        if(conexao){
            conexao->no1 = no1;
            conexao->no2 = no2;
            conexao->dist = dist;
            return conexao;
        }
        return NULL;
    }
    int conexao_get_dist(CONEXAO* conexao){
        if(conexao){
            return conexao->dist;
        }
        return NULL;
    }
    NO* conexao_get_no1(CONEXAO* conexao){
        if(conexao){
            return conexao->no1;
        }
        return NULL;
    }
    NO* conexao_get_no2(CONEXAO* conexao){
        if(conexao){
            return conexao->no2;
        }
        return NULL;
    }
    void conexao_apagar(CONEXAO** conexao){
        if(*conexao){
            free(*conexao);
            *conexao=NULL;
        }
    }