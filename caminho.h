
#ifndef CAMINHO_H
    #define CAMINHO_H
    typedef struct caminho CAMINHO;

    CAMINHO* caminho_criar(int l);
    void caminho_set_dist(CAMINHO* caminho, int dist);
    void caminho_inserir(CAMINHO* caminho, int num, int index);
    int caminho_get_dist(CAMINHO* caminho);
    void caminho_copiar_addicionando_cidade(CAMINHO* destino, CAMINHO* origem, int largura_caminho_original,
                                            int cidade_nova, int dist);
    int caminho_get_cidade_index(CAMINHO* caminho, int index);
    void caminho_apagar(CAMINHO** caminho);
    void caminho_imprimir(CAMINHO* caminho,int n);
#endif