#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000


typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;


Aresta *grafo[510];


void adicionar_aresta(int origem, int destino, int peso) {
    Aresta *nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = peso;
    nova->prox = grafo[origem];
    grafo[origem] = nova;
}

int dijkstra(int inicio, int fim, int n) {
    int dist[510], visitado[510];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visitado[i] = 0;
    }

    dist[inicio] = 0;

    for (int i = 1; i <= n; i++) {
        int menor = -1;

      
        for (int j = 1; j <= n; j++) {
            if (!visitado[j] && (menor == -1 || dist[j] < dist[menor])) {
                menor = j;
            }
        }

        if (menor == -1) break;
        visitado[menor] = 1;


        Aresta *aux = grafo[menor];
        while (aux != NULL) {
            if (dist[menor] + aux->peso < dist[aux->destino]) {
                dist[aux->destino] = dist[menor] + aux->peso;
            }
            aux = aux->prox;
        }
    }

    return dist[fim];
}


int main() {
    int n, m;

    while (1) {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;


        for (int i = 1; i <= n; i++) grafo[i] = NULL;


        int reverso[510][510] = {0};

      
        for (int i = 0; i < m; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

          
            if (reverso[v][u]) {
                adicionar_aresta(u, v, 0);
                adicionar_aresta(v, u, 0);
            } else {
                adicionar_aresta(u, v, p);
                reverso[u][v] = 1;
            }
        }

        int consultas;
        scanf("%d", &consultas);

        for (int i = 0; i < consultas; i++) {
            int origem, destino;
            scanf("%d %d", &origem, &destino);

            int resposta = dijkstra(origem, destino, n);

            if (resposta >= INF)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", resposta);
        }

        printf("\n");
    }

    return 0;
}
