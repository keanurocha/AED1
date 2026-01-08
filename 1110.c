#include <stdio.h>

int main() {
    int n;

    while (scanf("%d", &n) == 1 && n != 0) {
        int deck[2000];
        int descartados[1000];
        int inicio = 0;
        int fim = n;
        int d_idx = 0;

        for (int i = 0; i < n; i++) {
            deck[i] = i + 1;
        }

        while ((fim - inicio) >= 2) {
            descartados[d_idx++] = deck[inicio++];
            deck[fim++] = deck[inicio++];
        }

        printf("Discarded cards:");
        for (int j = 0; j < d_idx; j++) {
            printf(" %d%s", descartados[j], (j == d_idx - 1) ? "" : ",");
        }
        
        printf("\nRemaining card: %d\n", deck[inicio]);
    }

    return 0;
}
