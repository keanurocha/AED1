#include <stdio.h>
#include <stdlib.h>

int **sudoku; 

int verificaLinha(int x){
    int numeros[10] = {0};

    for(int i = 0; i < 9; ++i){
        if(numeros[sudoku[x][i]])   return 0;
        numeros[sudoku[x][i]] += 1;
    }

    return 1;
}

int verificaColuna(int x){
    int numeros[10] = {0};

    for(int i = 0; i < 9; ++i){
        if(numeros[sudoku[i][x]])   return 0;
        numeros[sudoku[i][x]] += 1;
    }

    return 1;
}

int verificaQuadrado(int x){
    int numeros[10] = {0};
    int linha = 3*(x/3), coluna = 3*(x%3);

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(numeros[sudoku[linha + i][coluna + j]])  return 0;
            numeros[sudoku[linha + i][coluna + j]] += 1;
        }
    }

    return 1;
}

int main(){
    int n;
    char* resposta;

    scanf("%d", &n);

    sudoku = (int**) malloc(9 * sizeof(int*));
    for(int i = 0; i < 9; i++){
        sudoku[i] = (int*) malloc(9 * sizeof(int));
    }

    for(int k = 1; k <= n; ++k){
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                scanf("%d", &sudoku[i][j]);
            }
        }

        printf("Instancia %d\n", k);

        resposta = "SIM";
        for(int i = 0; i < 9; ++i){
            if(!verificaLinha(i) || !verificaColuna(i) || !verificaQuadrado(i)){
                resposta = "NAO";
                break;
            }
        }

        printf("%s\n\n", resposta);
    }

    // liberar memória
    for(int i = 0; i < 9; i++){
        free(sudoku[i]);
    }
    free(sudoku);

    return 0;
}
