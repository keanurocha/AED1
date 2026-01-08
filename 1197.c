#include <stdio.h>

int main() {
    int velocidade, tempo;

    while (scanf("%d %d", &velocidade, &tempo) != EOF) {
        int deslocamento = velocidade * (2 * tempo);
        printf("%d\n", deslocamento);
    }

    return 0;
}
