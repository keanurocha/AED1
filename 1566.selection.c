#include <stdio.h>

int v[3000005];

void selectionSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min])
                min = j;
        }
        if (min != i) {
            int tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
}

int main(void) {
    int t, n;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        if (scanf("%d", &n) != 1) break;
        
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        selectionSort(v, n);

        for (int i = 0; i < n; i++) {
            printf("%d%s", v[i], (i == n - 1) ? "" : " ");
        }
        printf("\n");
    }

    return 0;
}
