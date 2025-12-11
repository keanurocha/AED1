#include <stdio.h>
#include <stdlib.h>

#define MAX_N 505
#define INF 99999999

// Matriz de Adjacência para o grafo
int adj[MAX_N][MAX_N];
int dist[MAX_N];
int visitado[MAX_N];

// Função Dijkstra simples (sem Heap, complexidade O(N^2))
// Ideal para N <= 500
int dijkstra(int origem, int destino, int N) {
    // Inicialização
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        visitado[i] = 0;
    }
    dist[origem] = 0;

    for (int i = 1; i <= N; i++) {
        int u = -1;
        int minVal = INF;

        // Encontra o nó não visitado com menor distância
        for (int j = 1; j <= N; j++) {
            if (!visitado[j] && dist[j] < minVal) {
                minVal = dist[j];
                u = j;
            }
        }

        // Se não encontrou caminho ou chegou ao destino (opcional, mas otimiza)
        if (u == -1 || dist[u] == INF) break;
        
        visitado[u] = 1;
        if (u == destino) return dist[destinio];

        // Relaxamento dos vizinhos
        for (int v = 1; v <= N; v++) {
            if (adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    return dist[destino];
}

int main() {
    int N, E;
    int X, Y, H;
    int K, O, D;

    // Loop principal dos casos de teste
    while (scanf("%d %d", &N, &E) && (N != 0 || E != 0)) {
        
        // Limpar matriz com INF
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                adj[i][j] = INF;
            }
            adj[i][i] = 0; // Distância para si mesmo é 0
        }

        // Leitura das arestas
        for (int i = 0; i < E; i++) {
            scanf("%d %d %d", &X, &Y, &H);
            // Se já houver aresta, mantemos a menor (caso haja múltiplas entradas)
            if (adj[X][Y] > H) {
                adj[X][Y] = H;
            }
        }

        // TRUQUE DO PROBLEMA:
        // Verificar reciprocidade para definir "mesmo país" (Custo 0)
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                // Se vai de i->j E de j->i, o custo vira 0 instantaneamente
                if (adj[i][j] != INF && adj[j][i] != INF) {
                    adj[i][j] = 0;
                    adj[j][i] = 0;
                }
            }
        }

        // Leitura das consultas
        scanf("%d", &K);
        while (K--) {
            scanf("%d %d", &O, &D);
            int resposta = dijkstra(O, D, N);

            if (resposta == INF) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", resposta);
            }
        }
        
        // Linha em branco após cada caso de teste
        printf("\n");
    }

    return 0;
}