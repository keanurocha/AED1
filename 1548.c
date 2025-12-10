#include <stdio.h>
#include <stdlib.h>

// Função de comparação para o qsort (ordem decrescente)
int compara(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        int M;
        scanf("%d", &M);

        int notas[1000];
        int notasOrdenadas[1000];

        // Lê as notas e cria uma cópia para ordenar
        for (int i = 0; i < M; i++) {
            scanf("%d", &notas[i]);
            notasOrdenadas[i] = notas[i];
        }

        // Ordena a cópia em ordem decrescente (maior nota primeiro)
        qsort(notasOrdenadas, M, sizeof(int), compara);

        // Compara a fila original com a ordenada
        int naoMudaram = 0;
        for (int i = 0; i < M; i++) {
            // Se a nota na posição i for igual nas duas listas, o aluno não mudou de lugar
            if (notas[i] == notasOrdenadas[i]) {
                naoMudaram++;
            }
        }

        printf("%d\n", naoMudaram);
    }

    return 0;
}