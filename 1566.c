#include <stdio.h>
#include <string.h> 

int contagemAlturas[231];

int main() {
    int NC; 
    scanf("%d", &NC);

    while (NC--) {
        int N; 
        scanf("%d", &N);

        memset(contagemAlturas, 0, sizeof(contagemAlturas));

        for (int i = 0; i < N; i++) {
            int altura;
            scanf("%d", &altura);
            contagemAlturas[altura]++;
        }

        int primeiro = 1;

        for (int h = 20; h <= 230; h++) {
            
            for (int j = 0; j < contagemAlturas[h]; j++) {
                if (primeiro) {
                    printf("%d", h);
                    primeiro = 0; 
                } else {
                    printf(" %d", h); 
                }
            }
        }

        printf("\n"); 
    }

    return 0;
}