#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;             
    int repeticoes;         
    int altura_no;         
    struct No *esq, *dir;  
} No;

int altura_no(No *no) {
    return no ? no->altura_no : 0;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

No* novo_no(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->repeticoes = 1;
    no->altura_no = 1;
    no->esq = no->dir = NULL;
    return no;
}

No* rotacao_direita(No* y) {
    No* x = y->esq;
    No* t2 = x->dir;

    x->dir = y;
    y->esq = t2;

    y->altura_no = maior(altura_no(y->esq), altura_no(y->dir)) + 1;
    x->altura_no = maior(altura_no(x->esq), altura_no(x->dir)) + 1;

    return x;
}

No* rotacao_esquerda(No* x) {
    No* y = x->dir;
    No* t2 = y->esq;

    y->esq = x;
    x->dir = t2;

    x->altura_no = maior(altura_no(x->esq), altura_no(x->dir)) + 1;
    y->altura_no = maior(altura_no(y->esq), altura_no(y->dir)) + 1;

    return y;
}

int fator_balanceamento(No* no) {
    return no ? altura_no(no->esq) - altura_no(no->dir) : 0;
}

No* inserir(No* raiz, int chave) {
    if (!raiz) return novo_no(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else {
        raiz->repeticoes++; 
        return raiz;
    }

    raiz->altura_no = 1 + maior(altura_no(raiz->esq), altura_no(raiz->dir));
    int balanceamento = fator_balanceamento(raiz);


    if (balanceamento > 1 && chave < raiz->esq->chave)
        return rotacao_direita(raiz);

  
    if (balanceamento < -1 && chave > raiz->dir->chave)
        return rotacao_esquerda(raiz);

   
    if (balanceamento > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

   
    if (balanceamento < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

void imprimir_em_ordem(No* raiz, int *primeiro) {
    if (!raiz) return;

    imprimir_em_ordem(raiz->esq, primeiro);

    for (int i = 0; i < raiz->repeticoes; i++) {
        if (*primeiro) {
            printf("%d", raiz->chave);
            *primeiro = 0;
        } else {
            printf(" %d", raiz->chave);
        }
    }

    imprimir_em_ordem(raiz->dir, primeiro);
}

void liberar_arvore(No* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main() {
    int num_casos;
    scanf("%d", &num_casos);

    while (num_casos--) {
        int quantidade;
        scanf("%d", &quantidade);

        No* raiz = NULL;

        for (int i = 0; i < quantidade; i++) {
            int altura;
            scanf("%d", &altura);
            raiz = inserir(raiz, altura);
        }

        int primeiro = 1;
        imprimir_em_ordem(raiz, &primeiro);
        printf("\n");

        liberar_arvore(raiz);
    }

    return 0;
}
