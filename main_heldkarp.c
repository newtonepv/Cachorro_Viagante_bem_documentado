#include "lista.h"
#include "cidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include "caminho.h"


int contar_uns(unsigned int num) {
    int contador = 0;

    while (num > 0) {
        contador += (num & 1);
        num >>= 1;
    }

    return contador;
}

void held_karp(CIDADE** cidades, int n, int ini){
    CAMINHO*** dp = malloc(sizeof(CAMINHO**)*(1<<n)); //sim um ponteiro triplo :)
    

    for(int i=1<<ini;i<(1<<n);i++){
        dp[i] = malloc(sizeof(CAMINHO*)*n);
    }//allocando as linhas

    for(int i=1<<ini;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j] = caminho_criar(contar_uns(i));//aloca tudo e registra como invalido

        }
    }

    CAMINHO* menor_caminho = caminho_criar(n+1);

    //inicializa a celula que representa o caminho com apenas a cidade de inicio, como 0,
    //fazendo com que caminhos que não sejam advindos dessa, continuem sendo invalidos
    caminho_set_dist(dp[1<<ini][ini],0);
    caminho_inserir(dp[1<<ini][ini],ini,0);

    for(int i = (1<<ini);i<(1<<n);i++){
        for(int j = 0; j<n; j++){//percorre a matriz do inicio em frente
            if(caminho_get_dist(dp[i][j])!=INT_MAX){//apenas os validos (que vem da cidade inicio)


                for(int nao_visitada = 0; nao_visitada<n; nao_visitada++){
                    if((i & (1 << nao_visitada)) == 0){
                        //for percorre as que nao foram visitadas, exemplo: se estamos na 0100 ele percorre a 0101 a 0110 e a 1100
                        
                        CAMINHO* continuado = dp[i|(1<<nao_visitada)][nao_visitada];
                        
                        if( caminho_get_dist(continuado) > caminho_get_dist(dp[i][j]) + cidade_dist(cidades[j],nao_visitada)
                        &&  caminho_get_dist(dp[i][j]) + cidade_dist(cidades[j],nao_visitada)<INT_MAX
                             )//ver se o que queremos por eh realmente menor do que ja tem
                        {
                            //funcao contar_uns conta quantos numeros 1 tem no numero em binario, 
                            //contando assim a largura do caminho
                            
                            caminho_copiar_addicionando_cidade(continuado,dp[i][j],contar_uns(i),
                                                nao_visitada,cidade_dist(cidades[j],nao_visitada));

                        }
                    }

                }
                if(i==(1<<n)-1){//fazer no final, quando a linha for só uns
                    
                    if( caminho_get_dist(menor_caminho) > caminho_get_dist(dp[i][j]) + cidade_dist(cidades[j],ini)
                            &&caminho_get_dist(dp[i][j]) + cidade_dist(cidades[j],ini)<INT_MAX
                            )//ver se o que queremos por eh realmente menor do que ja tem
                        {
                        caminho_copiar_addicionando_cidade(menor_caminho, dp[i][j], n, ini, cidade_dist(cidades[j],ini));

                        
                    }
                }
            }
            caminho_apagar(&dp[i][j]);
        }
        free(dp[i]);
        dp[i]=NULL;
    }
    free(dp);
    dp=NULL;

    caminho_imprimir(menor_caminho,n+1);

    caminho_apagar(&menor_caminho);
}
int main(){

    printf("main heldkarp\n");
    int n, ini, caminhos;//precisamos saber o numero de caminhos pra parar o for que usamos pra ler eles
    scanf("%d", &n);
    scanf("%d", &ini);
    ini = ini-1; // nunca vamos receber 0 como cidade de inicio, por isso preciamos ajustar essa entrada
    scanf("%d", &caminhos);

    CIDADE* cidades[n];
    for(int i = 0; i < n; i++){
        CIDADE* c = cidade_criar(i); 
        if (c == NULL) return 1;
        cidades[i]=c;
    }
    for(int i = 1; i <= caminhos; i++){
        int a, b;
        int *dist = (int*) malloc(sizeof(int));
        int *dist2 = (int*) malloc(sizeof(int));
        scanf("%d %d %d", &a, &b, dist);       
        *dist2 = *dist;
        cidade_con(cidades[a-1], cidades[b-1], dist);
        cidade_con(cidades[b-1], cidades[a-1], dist2);
    }

    held_karp(cidades, n, ini);
    for(int i =0; i < n; i++){
        cidade_apagar(&cidades[i]);
    }



    return 0;
}
