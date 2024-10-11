#include "lista.h"
#include "cidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct caminho{
    LISTA* cidades;
    float distancia_total;
};
typedef struct caminho CAMINHO;

void printBinary(int num) {
    // Loop through each bit from the most significant to the least significant
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;  // Shift and mask to get the i-th bit
        printf("%d", bit);
    }
    printf("\n");
}

CAMINHO menor_caminho_hipotetico(CIDADE* c, float dist, CAMINHO c1, CAMINHO c2) {
    if (dist + c1.distancia_total < c2.distancia_total) {
        CAMINHO novo;
        novo.distancia_total = c1.distancia_total + dist;
        
        // Criar uma nova lista e copiar os elementos da lista de c1
        novo.cidades = lista_criar(false);
        for (int i =0; i<lista_tamanho(c1.cidades); i++) {
            ITEM* item = lista_get_index(c1.cidades,i);
            CIDADE* cidade_atual = item_get_dados(item);
            ITEM* novo_item = item_criar(0, cidade_atual);
            lista_inserir(novo.cidades, novo_item);
        }

        // Inserir a nova cidade no caminho
        ITEM* itemC = item_criar(0, c);
        lista_inserir(novo.cidades, itemC);

        return novo;
    }
    return c2;
}


CAMINHO menor_caminho_no_vetor(CAMINHO* caminhos, int l) {
    CAMINHO menor_de_todos;
    menor_de_todos.distancia_total = INT_MAX;
    for (int i = 0; i < l; i++) {
        if (caminhos[i].distancia_total < menor_de_todos.distancia_total) {
            menor_de_todos = caminhos[i];
        }
    }
    return menor_de_todos;
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

    CAMINHO dp[(1<<n)][n];


    for(int i=0;i<(1<<n); i++){
        for(int j=0;j<n;j++){
            dp[i][j].distancia_total=INT_MAX;
            dp[i][j].cidades=lista_criar(false);
        }
    }

    dp[1<<ini][ini].distancia_total=0;
    ITEM* primeiro = item_criar(0,cidades[ini]);
    lista_inserir(dp[1<<ini][ini].cidades,primeiro);

    //a rota que comeca com a cidade de origem tem caminho com apenas a origem e tem distancia 0
    dp[1<<ini][ini].distancia_total = 0;

    for(int mask = 1; mask<(1<<n); mask++){
            
        printBinary(mask);

        for(int col=0; col<n; col++){
            if((mask & (1<<col))){
            //este for roda para cada cidade visitada no caminho mask, mask = 0110 vai rodar na cidade 1 e 2 
                printf("col: %d\n", col);
                fflush(stdout);

                for(int visit=0;visit<n;visit++){

                    if (mask & (1 << visit)) { // Se a cidade v também está no subconjunto

                        dp[mask][col] = menor_caminho_hipotetico(cidades[visit],cidade_dist(cidades[visit],col) ,dp[mask ^ (1 << col)][visit],dp[mask][col]);

                    }
                }
            }
        }
        printf("\n");
        
    }


    // pega o melhor custo que volta no começo  
    float menorCustoFinal = INT_MAX;
    CAMINHO resultadoFinal;
    for (int i = 0; i < n; i++) {
        if (i != ini) { // Ignora a cidade inicial
            float custoComRetorno = dp[(1 << n) - 1][i].distancia_total + cidade_dist(cidades[i], ini); // Adiciona o custo para voltar
            if (custoComRetorno < menorCustoFinal) {
                menorCustoFinal = custoComRetorno;
                // Copia o caminho final
                resultadoFinal = dp[(1 << n) - 1][i];
                ITEM* itemRetorno = item_criar(0, cidades[ini]);
                lista_inserir(resultadoFinal.cidades, itemRetorno); // Adiciona a cidade inicial no final
            }
        }
    }

    printf("Menor distância: %f\n", menorCustoFinal);
    printf("Caminho percorrido: ");
    lista_imprimir(resultadoFinal.cidades);
    printf("\n");

    return 0;
}
