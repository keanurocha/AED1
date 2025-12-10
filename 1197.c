#include <stdio.h>

int main() {
    int v, t;
    
    // Lê os valores de velocidade (v) e tempo (t) até o final do arquivo (EOF)
    while (scanf("%d %d", &v, &t) != EOF) {
        // A fórmula para o deslocamento no dobro do tempo, assumindo partida do repouso,
        // simplifica para 2 * v * t
        printf("%d\n", 2 * v * t);
    }

    return 0;
}