#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        char mine[1001];
        scanf("%s", mine);
        
        int open_brackets = 0;
        int diamonds = 0;
        int len = strlen(mine);
        
        for (int i = 0; i < len; i++) {
            if (mine[i] == '<') {
                open_brackets++;
            } else if (mine[i] == '>') {
                if (open_brackets > 0) {
                    diamonds++;
                    open_brackets--;
                }
            }
        }
        printf("%d\n", diamonds);
    }
    return 0;
}