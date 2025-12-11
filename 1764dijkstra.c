#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 40005 // Máximo de cidades
#define MAX_N 50005 // Máximo de arestas
#define INF INT_MAX

// Estrutura para a Lista de Adjacência
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

Aresta* grafo[MAX_M];

// Estrutura para o Heap (Fila de Prioridade)
typedef struct {
    int u;
    int custo;
} Node;

Node heap[MAX_N * 2];
int heapSize;
int dist[MAX_M];   // Guarda o menor custo para conectar o nó à árvore
int visitado[MAX_M]; // Marca se o nó já foi incluído na MST

// --- Funções de Lista de Adjacência ---
void adicionarAresta(int u, int v, int p) {
    Aresta* nova = (Aresta*)malloc(sizeof(Aresta));
    nova->destino = v;
    nova->peso = p;
    nova->prox = grafo[u];
    grafo[u] = nova;
    
    // Como é bidirecional, adiciona de volta
    Aresta* nova2 = (Aresta*)malloc(sizeof(Aresta));
    nova2->destino = u;
    nova2->peso = p;
    nova2->prox = grafo[v];
    grafo[v] = nova2;
}

void limparGrafo(int M) {
    for (int i = 0; i < M; i++) {
        Aresta* atual = grafo[i];
        while (atual != NULL) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        grafo[i] = NULL;
    }
}

// --- Funções de Heap (Priority Queue) ---
void swap(int i, int j) {
    Node temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void sobe(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (heap[i].custo < heap[pai].custo) {
            swap(i, pai);
            i = pai;
        } else {
            break;
        }
    }
}

void desce(int i) {
    while (2 * i + 1 < heapSize) {
        int filho = 2 * i + 1;
        if (filho + 1 < heapSize && heap[filho + 1].custo < heap[filho].custo) {
            filho++;
        }
        if (heap[filho].custo < heap[i].custo) {
            swap(i, filho);
            i = filho;
        } else {
            break;
        }
    }
}

void push(int u, int custo) {
    heap[heapSize].u = u;
    heap[heapSize].custo = custo;
    sobe(heapSize);
    heapSize++;
}

Node pop() {
    Node topo = heap[0];
    heapSize--;
    heap[0] = heap[heapSize];
    desce(0);
    return topo;
}

// --- Algoritmo de Prim (Lógica idêntica ao Dijkstra) ---
int prim(int M) {
    long long total = 0; // Soma total da MST
    heapSize = 0;
    
    // Inicialização
    for (int i = 0; i < M; i++) {
        dist[i] = INF;
        visitado[i] = 0;
    }

    // Começa pelo nó 0
    dist[0] = 0;
    push(0, 0);

    while (heapSize > 0) {
        Node atual = pop();
        int u = atual.u;
        int custo = atual.custo;

        // Se já visitamos e incluímos na árvore, ignora
        if (visitado[u]) continue;
        
        // Inclui na MST
        visitado[u] = 1;
        total += custo;

        // Verifica vizinhos
        Aresta* vizinho = grafo[u];
        while (vizinho != NULL) {
            int v = vizinho->destino;
            int peso = vizinho->peso;

            // Diferença chave para o Dijkstra:
            // Dijkstra: if (dist[u] + peso < dist[v])
            // Prim:     if (peso < dist[v])
            if (!visitado[v] && peso < dist[v]) {
                dist[v] = peso;
                push(v, dist[v]);
            }
            vizinho = vizinho->prox;
        }
    }
    return (int)total;
}

int main() {
    int M, N;
    int X, Y, Z;

    while (scanf("%d %d", &M, &N) && (M != 0 || N != 0)) {
        // Limpeza inicial
        for(int i = 0; i < M; i++) grafo[i] = NULL;

        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &X, &Y, &Z);
            adicionarAresta(X, Y, Z);
        }

        printf("%d\n", prim(M));

        limparGrafo(M);
    }

    return 0;
}