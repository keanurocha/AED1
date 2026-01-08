#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char chave;
    struct No *esq, *dir;
} No;

No* novo_no(char chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esq = no->dir = NULL;
    return no;
}

No* inserir(No* raiz, char chave) {
    if (!raiz) return novo_no(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);

    return raiz; // sem repetição
}

int pesquisar(No* raiz, char chave) {
    if (!raiz) return 0;
    if (chave == raiz->chave) return 1;
    if (chave < raiz->chave) return pesquisar(raiz->esq, chave);
    return pesquisar(raiz->dir, chave);
}

void imprimir_infixa(No* raiz, int *primeiro) {
    if (!raiz) return;

    imprimir_infixa(raiz->esq, primeiro);

    if (*primeiro) {
        printf("%c", raiz->chave);
        *primeiro = 0;
    } else {
        printf(" %c", raiz->chave);
    }

    imprimir_infixa(raiz->dir, primeiro);
}

void imprimir_prefixa(No* raiz, int *primeiro) {
    if (!raiz) return;

    if (*primeiro) {
        printf("%c", raiz->chave);
        *primeiro = 0;
    } else {
        printf(" %c", raiz->chave);
    }

    imprimir_prefixa(raiz->esq, primeiro);
    imprimir_prefixa(raiz->dir, primeiro);
}

void imprimir_posfixa(No* raiz, int *primeiro) {
    if (!raiz) return;

    imprimir_posfixa(raiz->esq, primeiro);
    imprimir_posfixa(raiz->dir, primeiro);

    if (*primeiro) {
        printf("%c", raiz->chave);
        *primeiro = 0;
    } else {
        printf(" %c", raiz->chave);
    }
}

int main() {
    No* raiz = NULL;
    char comando[20], letra;

    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "I") == 0) {
            scanf(" %c", &letra);
            raiz = inserir(raiz, letra);
        }

        else if (strcmp(comando, "P") == 0) {
            scanf(" %c", &letra);
            if (pesquisar(raiz, letra))
                printf("%c existe\n", letra);
            else
                printf("%c nao existe\n", letra);
        }

        else if (strcmp(comando, "INFIXA") == 0) {
            int primeiro = 1;
            imprimir_infixa(raiz, &primeiro);
            printf("\n");
        }

        else if (strcmp(comando, "PREFIXA") == 0) {
            int primeiro = 1;
            imprimir_prefixa(raiz, &primeiro);
            printf("\n");
        }

        else if (strcmp(comando, "POSFIXA") == 0) {
            int primeiro = 1;
            imprimir_posfixa(raiz, &primeiro);
            printf("\n");
        }
    }

    return 0;
}
