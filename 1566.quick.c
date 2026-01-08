#include <stdio.h>

int v[3000005];

void quickSort(int v[], int ini, int fim) {
    if (ini < fim) {
        int pivo = v[(ini + fim) / 2];
        int i = ini, j = fim, temp;

        while (i <= j) {
            while (v[i] < pivo) i++;
            while (v[j] > pivo) j--;
            if (i <= j) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                i++;
                j--;
            }
        }

        if (ini < j) quickSort(v, ini, j);
        if (i < fim) quickSort(v, i, fim);
    }
}

int main(void) {
    int t, n;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        if (scanf("%d", &n) != 1) break;
        
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        quickSort(v, 0, n - 1);

        for (int i = 0; i < n; i++) {
            printf("%d%s", v[i], (i == n - 1) ? "" : " ");
        }
        printf("\n");
    }

    return 0;
}
