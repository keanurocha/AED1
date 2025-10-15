#include <stdio.h>
#include <string.h>

// O array para contar a frequência de cada altura.
// O tamanho é 231 para cobrir os índices de 0 a 230.
// 'static' garante que ele seja inicializado com zeros.
static int frequenciaAlturas[231];

int main() {
    int NC; // Número de Casos de Teste
    scanf("%d", &NC);

    // Loop para cada cidade (caso de teste)
    while (NC--) {
        int N; // Número de pessoas na cidade
        scanf("%d", &N);

        // Zera o array de frequência para o novo caso de teste.
        // Essencial para não misturar dados de cidades diferentes.
        memset(frequenciaAlturas, 0, sizeof(frequenciaAlturas));

        // Fase de contagem: lê cada altura e incrementa seu contador.
        for (int i = 0; i < N; i++) {
            int h;
            scanf("%d", &h);
            frequenciaAlturas[h]++;
        }

        // Fase de impressão (ou "seleção" ordenada)
        int primeiroElemento = 1; // Flag para controlar o espaço em branco
        
        // Itera por todas as alturas possíveis, do menor (20) ao maior (230)
        for (int h = 20; h <= 230; h++) {
            // "Seleciona" a altura 'h' e a imprime o número de vezes que ela apareceu
            for (int i = 0; i < frequenciaAlturas[h]; i++) {
                if (primeiroElemento) {
                    printf("%d", h);
                    primeiroElemento = 0; // Desativa a flag após o primeiro número
                } else {
                    printf(" %d", h);
                }
            }
        }
        printf("\n"); // Pula uma linha ao final de cada caso de teste
    }

    return 0;
}