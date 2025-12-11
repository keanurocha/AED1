#include <stdio.h>
#include <string.h>

int main() {
    int N, i, j, len;
    char str[1005];
    char temp;

    scanf("%d", &N);
    getchar(); // Consome a quebra de linha após o numero N

    while (N--) {
        // Leitura da linha (incluindo espaços)
        if (fgets(str, 1005, stdin) == NULL) break;

        // Remove o caractere de nova linha que o fgets pode pegar
        len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }

        // Passada 1: Deslocar letras maiúsculas e minúsculas 3 posições
        for (i = 0; i < len; i++) {
            if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
                str[i] = str[i] + 3;
            }
        }

        // Passada 2: Inverter a linha
        for (i = 0, j = len - 1; i < j; i++, j--) {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }

        // Passada 3: Deslocar caracteres da metade em diante 1 posição para a esquerda
        for (i = len / 2; i < len; i++) {
            str[i] = str[i] - 1;
        }

        printf("%s\n", str);
    }

    return 0;
}