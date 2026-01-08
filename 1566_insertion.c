#include <stdio.h>

void insertionSort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

int main(void) {
    int t, n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        int v[n];
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        insertionSort(v, n);

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    }

    return 0;
}
