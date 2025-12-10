#include <stdio.h>
#include <string.h>

// Definimos o tamanho máximo para os identificadores (100000)
// e para o número de pessoas na fila (50000)
#define MAX_ID 100001
#define MAX_N 50001

int fila[MAX_N];
int saiu[MAX_ID]; // Array usado como tabela Hash/Lookup para acesso rápido (O(1))

int main() {
    int N, M, id;

    // Leitura da quantidade inicial de pessoas
    scanf("%d", &N);

    // Leitura dos identificadores da fila inicial
    for (int i = 0; i < N; i++) {
        scanf("%d", &fila[i]);
    }

    // Leitura da quantidade de pessoas que saíram
    scanf("%d", &M);

    // Inicializa o array de "saiu" com 0
    memset(saiu, 0, sizeof(saiu));

    // Leitura dos que saíram. Marcamos 1 na posição do ID da pessoa.
    for (int i = 0; i < M; i++) {
        scanf("%d", &id);
        saiu[id] = 1;
    }

    // Percorre a fila inicial e imprime apenas quem não está marcado no array 'saiu'
    int primeiro = 1;
    for (int i = 0; i < N; i++) {
        if (!saiu[fila[i]]) {
            if (!primeiro) {
                printf(" ");
            }
            printf("%d", fila[i]);
            primeiro = 0;
        }
    }
    printf("\n");

    return 0;
}