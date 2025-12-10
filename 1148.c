#include <stdio.h>

#define MAX_N 505
#define INF 0x3f3f3f3f // Um valor grande para representar infinito

int adj[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

// Algoritmo de Dijkstra para encontrar o menor tempo entre origem e destino
int dijkstra(int origem, int destino, int n) {
    // Inicialização
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[origem] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int min_dist = INF;

        // Escolhe o vértice não visitado com a menor distância
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        // Se não conseguiu alcançar nenhum outro vértice ou chegou no destino
        if (u == -1 || dist[u] == INF) break;
        
        visited[u] = 1;
        if (u == destino) return dist[destino];

        // Relaxamento das arestas vizinhas
        for (int v = 1; v <= n; v++) {
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

    // Loop principal dos casos de teste. Para quando N e E forem 0.
    while (scanf("%d %d", &N, &E) && (N != 0 || E != 0)) {
        
        // Inicializa a matriz de adjacência com INF
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                adj[i][j] = INF;
            }
            adj[i][i] = 0; // Distância para si mesmo é 0
        }

        // Leitura dos acordos de envio (arestas)
        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            // Se houver múltiplas arestas, ficamos com a de menor custo (embora o problema não especifique)
            if (adj[x][y] > h) {
                adj[x][y] = h;
            }
        }

        // Regra do "Mesmo País": Se vai e volta, o custo é 0
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i != j && adj[i][j] != INF && adj[j][i] != INF) {
                    adj[i][j] = 0;
                    adj[j][i] = 0;
                }
            }
        }

        int K;
        scanf("%d", &K);

        // Processamento das consultas
        while (K--) {
            int O, D;
            scanf("%d %d", &O, &D);

            int resultado = dijkstra(O, D, N);

            if (resultado == INF) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", resultado);
            }
        }
        
        // Linha em branco após cada caso de teste
        printf("\n");
    }

    return 0;
}