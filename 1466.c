#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int valor;
    struct Node *esquerda;
    struct Node *direita;
} Node;

// Função para criar um novo nó
Node* criarNo(int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um valor na Árvore Binária de Busca
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

// Função para realizar o percurso em largura (BFS) usando uma fila
void bfs(Node* raiz) {
    if (raiz == NULL) return;

    // Fila simples usando um array de ponteiros para nós
    // Como N <= 500, um array de tamanho 505 é seguro
    Node* fila[505];
    int frente = 0;
    int tras = 0;

    // Enfileira a raiz
    fila[tras++] = raiz;

    int primeiro = 1; // Flag para controlar os espaços

    while (frente < tras) {
        // Desenfileira o nó atual
        Node* atual = fila[frente++];

        // Imprime o valor com formatação de espaço correta
        if (!primeiro) {
            printf(" ");
        }
        printf("%d", atual->valor);
        primeiro = 0;

        // Enfileira os filhos se existirem
        if (atual->esquerda != NULL) {
            fila[tras++] = atual->esquerda;
        }
        if (atual->direita != NULL) {
            fila[tras++] = atual->direita;
        }
    }
    printf("\n");
}

// Função para liberar a memória da árvore
void liberarArvore(Node* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

int main() {
    int C, i;
    scanf("%d", &C);

    for (i = 1; i <= C; i++) {
        int N, j, valor;
        scanf("%d", &N);

        Node* raiz = NULL;

        for (j = 0; j < N; j++) {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", i);
        bfs(raiz);
        printf("\n"); // Linha em branco exigida após cada caso de teste

        liberarArvore(raiz);
    }

    return 0;
}