#include <stdio.h>

// Define um tamanho máximo para o array, seguro para n <= 50
// Precisamos de espaço extra porque movemos cartas do início para o fim
#define MAX_SIZE 101 

int main() {
    int n;
    int pilha[MAX_SIZE];
    int descartadas[50]; // No máximo n-1 cartas são descartadas
    int inicio, fim;
    int i, count_descartadas;

    // Loop principal para ler os casos de teste
    while (scanf("%d", &n) == 1 && n != 0) {
        
        // --- Inicialização para o caso de teste atual ---
        
        // Preenche a pilha com cartas de 1 a n
        for (i = 0; i < n; i++) {
            pilha[i] = i + 1;
        }

        inicio = 0;             // O topo da pilha está no índice 0
        fim = n;                // O próximo espaço livre está no índice n
        count_descartadas = 0;  // Nenhuma carta descartada ainda

        // --- Simulação ---

        // O laço continua enquanto houver 2 ou mais cartas na pilha
        // (a quantidade de cartas é fim - inicio)
        while ((fim - inicio) >= 2) {
            // 1. Joga fora a carta do topo (pilha[inicio])
            descartadas[count_descartadas] = pilha[inicio];
            count_descartadas++;
            inicio++; // Move o ponteiro do início para a próxima carta

            // 2. Move a nova carta do topo (pilha[inicio]) para a base (pilha[fim])
            pilha[fim] = pilha[inicio];
            fim++;    // Aumenta o tamanho da pilha no final
            inicio++; // Remove a carta do início
        }

        // --- Impressão dos resultados ---

        printf("Discarded cards:");
        if (count_descartadas > 0) {
            printf(" %d", descartadas[0]);
            for (i = 1; i < count_descartadas; i++) {
                printf(", %d", descartadas[i]);
            }
        }
        printf("\n");

        // A carta remanescente é a única que sobrou na pilha, na posição 'inicio'
        printf("Remaining card: %d\n", pilha[inicio]);
    }

    return 0;
}