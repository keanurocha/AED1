#include <stdio.h>
#include <limits.h>

#define MAX_N 255
#define INF 0x3f3f3f3f // Um valor suficientemente grande para infinito

int adj[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];
int route_cost[MAX_N]; // Custo para ir da cidade i (dentro da rota) até C-1

int main() {
    int N, M, C, K;

    // Leitura dos casos de teste. Para quando N, M, C, K forem todos 0.
    while (scanf("%d %d %d %d", &N, &M, &C, &K) && (N || M || C || K)) {
        
        // Inicializa a matriz de adjacência com INF
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                adj[i][j] = INF;
            }
        }

        // Leitura das estradas
        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);
            adj[u][v] = p;
            adj[v][u] = p;
        }

        // Passo 1: Calcular o custo sufixo da rota de serviço
        // A rota é 0 -> 1 -> ... -> C-1
        // route_cost[i] é o custo de ir de i até C-1 seguindo a rota
        route_cost[C - 1] = 0;
        for (int i = C - 2; i >= 0; i--) {
            // Assume-se que a estrada entre i e i+1 existe conforme o enunciado
            route_cost[i] = adj[i][i + 1] + route_cost[i + 1];
        }

        // Passo 2: Dijkstra modificado
        // Inicializa distâncias e visitados
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            visited[i] = 0;
        }

        dist[K] = 0;
        int min_total_cost = INF;

        // Loop do Dijkstra
        // Nota: Só precisamos processar nós "fora da rota" (>= C) na fila de prioridade (lógica)
        // O loop roda no máximo N vezes (embora só K -> outside importe)
        for (int i = 0; i < N; i++) {
            int u = -1;
            int min_dist = INF;

            // Seleciona o vértice não visitado com menor distância
            // Restrição: O vértice deve estar FORA da rota (índice >= C)
            // pois se entrarmos na rota, o caminho é determinístico e já calculado
            for (int j = C; j < N; j++) {
                if (!visited[j] && dist[j] < min_dist) {
                    min_dist = dist[j];
                    u = j;
                }
            }

            // Se não alcançamos mais nenhum nó fora da rota, paramos
            if (u == -1 || dist[u] == INF) break;

            visited[u] = 1;

            // Verifica os vizinhos
            for (int v = 0; v < N; v++) {
                if (adj[u][v] != INF) {
                    if (v >= C) {
                        // Vizinho fora da rota: Relaxamento normal do Dijkstra
                        if (dist[u] + adj[u][v] < dist[v]) {
                            dist[v] = dist[u] + adj[u][v];
                        }
                    } else {
                        // Vizinho DENTRO da rota: Calculamos o custo final potencial
                        // Custo = Distância até aqui + aresta de entrada + restante da rota
                        int current_path_cost = dist[u] + adj[u][v] + route_cost[v];
                        if (current_path_cost < min_total_cost) {
                            min_total_cost = current_path_cost;
                        }
                    }
                }
            }
        }

        // Imprime o resultado
        printf("%d\n", min_total_cost);
    }

    return 0;
}