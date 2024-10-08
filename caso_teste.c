//Código gerado por IA para gerar casos teste válidos para o projeto.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para encontrar o representante de um conjunto (usado na união e busca)
int encontrar(int *pai, int i) {
    if (pai[i] == i) return i;
    return encontrar(pai, pai[i]);
}

// Função para unir dois conjuntos
void unir(int *pai, int *rank, int x, int y) {
    int raizX = encontrar(pai, x);
    int raizY = encontrar(pai, y);
    if (rank[raizX] < rank[raizY]) {
        pai[raizX] = raizY;
    } else if (rank[raizX] > rank[raizY]) {
        pai[raizY] = raizX;
    } else {
        pai[raizY] = raizX;
        rank[raizX]++;
    }
}

void gerar_caso_teste(int num_cidades) {
    // Escolhe uma cidade de origem aleatória
    int cidade_origem = rand() % num_cidades + 1;

    // Inicializa a matriz de distâncias
    int **distancias = (int **)malloc(num_cidades * sizeof(int *));
    for (int i = 0; i < num_cidades; i++) {
        distancias[i] = (int *)malloc(num_cidades * sizeof(int));
        for (int j = 0; j < num_cidades; j++) {
            distancias[i][j] = 0;
        }
    }
    // Ensure full connectivity
    int cidade_atual = 0;
    for (int i = 1; i < num_cidades; i++) {
        int cidade_proxima = (cidade_atual + 1) % num_cidades;
        int distancia = rand() % 491 + 10;
        distancias[cidade_atual][cidade_proxima] = distancia;
        distancias[cidade_proxima][cidade_atual] = distancia;
        cidade_atual = cidade_proxima;
    }

    // Add sufficient edges
    for (int i = 0; i < num_cidades; i++) {
        for (int j = i + 1; j < num_cidades; j++) {
            if (distancias[i][j] == 0 && rand() % 2) {  // 50% de chance de adicionar um caminho
                int distancia = rand() % 491 + 10;
                distancias[i][j] = distancia;
                distancias[j][i] = distancia;
            }
        }
    }
    // Arrays para união e busca
    int *pai = (int *)malloc(num_cidades * sizeof(int));
    int *rank = (int *)malloc(num_cidades * sizeof(int));
    for (int i = 0; i < num_cidades; i++) {
        pai[i] = i;
        rank[i] = 0;
    }
    int num_caminhos = 0;

    // Gera uma árvore mínima que garante a conectividade
    for (int i = 1; i < num_cidades; i++) {
        int cidade1 = i;
        int cidade2 = rand() % i;  // Garante que a cidade2 é anterior, garantindo a conectividade
        int distancia = rand() % 491 + 10;  // Distância aleatória entre 10 e 500
        distancias[cidade1][cidade2] = distancia;
        distancias[cidade2][cidade1] = distancia;
        unir(pai, rank, cidade1, cidade2);
    }

    // Adiciona mais caminhos aleatórios para tornar o grafo mais denso
    for (int i = 0; i < num_cidades; i++) {
        for (int j = i + 1; j < num_cidades; j++) {
            if (distancias[i][j] == 0 && rand() % 2) {  // 50% de chance de adicionar um caminho
                int distancia = rand() % 491 + 10;  // Distância aleatória entre 10 e 500
                distancias[i][j] = distancia;
                distancias[j][i] = distancia;
            }
        }
    }

    // Conta o número de caminhos
    num_caminhos = 0;
    for (int i = 0; i < num_cidades; i++) {
        for (int j = i + 1; j < num_cidades; j++) {
            if (distancias[i][j] != 0) {
                num_caminhos++;
            }
        }
    }

    // Grava o número de cidades, cidade de origem e número de caminhos no arquivo
    printf("%d\n", num_cidades);
    printf("%d\n", cidade_origem);
    printf("%d\n", num_caminhos);

    // Grava os caminhos no arquivo
    for (int i = 0; i < num_cidades; i++) {
        for (int j = i + 1; j < num_cidades; j++) {
            if (distancias[i][j] != 0) {
                printf("%d %d %d\n", i + 1, j + 1, distancias[i][j]);
            }
        }
    }

    // Libera a memória alocada
    for (int i = 0; i < num_cidades; i++) {
        free(distancias[i]);
    }
    free(distancias);
    free(pai);
    free(rank);

    // Fecha o arquivo
}

int main() {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    int num_cidades;
    scanf("%d", &num_cidades);

    gerar_caso_teste(num_cidades);

    return 0;
}
