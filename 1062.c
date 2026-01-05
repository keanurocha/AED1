#include <stdio.h>

#define MAXN 1005

int main() {
    int n, i;
    while (scanf("%d", &n) == 1 && n != 0) {
        
        while (1) {
            int vetor[MAXN];
            scanf("%d", &vetor[0]);
            
            if (vetor[0] == 0) {
                printf("\n");
                break;
            }

            for (i = 1; i < n; i++) {
                scanf("%d", &vetor[i]);
            }

            int pilha[MAXN];
            int top = 0;       
            int prox_carro_chegando = 1;       
            int i_vetor = 0;          

            while (i_vetor < n) {
                if (prox_carro_chegando <= n && prox_carro_chegando == vetor[i_vetor]) {
                    prox_carro_chegando++;
                    i_vetor++;
                }
                else if (top > 0 && pilha[top - 1] == vetor[i_vetor]) {
                    top--;
                    i_vetor++;
                }
                else if (prox_carro_chegando <= n) {
                    pilha[top++] = prox_carro_chegando;
                    prox_carro_chegando++;
                }
                else {
                    break;
                }
            }

            if (i_vetor == n) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }
    return 0;
}
