#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int altura;
    int quantidade; // Armazena quantas pessoas têm essa altura (frequência)
    struct Node *esq;
    struct Node *dir;
} Node;

// Cria um novo nó
Node* criarNo(int h) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->altura = h;
    novo->quantidade = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Insere na árvore ou incrementa a quantidade se já existir
Node* inserir(Node* raiz, int h) {
    if (raiz == NULL) return criarNo(h);

    if (h == raiz->altura) {
        raiz->quantidade++; // Apenas incrementa o contador
    } else if (h < raiz->altura) {
        raiz->esq = inserir(raiz->esq, h);
    } else {
        raiz->dir = inserir(raiz->dir, h);
    }
    return raiz;
}

// Variável global para controlar a formatação de espaços
int primeiro;

// Percurso em Ordem (In-Order) para imprimir ordenado
void emOrdem(Node* raiz) {
    if (raiz == NULL) return;

    emOrdem(raiz->esq);

    // Imprime a altura 'N' vezes, onde N é a quantidade armazenada
    for (int i = 0; i < raiz->quantidade; i++) {
        if (primeiro) {
            printf("%d", raiz->altura);
            primeiro = 0;
        } else {
            printf(" %d", raiz->altura);
        }
    }

    emOrdem(raiz->dir);
}

// Libera a memória da árvore
void liberarArvore(Node* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main() {
    int NC, N, h;
    
    // Leitura rápida recomendada pode ser feita com scanf normal em C,
    // mas evite cin/cout se fosse C++.
    if (scanf("%d", &NC) != 1) return 0;

    while (NC--) {
        if (scanf("%d", &N) != 1) break;
        
        Node* raiz = NULL;

        for (int i = 0; i < N; i++) {
            scanf("%d", &h);
            raiz = inserir(raiz, h);
        }

        primeiro = 1; // Reseta a flag para o novo caso de teste
        emOrdem(raiz);
        printf("\n");

        liberarArvore(raiz);
    }

    return 0;
}