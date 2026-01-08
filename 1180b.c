#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, pos;
    int *v;

    if (scanf("%d", &n) != 1) return 0;

    v = (int*) malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", (v + i));
    }

    int m = *v;
    pos = 0;

    for (i = 1; i < n; i++) {
        if (*(v + i) < m) {
            m = *(v + i);
            pos = i;
        }
    }

    printf("Menor valor: %d\n", m);
    printf("Posicao: %d\n", pos);

    free(v);

    return 0;
}
