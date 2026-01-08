#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1e9

typedef struct No {
    int id;
    int custo;
    struct No *seguinte;
} No;

No *lista[255];

void inserir_ligacao(int de, int para, int peso) {
    No *novo = (No*) malloc(sizeof(No));
    novo->id = para;
    novo->custo = peso;
    novo->seguinte = lista[de];
    lista[de] = novo;
}

int calcular_rota(int origem, int destino, int total_n) {
    int distancias[255];
    int processado[255];

    for (int i = 0; i < total_n; i++) {
        distancias[i] = INFINITO;
        processado[i] = 0;
    }

    distancias[origem] = 0;

    for (int i = 0; i < total_n; i++) {
        int u = -1;
        for (int j = 0; j < total_n; j++) {
            if (!processado[j] && (u == -1 || distancias[j] < distancias[u])) {
                u = j;
            }
        }

        if (distancias[u] == INFINITO) break;
        processado[u] = 1;

        for (No *e = lista[u]; e != NULL; e = e->seguinte) {
            int v = e->id;
            int p = e->custo;

            if (distancias[u] + p < distancias[v]) {
                distancias[v] = distancias[u] + p;
            }
        }
    }
    return distancias[destino];
}

int main() {
    int n, m, c, k;

    while (scanf("%d %d %d %d", &n, &m, &c, &k) == 4 && (n || m || c || k)) {
        for (int i = 0; i < n; i++) {
            lista[i] = NULL;
        }

        for (int i = 0; i < m; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            if (u < c && v < c) {
                if (abs(u - v) == 1) {
                    if (u < v) inserir_ligacao(u, v, p);
                    else inserir_ligacao(v, u, p);
                }
            } else if (u < c && v >= c) {
                inserir_ligacao(v, u, p);
            } else if (u >= c && v < c) {
                inserir_ligacao(u, v, p);
            } else {
                inserir_ligacao(u, v, p);
                inserir_ligacao(v, u, p);
            }
        }

        printf("%d\n", calcular_rota(k, c - 1, n));

        for (int i = 0; i < n; i++) {
            No *aux = lista[i];
            while (aux) {
                No *temp = aux;
                aux = aux->seguinte;
                free(temp);
            }
        }
    }

    return 0;
}
