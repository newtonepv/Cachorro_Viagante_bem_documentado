#!/bin/bash

# Caminho da pasta principal onde estão as 9 subpastas
PASTA_PRINCIPAL="./casos_teste"

# Navegar por cada uma das 9 pastas
for pasta in "$PASTA_PRINCIPAL"/*; do
    # Certifica-se de que estamos lidando com uma pasta
    if [ -d "$pasta" ]; then
        # Para cada arquivo .in dentro da pasta
        for input in "$pasta"/*.in; do
            # Executa o programa com o arquivo .in
            ./caixeiro < "$input"
            # O output será salvo como .out na mesma pasta do arquivo .in
            echo "Rodou com $input"
        done
    fi
done
