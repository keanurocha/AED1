#include <stdio.h>
#include <string.h>

#define MAX_ALTURA 231

static int frequenciaAlturas[MAX_ALTURA];

int main() {
    int NC;
    scanf("%d", &NC);

    while (NC--) {
        int N;
        scanf("%d", &N);

        memset(frequenciaAlturas, 0, sizeof(frequenciaAlturas));

        for (int i = 0; i < N; i++) {
            int h;
            scanf("%d", &h);
            frequenciaAlturas[h]++;
        }

        int primeiro = 1;
        for (int h = 20; h < MAX_ALTURA; h++) {
            if (frequenciaAlturas[h] > 0) {
                for (int i = 0; i < frequenciaAlturas[h]; i++) {
                    if (primeiro) {
                        printf("%d", h);
                        primeiro = 0;
                    } else {
                        printf(" %d", h);
                    }
                }
            }
        }
        printf("\n");
    }

    return 0;
}