#include <stdio.h>

#define MAX 1025
#define MAX_QUEUE (MAX * MAX)

char grid[MAX][MAX];
int qx[MAX_QUEUE];
int qy[MAX_QUEUE];

int main() {
    int N, M;
    
    // Leitura das dimensões
    scanf("%d %d", &N, &M);

    // Leitura da matriz
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }

    int clicks = 0;
    
    // Direções: Cima, Baixo, Esquerda, Direita
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Percorre toda a matriz
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Se encontrar um pixel branco, inicia uma nova coloração (novo clique)
            if (grid[i][j] == '.') {
                clicks++;

                // BFS para preencher toda a região conectada
                int head = 0;
                int tail = 0;
                
                // Adiciona o ponto inicial na fila e marca como visitado ('o')
                qx[tail] = i;
                qy[tail] = j;
                tail++;
                grid[i][j] = 'o'; 

                while (head < tail) {
                    int cx = qx[head];
                    int cy = qy[head];
                    head++;

                    // Verifica os 4 vizinhos
                    for (int k = 0; k < 4; k++) {
                        int nx = cx + dx[k];
                        int ny = cy + dy[k];

                        // Se o vizinho é válido e é um pixel branco
                        if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == '.') {
                            grid[nx][ny] = 'o'; // Marca como visitado imediatamente
                            qx[tail] = nx;
                            qy[tail] = ny;
                            tail++;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", clicks);

    return 0;
}