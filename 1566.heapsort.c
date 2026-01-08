#include <stdio.h>
#include <stdlib.h>

void heapify(int v[], int n, int i) {
    int maior, esq, dir, tmp;
    
    while (1) {
        maior = i;
        esq = 2 * i + 1;
        dir = 2 * i + 2;

        if (esq < n && v[esq] > v[maior])
            maior = esq;
        if (dir < n && v[dir] > v[maior])
            maior = dir;

        if (maior != i) {
            tmp = v[i];
            v[i] = v[maior];
            v[maior] = tmp;
            i = maior;
        } else {
            break;
        }
    }
}

void heapSort(int v[], int n) {
    int i, tmp;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (i = n - 1; i > 0; i--) {
        tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;
        heapify(v, i, 0);
    }
}

int main(void) {
    int t, n, i;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        if (scanf("%d", &n) != 1) break;

        int *v = (int *)malloc(n * sizeof(int));
        
        for (i = 0; i < n; i++)
            scanf("%d", &v[i]);

        heapSort(v, n);

        for (i = 0; i < n; i++) {
            printf("%d%s", v[i], (i == n - 1) ? "" : " ");
        }
        printf("\n");
        
        free(v);
    }

    return 0;
}
