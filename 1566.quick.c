#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int NC;
    scanf("%d", &NC);

    while (NC--) {
        int N;
        scanf("%d", &N);

        int *alturas = (int *)malloc(N * sizeof(int));
        if (alturas == NULL) {
            return 1;
        }

        for (int i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }

        quickSort(alturas, 0, N - 1);

        for (int i = 0; i < N; i++) {
            printf("%d%c", alturas[i], (i == N - 1) ? '\n' : ' ');
        }

        free(alturas);
    }

    return 0;
}