#include <stdio.h>
#include <stdlib.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;

    for (int caso = 0; caso < t; caso++) {
        int m, c;
        scanf("%d %d", &m, &c);

        int **tabela = (int**) malloc(m * sizeof(int*));
        for (int i = 0; i < m; i++) {
            tabela[i] = (int*) malloc(c * sizeof(int));
            for (int j = 0; j < c; j++) tabela[i][j] = -1;
        }

        for (int k = 0; k < c; k++) {
            int valor;
            scanf("%d", &valor);
            int pos = valor % m;
            for (int j = 0; j < c; j++) {
                if (tabela[pos][j] == -1) {
                    tabela[pos][j] = valor;
                    break;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            printf("%d -> ", i);
            for (int j = 0; j < c; j++) {
                if (tabela[i][j] == -1) break;
                printf("%d -> ", tabela[i][j]);
            }
            printf("\\\n"); 
        }

       
        if (caso != t - 1) printf("\n");

      
        for (int i = 0; i < m; i++) free(tabela[i]);
        free(tabela);
    }

    return 0;
}
