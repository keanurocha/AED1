#include <stdio.h>
#include <stdlib.h>

// Função para alocar a matriz 9x9 dinamicamente
int** alocarMatriz() {
    int **mat = (int**)malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) {
        mat[i] = (int*)malloc(9 * sizeof(int));
    }
    return mat;
}

// Função para liberar a memória da matriz
void liberarMatriz(int **mat) {
    for (int i = 0; i < 9; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Verifica se um conjunto de 9 números é válido (sem repetição e entre 1-9)
int validarConjunto(int *numeros) {
    int contagem[10] = {0}; // Índices 1 a 9
    for (int i = 0; i < 9; i++) {
        int val = numeros[i];
        if (val < 1 || val > 9) return 0; // Valor inválido
        if (contagem[val]) return 0;      // Valor repetido
        contagem[val] = 1;
    }
    return 1;
}

int verificarSudoku(int **mat) {
    int vetorTemp[9];
    int i, j, k;

    // 1. Verificar Linhas
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            vetorTemp[j] = mat[i][j];
        }
        if (!validarConjunto(vetorTemp)) return 0;
    }

    // 2. Verificar Colunas
    for (j = 0; j < 9; j++) {
        for (i = 0; i < 9; i++) {
            vetorTemp[i] = mat[i][j];
        }
        if (!validarConjunto(vetorTemp)) return 0;
    }

    // 3. Verificar Regiões 3x3
    // bl = bloco linha (0, 3, 6), bc = bloco coluna (0, 3, 6)
    for (int bl = 0; bl < 9; bl += 3) {
        for (int bc = 0; bc < 9; bc += 3) {
            k = 0;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    vetorTemp[k++] = mat[bl + i][bc + j];
                }
            }
            if (!validarConjunto(vetorTemp)) return 0;
        }
    }

    return 1;
}

int main() {
    int N, i, j, k;
    scanf("%d", &N);

    for (k = 1; k <= N; k++) {
        // Alocação Dinâmica
        int **sudoku = alocarMatriz();

        // Leitura
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                scanf("%d", &sudoku[i][j]);
            }
        }

        printf("Instancia %d\n", k);
        if (verificarSudoku(sudoku)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        printf("\n");

        // Liberação de Memória
        liberarMatriz(sudoku);
    }

    return 0;
}