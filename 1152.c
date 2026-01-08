#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, peso;
} Aresta;

int pai[200005], tamanho[200005];

int encontrar(int x) {
    if (pai[x] == x) return x;
    return pai[x] = encontrar(pai[x]);
}

void unir(int a, int b) {
    a = encontrar(a);
    b = encontrar(b);
    if (a == b) return;

    if (tamanho[a] < tamanho[b]) {
        pai[a] = b;
        tamanho[b] += tamanho[a];
    } else {
        pai[b] = a;
        tamanho[a] += tamanho[b];
    }
}

int comparar(const void *a, const void *b) {
    Aresta *x = (Aresta*) a;
    Aresta *y = (Aresta*) b;
    return x->peso - y->peso;
}

int main() {
    int n, m;

    while (1) {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;

        Aresta *arestas = (Aresta*) malloc(m * sizeof(Aresta));
        long long soma_total = 0;

        for (int i = 0; i < n; i++) {
            pai[i] = i;
            tamanho[i] = 1;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].peso);
            soma_total += arestas[i].peso;
        }

        qsort(arestas, m, sizeof(Aresta), comparar);

        long long custo_mst = 0;

        for (int i = 0; i < m; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;
            int p = arestas[i].peso;

            if (encontrar(u) != encontrar(v)) {
                unir(u, v);
                custo_mst += p;
            }
        }

        printf("%lld\n", soma_total - custo_mst);

        free(arestas);
    }

    return 0;
}
