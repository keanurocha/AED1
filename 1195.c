#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        No* novo = (No*) malloc(sizeof(No));
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

void pre_ordem(No* raiz) {
    if (raiz == NULL) return;
    printf(" %d", raiz->valor);
    pre_ordem(raiz->esquerda);
    pre_ordem(raiz->direita);
}

void in_ordem(No* raiz) {
    if (raiz == NULL) return;
    in_ordem(raiz->esquerda);
    printf(" %d", raiz->valor);
    in_ordem(raiz->direita);
}

void pos_ordem(No* raiz) {
    if (raiz == NULL) return;
    pos_ordem(raiz->esquerda);
    pos_ordem(raiz->direita);
    printf(" %d", raiz->valor);
}

void liberar(No* raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    free(raiz);
}

int main() {
    int casos, quantidade, valor, i, j;
    scanf("%d", &casos);

    for (i = 1; i <= casos; i++) {
        scanf("%d", &quantidade);
        No* raiz = NULL;

        for (j = 0; j < quantidade; j++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", i);
        printf("Pre.:");
        pre_ordem(raiz);
        printf("\n");

        printf("In..:");
        in_ordem(raiz);
        printf("\n");

        printf("Post:");
        pos_ordem(raiz);
        printf("\n\n");

        liberar(raiz);
    }

    return 0;
}
