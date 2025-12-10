#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005

// Matriz de adjacência (usando char para economizar memória)
// adj[i][j] = 1 se 'i' depende de 'j'
char adj[MAX_N][MAX_N];
int vis[MAX_N]; // 0: Branco, 1: Cinza, 2: Preto
int N, M;

// Retorna 1 se encontrou ciclo, 0 caso contrário
int dfs(int u) {
    vis[u] = 1; // Marca como "Visitando" (Cinza)

    for (int v = 1; v <= N; v++) {
        if (adj[u][v]) {
            if (vis[v] == 1) {
                return 1; // Ciclo detectado (encontrou nó cinza)
            }
            if (vis[v] == 0) {
                if (dfs(v)) return 1;
            }
        }
    }

    vis[u] = 2; // Marca como "Finalizado" (Preto)
    return 0;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        scanf("%d %d", &N, &M);

        // Limpeza das estruturas
        // Nota: Limpar uma matriz 10000x10000 é lento. 
        // Em um cenário real de competição, evite matriz para N grande.
        for (int i = 0; i <= N; i++) {
            vis[i] = 0;
            // Otimização: limpar apenas as linhas usadas ou usar memset se N for pequeno
            memset(adj[i], 0, (N + 1) * sizeof(char)); 
        }

        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][v] = 1;
        }

        int ciclo = 0;
        for (int i = 1; i <= N; i++) {
            if (vis[i] == 0) {
                if (dfs(i)) {
                    ciclo = 1;
                    break;
                }
            }
        }

        if (ciclo) printf("SIM\n");
        else printf("NAO\n");
    }

    return 0;
}