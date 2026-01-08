#include <stdio.h>
#include <string.h>

int main() {
    int N, i, j, len;
    char str[1005];
    char temp;

    scanf("%d", &N);
    getchar();

    while (N--) {
        if (fgets(str, 1005, stdin) == NULL) break;
        len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }

        for (i = 0; i < len; i++) {
            if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
                str[i] = str[i] + 3;
            }
        }

        for (i = 0, j = len - 1; i < j; i++, j--) {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }

        for (i = len / 2; i < len; i++) {
            str[i] = str[i] - 1;
        }

        printf("%s\n", str);
    }

    return 0;

}
