#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, i;
    int menor, posicao;
    
    scanf("%d", &N);
    
    // Alocação dinâmica da lista (vetor)
    int *X = (int*)malloc(N * sizeof(int));
    
    for (i = 0; i < N; i++) {
        scanf("%d", &X[i]);
    }
    
    // Inicializa com o primeiro elemento
    menor = X[0];
    posicao = 0;
    
    // Percorre a lista para encontrar o menor
    for (i = 1; i < N; i++) {
        if (X[i] < menor) {
            menor = X[i];
            posicao = i;
        }
    }
    
    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);
    
    free(X);
    return 0;
}