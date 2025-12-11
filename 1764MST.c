#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 40005
#define MAX_EDGES 50005

typedef struct {
    int u, v;
    int custo;
} Aresta;

Aresta arestas[MAX_EDGES];
int pai[MAX_NODES];

// Função de comparação para o qsort (ordena pelo custo)
int compara(const void *a, const void *b) {
    Aresta *A = (Aresta *)a;
    Aresta *B = (Aresta *)b;
    return A->custo - B->custo;
}

// Função Find do Union-Find (com compressão de caminho)
int find(int i) {
    if (pai[i] == i)
        return i;
    return pai[i] = find(pai[i]);
}

// Função Union do Union-Find
void unir(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);
    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j;
    }
}

int main() {
    int M, N;

    while (scanf("%d %d", &M, &N) && (M != 0 || N != 0)) {
        
        // Leitura das arestas
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].custo);
        }

        // 1. Ordena todas as arestas pelo peso (menor para maior)
        qsort(arestas, N, sizeof(Aresta), compara);

        // 2. Inicializa o Union-Find (cada cidade é pai de si mesma)
        for (int i = 0; i < M; i++) {
            pai[i] = i;
        }

        int custoTotal = 0;
        int arestasEscolhidas = 0;

        // 3. Itera pelas arestas ordenadas (Algoritmo de Kruskal)
        for (int i = 0; i < N; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;

            // Se u e v não estão conectados ainda (não formam ciclo)
            if (find(u) != find(v)) {
                unir(u, v);
                custoTotal += arestas[i].custo;
                arestasEscolhidas++;
            }
            
            // Otimização: Se já conectamos M-1 arestas, a árvore está pronta
            if (arestasEscolhidas == M - 1) break;
        }

        printf("%d\n", custoTotal);
    }

    return 0;
}