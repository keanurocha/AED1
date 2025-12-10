#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10005

// Estrutura para o nó da lista encadeada
typedef struct Node {
    int destino;
    struct Node* prox;
} Node;

// Vetor de ponteiros para as listas de adjacência
Node* adj[MAX_N];
int vis[MAX_N]; // 0: Branco, 1: Cinza, 2: Preto
int N, M;

// Função para adicionar aresta
void addEdge(int u, int v) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->destino = v;
    novo->prox = adj[u];
    adj[u] = novo;
}

// Função para liberar a memória da lista
void freeGraph() {
    for (int i = 0; i <= N; i++) {
        Node* atual = adj[i];
        while (atual != NULL) {
            Node* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        adj[i] = NULL;
    }
}

// Retorna 1 se encontrou ciclo, 0 caso contrário
int dfs(int u) {
    vis[u] = 1; // Marca como "Visitando" (Cinza)

    Node* atual = adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        
        if (vis[v] == 1) {
            return 1; // Ciclo detectado (encontrou nó na pilha de recursão)
        }
        if (vis[v] == 0) {
            if (dfs(v)) return 1;
        }
        
        atual = atual->prox;
    }

    vis[u] = 2; // Marca como "Finalizado" (Preto)
    return 0;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        scanf("%d %d", &N, &M);

        // Inicializa vetor de visitados e garante que a lista está vazia
        // (A lista é limpa no final do loop anterior, mas inicializamos os ponteiros aqui por segurança na 1ª vez)
        // Nota: O freeGraph no final do loop é quem realmente limpa para o próximo caso.
        for(int i = 0; i <= N; i++) {
            vis[i] = 0;
            adj[i] = NULL; 
        }

        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
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

        freeGraph(); // Limpa a memória para o próximo caso de teste
    }

    return 0;
}