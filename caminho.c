#include "caminho.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
struct caminho{
    int* cidades;
    int distancia_total;
};

CAMINHO* caminho_criar(int l){
    CAMINHO* caminho = malloc(sizeof(CAMINHO));
    if(caminho){
        caminho->distancia_total=INT_MAX;
        caminho->cidades=malloc(sizeof(int)*(l));
    }
    return caminho;
}

void caminho_set_dist(CAMINHO* caminho, int dist){
    caminho->distancia_total = dist;
}
void caminho_inserir(CAMINHO* caminho, int num, int index){
    caminho->cidades[index]=num;
}
int caminho_get_dist(CAMINHO* caminho){
    return caminho->distancia_total;
}

void copia_addicionando(int*destino, int* origem, int novo, int l){
    for(int i=0; i<l;i++){
        destino[i]=origem[i];
    }
    destino[l]=novo;
}

void caminho_copiar_addicionando_cidade(CAMINHO* destino, CAMINHO* origem, int largura_caminho_original,
                                            int cidade_nova, int dist){
    
    copia_addicionando(destino->cidades, origem->cidades, cidade_nova, largura_caminho_original);
    
    caminho_set_dist(destino,  caminho_get_dist(origem)+dist); 
    
}

int caminho_get_cidade_index(CAMINHO* caminho, int index){
    return caminho->cidades[index];
}
    
void caminho_apagar(CAMINHO** caminho){
    if(*caminho){
        if((*caminho)->cidades){

            free((*caminho)->cidades);
            (*caminho)->cidades=NULL;

        }

        free(*caminho);
        *caminho=NULL;
    }
}

void caminho_imprimir(CAMINHO* caminho,int n){
    printf("distancia %d | ", caminho_get_dist(caminho));
    for(int k=0; k<n;k++){
        printf("%d", (caminho_get_cidade_index(caminho,k)+1));
        if(k!=n-1){
            printf(" -> ");
        }
    }
    printf("\n");
}