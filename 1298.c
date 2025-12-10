#include <stdio.h>
#include <stdlib.h>

#define MAX_N 305
#define MAX_ROWS (2 * MAX_N)
#define MAX_COLS (2 * MAX_N + 1)
// Definindo um tamanho seguro para o Union-Find
// O número de nós é aprox (2N)*(2N), para N=300 -> 360.000 nós.
#define MAX_NODES (MAX_ROWS + 5) * (MAX_COLS + 5)
#define MAX_EDGES (MAX_NODES * 2)

// Estrutura para representar uma aresta possível (barreira)
typedef struct {
    int u;      // Nó 1
    int v;      // Nó 2
    int weight; // Custo (0 se manter, 1 se girar)
} Edge;

Edge edges[MAX_EDGES];
int parent[MAX_NODES];
int N;
int rows, cols;

// Função para mapear coordenada (r, c) para um ID de nó único
int get_node_id(int r, int c) {
    return r * (cols + 1) + c;
}

// Verifica se o nó está na borda da lagoa
int is_boundary(int r, int c) {
    return (r == 0 || r == rows || c == 0 || c == cols);
}

// Funções do Union-Find
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

// Comparador para o qsort (ordem crescente de peso)
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int main() {
    // Leitura do N. Loop para casos de teste implícitos (embora o problema diga "Diversas linhas", 
    // a estrutura sugere um único N por caso ou EOF. Vamos assumir leitura até EOF).
    while (scanf("%d", &N) != EOF) {
        rows = 2 * N;
        cols = 2 * N + 1;
        
        // Reinicializa o Union-Find
        // Usamos um nó extra (ID máximo) para representar a "Borda/Raiz"
        int root_node = get_node_id(rows + 1, cols + 1); 
        
        // Inicializa parentes. O limite superior seguro é root_node + 1.
        for (int i = 0; i <= root_node; i++) {
            parent[i] = i;
        }

        int edge_count = 0;
        char buffer[MAX_N + 5];

        // Processa as 2N - 1 linhas de entrada
        for (int i = 1; i <= rows - 1; i++) {
            scanf("%s", buffer);
            for (int j = 1; j <= N; j++) {
                // Calcula o centro da barreira (r, c)
                int r = i;
                int c = (i % 2 != 0) ? (2 * j - 1) : (2 * j);
                
                // O caractere atual
                char orientation = buffer[j - 1];

                // --- Criação da Aresta Vertical ---
                // Conecta (r-1, c) e (r+1, c)
                int u_v = get_node_id(r - 1, c);
                int v_v = get_node_id(r + 1, c);
                int cost_v = (orientation == 'V') ? 0 : 1;
                
                // Se algum ponto for borda, conecta ao root_node
                if (is_boundary(r - 1, c)) u_v = root_node;
                if (is_boundary(r + 1, c)) v_v = root_node;

                edges[edge_count].u = u_v;
                edges[edge_count].v = v_v;
                edges[edge_count].weight = cost_v;
                edge_count++;

                // --- Criação da Aresta Horizontal ---
                // Conecta (r, c-1) e (r, c+1)
                int u_h = get_node_id(r, c - 1);
                int v_h = get_node_id(r, c + 1);
                int cost_h = (orientation == 'H') ? 0 : 1;

                if (is_boundary(r, c - 1)) u_h = root_node;
                if (is_boundary(r, c + 1)) v_h = root_node;

                edges[edge_count].u = u_h;
                edges[edge_count].v = v_h;
                edges[edge_count].weight = cost_h;
                edge_count++;
            }
        }

        // Ordena as arestas pelo custo (Kruskal)
        qsort(edges, edge_count, sizeof(Edge), compare);

        int min_switches = 0;
        
        // Executa Kruskal
        for (int i = 0; i < edge_count; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].weight;

            if (find(u) != find(v)) {
                unite(u, v);
                min_switches += w;
            }
        }

        printf("%d\n", min_switches);
    }

    return 0;
}