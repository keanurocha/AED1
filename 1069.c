#include <stdio.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        char s[1005];
        scanf("%s", s);

        int c = 0;
        int sum = 0;
        char *p = s;

        while (*p != '\0') {
            if (*p == '<') {
                c++;
            } else if (*p == '>') {
                if (c > 0) {
                    sum++;
                    c--;
                }
            }
            p++;
        }
        printf("%d\n", sum);
    }
    return 0;
}
