#include <stdio.h>

int main() {
    int h, v;

    while (scanf("%d %d", &h, &v) == 2 && h != 0 && v != 0) {
        if (h > 0) {
            if (v > 0) {
                printf("primeiro\n");
            } else {
                printf("quarto\n");
            }
        } else {
            if (v > 0) {
                printf("segundo\n");
            } else {
                printf("terceiro\n");
            }
        }
    }

    return 0;
}
