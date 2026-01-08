#include <stdio.h>

#define DIM 1030
#define FILA_TAM (DIM * DIM)

char mapa[DIM][DIM];
int posX[FILA_TAM];
int posY[FILA_TAM];

int main() {
    int h, w;
    if (scanf("%d %d", &h, &w) != 2) return 0;

    for (int i = 0; i < h; i++) {
        scanf("%s", mapa[i]);
    }

    int cliques = 0;
    int movX[] = {1, -1, 0, 0};
    int movY[] = {0, 0, 1, -1};

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (mapa[i][j] == '.') {
                cliques++;

                int inicio = 0;
                int fim = 0;

                posX[fim] = i;
                posY[fim] = j;
                fim++;
                mapa[i][j] = '*';

                while (inicio < fim) {
                    int atualX = posX[inicio];
                    int atualY = posY[inicio];
                    inicio++;

                    for (int k = 0; k < 4; k++) {
                        int nx = atualX + movX[k];
                        int ny = atualY + movY[k];

                        if (nx >= 0 && nx < h && ny >= 0 && ny < w && mapa[nx][ny] == '.') {
                            mapa[nx][ny] = '*';
                            posX[fim] = nx;
                            posY[fim] = ny;
                            fim++;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", cliques);

    return 0;
}
