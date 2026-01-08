#include <stdio.h>

int main() {
    int total, i;
    int num;

    if (scanf("%d", &total) != 1) return 0;

    for (i = 0; i < total; i++) {
        scanf("%d", &num);

        if (num == 0) {
            printf("NULL\n");
        } else {
            const char *tipo = (num % 2 == 0) ? "EVEN" : "ODD";
            const char *polaridade = (num > 0) ? "POSITIVE" : "NEGATIVE";
            
            printf("%s %s\n", tipo, polaridade);
        }
    }

    return 0;
}
