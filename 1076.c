#include <stdio.h>
#include <string.h>

#define MAX_NODES 100

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int startNode;
        scanf("%d", &startNode); // Lê o ponto de partida (não afeta o cálculo em árvores)

        int V, A;
        scanf("%d %d", &V, &A);

        // Matriz para rastrear quais arestas já foram contadas
        // (para lidar com a possibilidade de arestas repetidas 4-1 e 1-4)
        int adj[MAX_NODES][MAX_NODES];
        memset(adj, 0, sizeof(adj));

        int uniqueEdges = 0;

        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);

            // Verifica se a aresta já foi processada (grafo não direcionado)
            if (!adj[u][v]) {
                adj[u][v] = 1;
                adj[v][u] = 1; // Marca o inverso também
                uniqueEdges++;
            }
        }

        // Como não há ciclos (é uma árvore), percorrer tudo e voltar
        // requer passar por cada aresta 2 vezes.
        printf("%d\n", uniqueEdges * 2);
    }

    return 0;
}