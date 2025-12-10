#include <stdio.h>
#include <stdlib.h>

#define MAX_M 40005 // Máximo de cidades
#define MAX_N 50005 // Máximo de estradas

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX_N];
int parent[MAX_M];

// Função de comparação para o qsort (ordena por peso crescente)
int compare(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

// Função Find do Union-Find (com compressão de caminho)
// Encontra o representante do conjunto ao qual o elemento 'i' pertence
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Função Union do Union-Find
// Une os conjuntos de 'i' e 'j'
void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    int M, N;

    // Loop principal: lê M e N. Para quando ambos forem 0.
    while (scanf("%d %d", &M, &N) && (M != 0 || N != 0)) {
        
        // Leitura das arestas (rotas)
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        }

        // Ordena as arestas pelo peso (distância)
        qsort(edges, N, sizeof(Edge), compare);

        // Inicializa o Union-Find: cada cidade é seu próprio pai inicialmente
        for (int i = 0; i < M; i++) {
            parent[i] = i;
        }

        int total_distance = 0;
        int edges_count = 0;

        // Algoritmo de Kruskal
        for (int i = 0; i < N; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;

            // Verifica se u e v já estão conectados
            if (find(u) != find(v)) {
                unite(u, v);       // Une os conjuntos
                total_distance += w; // Soma a distância
                edges_count++;
            }
            
            // Otimização: Se já selecionamos M-1 arestas, conectamos todas as cidades
            if (edges_count == M - 1) break; 
        }

        printf("%d\n", total_distance);
    }

    return 0;
}