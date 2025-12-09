#include <stdio.h>
#include <stdbool.h>

// Função para verificar se todas as linhas são válidas
bool validaLinhas(int matriz[9][9]) {
    for (int i = 0; i < 9; i++) {
        bool vistos[10] = {false}; // Índices 1 a 9 para os números 1 a 9
        for (int j = 0; j < 9; j++) {
            int num = matriz[i][j];
            // Verifica se o número está no intervalo correto e se já foi visto
            if (num < 1 || num > 9 || vistos[num]) {
                return false;
            }
            vistos[num] = true;
        }
    }
    return true;
}

// Função para verificar se todas as colunas são válidas
bool validaColunas(int matriz[9][9]) {
    for (int j = 0; j < 9; j++) {
        bool vistos[10] = {false};
        for (int i = 0; i < 9; i++) {
            int num = matriz[i][j];
            if (num < 1 || num > 9 || vistos[num]) {
                return false;
            }
            vistos[num] = true;
        }
    }
    return true;
}

// Função para verificar se todas as regiões 3x3 são válidas
bool validaRegioes(int matriz[9][9]) {
    // Itera sobre as 9 regiões 3x3
    for (int inicioLinha = 0; inicioLinha < 9; inicioLinha += 3) {
        for (int inicioColuna = 0; inicioColuna < 9; inicioColuna += 3) {
            bool vistos[10] = {false};
            // Itera dentro da região 3x3 atual
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = matriz[inicioLinha + i][inicioColuna + j];
                    if (num < 1 || num > 9 || vistos[num]) {
                        return false;
                    }
                    vistos[num] = true;
                }
            }
        }
    }
    return true;
}

// Função principal que verifica a solução do Sudoku
bool validaSudoku(int matriz[9][9]) {
    return validaLinhas(matriz) && validaColunas(matriz) && validaRegioes(matriz);
}

int main() {
    int n, i, j, instancia;
    
    // Lê o número de instâncias
    scanf("%d", &n);

    for (instancia = 1; instancia <= n; instancia++) {
        int sudokuMatriz[9][9];
        
        // Lê a matriz 9x9
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                scanf("%d", &sudokuMatriz[i][j]);
            }
        }

        // Imprime o cabeçalho da instância
        printf("Instancia %d\n", instancia);

        // Valida e imprime o resultado
        if (validaSudoku(sudokuMatriz)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        
        // Imprime a linha em branco após cada instância
        printf("\n");
    }

    return 0;
}
