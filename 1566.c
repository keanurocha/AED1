#include <stdio.h>

int main() {
    int casos, quantidade, altura;
    int contagem[231]; 
    
    scanf("%d", &casos);

    while (casos--) {
        for (int i = 0; i <= 230; i++) {
            contagem[i] = 0;
        }

        scanf("%d", &quantidade);

        for (int i = 0; i < quantidade; i++) {
            scanf("%d", &altura);
            contagem[altura]++;
        }

        int primeiro = 1;

        for (int i = 20; i <= 230; i++) {
            while (contagem[i] > 0) {
                if (!primeiro) {
                    printf(" ");
                }
                printf("%d", i);
                primeiro = 0;
                contagem[i]--;
            }
        }
        printf("\n");
    }

    return 0;
}
