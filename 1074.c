#include <stdio.h>

int main() {
    int N, X;

    scanf("%d", &N);

    while (N--) {
        scanf("%d", &X);

        if (X == 0) {
            printf("NULL\n");
        } else {
            if (X % 2 == 0) printf("EVEN");
            else printf("ODD");

            printf(" ");

            if (X > 0) printf("POSITIVE");
            else printf("NEGATIVE");

            printf("\n");
        }
    }

    return 0;
}