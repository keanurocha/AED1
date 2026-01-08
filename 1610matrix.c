#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10005

char grade[MAX_SIZE][MAX_SIZE];
int status[MAX_SIZE];
int v_num, a_num;

int verificar_circuito(int ponto) {
    status[ponto] = 1;

    for (int vizinho = 1; vizinho <= v_num; vizinho++) {
        if (grade[ponto][vizinho]) {
            if (status[vizinho] == 1) {
                return 1;
            }
            if (status[vizinho] == 0) {
                if (verificar_circuito(vizinho)) return 1;
            }
        }
    }

    status[ponto] = 2;
    return 0;
}

int main() {
    int testes;
    if (scanf("%d", &testes) != 1) return 0;

    for (int t = 0; t < testes; t++) {
        if (scanf("%d %d", &v_num, &a_num) != 2) break;

        for (int i = 0; i <= v_num; i++) {
            status[i] = 0;
            memset(grade[i], 0, (v_num + 1) * sizeof(char));
        }

        for (int i = 0; i < a_num; i++) {
            int de, para;
            scanf("%d %d", &de, &para);
            grade[de][para] = 1;
        }

        int achou_loop = 0;
        for (int i = 1; i <= v_num; i++) {
            if (status[i] == 0) {
                if (verificar_circuito(i)) {
                    achou_loop = 1;
                    break;
                }
            }
        }

        if (achou_loop) printf("SIM\n");
        else printf("NAO\n");
    }

    return 0;
}
