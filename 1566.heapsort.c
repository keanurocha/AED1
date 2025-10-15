#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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

        heapSort(alturas, N);

        for (int i = 0; i < N; i++) {
            printf("%d%c", alturas[i], (i == N - 1) ? '\n' : ' ');
        }

        free(alturas);
    }

    return 0;
}