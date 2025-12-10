#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 30

// Matriz de adjacência e vetor de visitados
int adj[MAX_V][MAX_V];
int visited[MAX_V];
int numVertices, numArestas;

// Vetor auxiliar para armazenar e ordenar os nós de um componente
int componenteAtual[MAX_V];
int tamComponente;

// Função de comparação para o qsort
int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

// Busca em Profundidade (DFS)
void dfs(int u) {
    visited[u] = 1;
    componenteAtual[tamComponente++] = u; // Adiciona o nó à lista do componente atual

    for (int v = 0; v < numVertices; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    int N, caso = 1;
    scanf("%d", &N);

    while (N--) {
        scanf("%d %d", &numVertices, &numArestas);

        // Inicializa as estruturas de dados para o caso atual
        memset(adj, 0, sizeof(adj));
        memset(visited, 0, sizeof(visited));

        // Leitura das arestas
        for (int i = 0; i < numArestas; i++) {
            char u, v;
            scanf(" %c %c", &u, &v); // Espaço antes de %c para ignorar quebras de linha
            adj[u - 'a'][v - 'a'] = 1;
            adj[v - 'a'][u - 'a'] = 1;
        }

        printf("Case #%d:\n", caso++);

        int qtdComponentes = 0;

        // Itera sobre todos os vértices possíveis ('a' até o limite V)
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                qtdComponentes++;
                tamComponente = 0;
                
                // Inicia a busca para encontrar todos os nós deste componente
                dfs(i);
                
                // Ordena os nós do componente para garantir ordem crescente (a,b,c...)
                qsort(componenteAtual, tamComponente, sizeof(int), compare);

                // Imprime o componente
                for (int j = 0; j < tamComponente; j++) {
                    printf("%c,", componenteAtual[j] + 'a');
                }
                printf("\n");
            }
        }

        printf("%d connected components\n\n", qtdComponentes);
    }

    return 0;
}