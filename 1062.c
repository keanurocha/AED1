#include <stdio.h>

#define MAX 1005

int main() {
    int N;
    
    while (scanf("%d", &N) && N != 0) {
        int target[MAX];
        
        while (1) {
            scanf("%d", &target[0]);
            if (target[0] == 0) {
                printf("\n");
                break;
            }
            
            for (int i = 1; i < N; i++) {
                scanf("%d", &target[i]);
            }
            
            int stack[MAX];
            int top = 0;
            int incoming = 1;
            int possible = 1;
            int targetIndex = 0;
            
            while (targetIndex < N) {
                if (top > 0 && stack[top] == target[targetIndex]) {
                    top--;
                    targetIndex++;
                } else if (incoming <= N) {
                    stack[++top] = incoming++;
                } else {
                    possible = 0;
                    break;
                }
            }
            
            if (possible) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }
    
    return 0;
}