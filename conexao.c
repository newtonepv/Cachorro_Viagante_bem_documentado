#include "conexao.h"
#include <stdlib.h>
    struct _conexao{
        int* lsNos[2];
        int dist;
    };

    CONEXAO* conexao_criar(int dist,int no1, int no2){
        CONEXAO* conexao = (CONEXAO*)malloc(sizeof(CONEXAO));
        if(conexao){
            conexao->lsNos[0] = no1;
            conexao->lsNos[1] = no2;
            conexao->dist = dist;
            return conexao;
        }
        return NULL;
    }
    void conexao_apagar(CONEXAO** conexao){
        if(*conexao){
            free(*conexao);
            *conexao = NULL;
        }
    }
    int conexao_get_dist(CONEXAO* conexao){
        if(conexao){
            return conexao->dist;
        }
        return NULL;
    }
    int conexao_get_no(CONEXAO* conexao, int index){
        if(conexao){
            return conexao->lsNos[index];
        }
        return NULL;
    }
    void conexao_apagar(CONEXAO** conexao){
        if(*conexao){
            free(*conexao);
            *conexao=NULL;
        }
    }