#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_C 10005
#define INF 0x3f3f3f3f

// Estrutura para representar o estado na fila de prioridade
typedef struct {
    int custo;
    int u;
    int paridade; // 0 para par, 1 para ímpar
} State;

// Estrutura para arestas (Lista de Adjacência)
typedef struct Edge {
    int v;
    int peso;
    struct Edge* next;
} Edge;

Edge* adj[MAX_C];
int dist[MAX_C][2]; // dist[cidade][0] = custo par, dist[cidade][1] = custo ímpar

// Min-Heap (Fila de Prioridade)
State heap[MAX_C * 2 * 10]; // Tamanho seguro
int heapSize = 0;

void push(int custo, int u, int paridade) {
    int i = heapSize++;
    heap[i].custo = custo;
    heap[i].u = u;
    heap[i].paridade = paridade;
    
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].custo <= heap[i].custo) break;
        State temp = heap[i];
        heap[i] = heap[p];
        heap[p] = temp;
        i = p;
    }
}

State pop() {
    State ret = heap[0];
    heap[0] = heap[--heapSize];
    int i = 0;
    while (i * 2 + 1 < heapSize) {
        int child = i * 2 + 1;
        if (child + 1 < heapSize && heap[child + 1].custo < heap[child].custo) {
            child++;
        }
        if (heap[i].custo <= heap[child].custo) break;
        State temp = heap[i];
        heap[i] = heap[child];
        heap[child] = temp;
        i = child;
    }
    return ret;
}

void addEdge(int u, int v, int w) {
    Edge* newNode = (Edge*)malloc(sizeof(Edge));
    newNode->v = v;
    newNode->peso = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}

int main() {
    int C, V;
    
    // Leitura até EOF não especificada, mas comum em maratonas.
    // O problema diz "diversas linhas", mas o formato da primeira linha sugere um caso único ou loop.
    // Vamos assumir loop para garantir.
    if (scanf("%d %d", &C, &V) != EOF) {
        
        // Inicialização
        for (int i = 0; i <= C; i++) {
            adj[i] = NULL;
            dist[i][0] = INF;
            dist[i][1] = INF;
        }

        // Leitura das arestas
        for (int i = 0; i < V; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }

        // Dijkstra
        // Começamos na cidade 1, custo 0, 0 passos (par)
        dist[1][0] = 0;
        push(0, 1, 0);

        while (heapSize > 0) {
            State atual = pop();
            int u = atual.u;
            int custo = atual.custo;
            int paridade = atual.paridade;

            if (custo > dist[u][paridade]) continue;

            Edge* edge = adj[u];
            while (edge != NULL) {
                int v = edge->v;
                int peso = edge->peso;
                int novaParidade = 1 - paridade; // Se era par(0) vira ímpar(1), e vice-versa

                if (dist[u][paridade] + peso < dist[v][novaParidade]) {
                    dist[v][novaParidade] = dist[u][paridade] + peso;
                    push(dist[v][novaParidade], v, novaParidade);
                }
                edge = edge->next;
            }
        }

        // Resultado: custo para chegar em C com paridade 0 (par)
        if (dist[C][0] == INF) {
            printf("-1\n");
        } else {
            printf("%d\n", dist[C][0]);
        }
    }

    return 0;
}