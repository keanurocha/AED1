#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct Ligacao {
    int alvo;
    int custo;
    struct Ligacao *prox;
} Ligacao;

Ligacao *mapa[10005];

typedef struct {
    int v, d, p;
} Item;

Item heap[500005];
int h_tam = 0;

void inserir(int v, int d, int p) {
    int i = ++h_tam;
    while (i > 1 && d < heap[i / 2].d) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i].v = v;
    heap[i].d = d;
    heap[i].p = p;
}

Item extrair() {
    Item min = heap[1];
    Item ultimo = heap[h_tam--];
    int i = 1, filho;
    while (i * 2 <= h_tam) {
        filho = i * 2;
        if (filho != h_tam && heap[filho + 1].d < heap[filho].d) filho++;
        if (ultimo.d > heap[filho].d) heap[i] = heap[filho];
        else break;
        i = filho;
    }
    heap[i] = ultimo;
    return min;
}

void nova_rota(int u, int v, int p) {
    Ligacao *n = (Ligacao*) malloc(sizeof(Ligacao));
    n->alvo = v;
    n->custo = p;
    n->prox = mapa[u];
    mapa[u] = n;
}

int main() {
    int c, v_total;
    if (scanf("%d %d", &c, &v_total) != 2) return 0;

    for (int i = 1; i <= c; i++) mapa[i] = NULL;

    for (int i = 0; i < v_total; i++) {
        int u, v, p;
        scanf("%d %d %d", &u, &v, &p);
        nova_rota(u, v, p);
        nova_rota(v, u, p);
    }

    int custos[10005][2];
    for (int i = 1; i <= c; i++) custos[i][0] = custos[i][1] = INF;

    custos[1][0] = 0;
    inserir(1, 0, 0);

    while (h_tam > 0) {
        Item atual = extrair();

        if (atual.d > custos[atual.v][atual.p]) continue;

        for (Ligacao *e = mapa[atual.v]; e != NULL; e = e->prox) {
            int prox_v = e->alvo;
            int n_peso = atual.d + e->custo;
            int n_pari = 1 - atual.p;

            if (n_peso < custos[prox_v][n_pari]) {
                custos[prox_v][n_pari] = n_peso;
                inserir(prox_v, n_peso, n_pari);
            }
        }
    }

    if (custos[c][0] == INF) printf("-1\n");
    else printf("%d\n", custos[c][0]);

    return 0;
}
