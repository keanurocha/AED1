#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 200005
#define MAX_NODES 200005

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX_EDGES];
int parent[MAX_NODES];

// Função de comparação para o qsort
int compare(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

// Função Find do Union-Find (com compressão de caminho)
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Função Union do Union-Find
void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    int m, n;

    // Loop até que m e n sejam 0
    while (scanf("%d %d", &m, &n) && (m != 0 || n != 0)) {
        long long total_cost = 0;

        // Leitura das arestas
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
            total_cost += edges[i].w;
        }

        // Ordena as arestas pelo peso (menor para o maior)
        qsort(edges, n, sizeof(Edge), compare);

        // Inicializa o Union-Find
        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }

        long long mst_cost = 0;
        int edges_count = 0;

        // Algoritmo de Kruskal
        for (int i = 0; i < n; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;

            // Se u e v não estão no mesmo componente, une-os
            if (find(u) != find(v)) {
                unite(u, v);
                mst_cost += w;
                edges_count++;
            }
        }

        // A economia é o custo total original menos o custo da MST
        printf("%lld\n", total_cost - mst_cost);
    }

    return 0;
}