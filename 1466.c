#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* criar_no(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = novo->dir = NULL;
    return novo;
}

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);

    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

typedef struct {
    No *fila[2000];
    int ini, fim;
} Fila;

void iniciar_fila(Fila *q) {
    q->ini = q->fim = 0;
}

void enfileirar(Fila *q, No *x) {
    q->fila[q->fim++] = x;
}

No* desenfileirar(Fila *q) {
    return q->fila[q->ini++];
}

int fila_vazia(Fila *q) {
    return q->ini == q->fim;
}

void percorrer_por_nivel(No *raiz) {
    if (raiz == NULL) return;

    Fila q;
    iniciar_fila(&q);
    enfileirar(&q, raiz);

    int primeiro = 1;

    while (!fila_vazia(&q)) {
        No *atual = desenfileirar(&q);

        if (!primeiro) printf(" ");
        printf("%d", atual->valor);
        primeiro = 0;

        if (atual->esq) enfileirar(&q, atual->esq);
        if (atual->dir) enfileirar(&q, atual->dir);
    }
    printf("\n");
}

void liberar_arvore(No *raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    int t, n, valor;
    scanf("%d", &t);

    for (int caso = 1; caso <= t; caso++) {
        scanf("%d", &n);

        No *raiz = NULL;

        for (int i = 0; i < n; i++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", caso);
        percorrer_por_nivel(raiz);
        printf("\n");

        liberar_arvore(raiz);
    }

    return 0;
}
