#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "cidade.h"
#include "lista.h"
#include "item.h"

// Esta é uma função de troca simples - Recebe dois ponteiros para inteiro e utiliza uma variável auxiliar para inverter o conteúdo desses ponteiros (ou seja, x aponta agora para o que y apontava antes e vice-versa)
void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Essa função calcula o percurso total de uma rota. Recebendo o vetor rota, a função percorre esse vetor e busca, na lista de adjacências de cada cidade, a próxima cidade da rota e pega sua distância, somando a uma variável de distância total que é retornada após o vetor percorrer toda a rota. Além disso, caso a cidade não seja encontrada ou não haja adjacência entre as cidades da rota, a função retorna INT_MAX, simbolizando um caminho inválido.
int distancia_calcular(LISTA *cidades, int rota[], int n) {
    int totalDist = 0;
    for (int i = 0; i < n; i++) {
        ITEM* item = lista_busca(cidades, rota[i]);
        if (item == NULL) {
            printf("Cidade com chave %d não encontrada\n", rota[i]);
            return INT_MAX;
        }
        CIDADE* c = (CIDADE*) item_get_dados(item);
        int prox = rota[(i + 1) % n];
        int dist = cidade_dist(c, prox);
        if (dist == INT_MAX) {
            return INT_MAX;
        }

        totalDist += dist;
    }
    return totalDist;
}


// Uma função simples para copiar um vetor. Dados como parâmetros um vetor de origem, um de destino e um inteiro com o tamanho do vetor, a função percorre o vetor origem e copia seus dados na posição do vetor de destino.
void copia_vetor(int origem[], int destino[], int len){
    for(int i = 0; i < len; i++){
        destino[i] = origem[i];
    }
}

// Essa função altera a posição dos elementos de um vetor. Dada a propriedade de que, o menor caminho sempre será o mesmo independente da cidade de origem, o programa é calculado tendo a cidade 1 como origem e destino e apenas "rodando" seus elementos após o cálculo. Enquanto o elemento 0 do vetor não for igual o inteiro origem, percorremos o vetor passando o primeiro elemento para a última posição e passamos todos os elementos uma posição para trás.
void roda_vetor(int vetor[], int len, int origem){
    while(vetor[0] != origem){
        int aux = vetor[0];
        for(int i = 1; i < len; i++){
            vetor[i-1] = vetor[i];
        }
        vetor[len-1] = aux;
    }
}


// Esta função utiliza de um princípio chamado backtracking para permutar os elementos do vetor. Ela troca os elementos, avança recursivamente para a próxima troca, verifica se uma permutação completa foi feita (ini == fim) e, se sim, calcula a distância e verifica se essa distância é menor que a menor distância anteriormente calculada. Após isso, ela volta os elementos para suas posições para explorar outras possibilidades de permutação.
void permutacao(LISTA* cidades, int rota[], int ini, int fim, int minRota[], int *minDist, int n){
    if(ini == fim){
        int curDist = distancia_calcular(cidades, rota, n);
        if(curDist < *minDist){
            *minDist = curDist;
            copia_vetor(rota, minRota, n);
        }
    } else {
        for (int i = ini; i <= fim; i++){
            troca((rota + ini), (rota + i));
            permutacao
        (cidades, rota, ini+1, fim, minRota, minDist, n);
            troca((rota+ini), (rota+i));
        }
    }
}

// A função tsp é o núcleo principal do programa. Ela inicializa o vetor de rota (que será permutado), o vetor minRota (que armazenará a rota mínima) e o valor minDist que será a distância mínima no final (inicializado com INT_MAX para casos onde as distâncias são muito grandes). Após isso, ela preenche o vetor rota com as chaves (ids), das cidades, calcula a permutação e as distâncias chamando permutacao() e roda o vetor (conforme explicado na função roda_vetor). Após isso, ela printa os resultados (cidade de origem, menor rota e distância).
void tsp(LISTA *cidades, int n, int origem) {
    int rota[n];
    int minRota[n];
    int minDist = INT_MAX;

    for (int i = 0; i < n; i++) {
        ITEM *cidade = lista_busca(cidades, i + 1);
        if (cidade) {
            rota[i] = item_get_chave(cidade);
        }
    }
    permutacao(cidades, rota, 1, n - 1, minRota, &minDist, n);
    roda_vetor(minRota, n, origem);
    printf("Cidade Origem: %d\n", origem);
    if(minDist == INT_MAX){
        printf("Caminho Impossível");
        return;
    }
    printf("Rota: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", minRota[i]);
    }
    printf("%d\n", minRota[0]);
    printf("Distância: %d\n", minDist);
}

// A função main é utilizada apenas para inicializar as listas de cidades, variáveis de entrada e limpar elas após isso.
int main(int argc, char *argv[]) { 
    clock_t begin = clock();
    int n, ini, caminhos;
    scanf("%d", &n);
    scanf("%d", &ini);
    scanf("%d", &caminhos);

    LISTA* l = lista_criar(false);
    if (l == NULL) return 1;
    for(int i = 1; i <= n; i++){
        CIDADE* c = cidade_criar(i); 
        if (c == NULL) return 1;
        ITEM *item = item_criar(i, c); 
        if (item == NULL) return 1;
        lista_inserir(l, item);
    }
    for(int i = 1; i <= caminhos; i++){
        int a, b;
        int *dist = (int*) malloc(sizeof(int));
        int *dist2 = (int*) malloc(sizeof(int));
        scanf("%d %d %d", &a, &b, dist);
        *dist2 = *dist;
        CIDADE* cA = (CIDADE*) item_get_dados(lista_busca(l, a));
        CIDADE* cB = (CIDADE*) item_get_dados(lista_busca(l, b));
        cidade_con(cA, cB, dist);
        cidade_con(cB, cA, dist2);
    }

    tsp(l, n, ini);
    NO* no = lista_inicio(l);
    while (no != NULL){
        ITEM* it = no_item(no);
        CIDADE* aux = (CIDADE*) item_get_dados(it);
        cidade_apagar(&aux);
        no = no_proximo(no);
    }
    lista_apagar(&l);
    clock_t end = clock();
    double time = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %lfs", time);
}
