#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um elemento na árvore
Node* insert(Node* root, char data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Função de pesquisa
int search(Node* root, char data) {
    if (root == NULL) {
        return 0; // Não encontrado
    }
    if (root->data == data) {
        return 1; // Encontrado
    }
    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Percurso Infixo (Esquerda, Raiz, Direita)
void infix(Node* root, int* first) {
    if (root == NULL) return;
    infix(root->left, first);
    
    if (!*first) printf(" ");
    printf("%c", root->data);
    *first = 0;
    
    infix(root->right, first);
}

// Percurso Prefixo (Raiz, Esquerda, Direita)
void prefix(Node* root, int* first) {
    if (root == NULL) return;
    
    if (!*first) printf(" ");
    printf("%c", root->data);
    *first = 0;
    
    prefix(root->left, first);
    prefix(root->right, first);
}

// Percurso Posfixo (Esquerda, Direita, Raiz)
void postfix(Node* root, int* first) {
    if (root == NULL) return;
    postfix(root->left, first);
    postfix(root->right, first);
    
    if (!*first) printf(" ");
    printf("%c", root->data);
    *first = 0;
}

// Função para liberar a memória da árvore (opcional para maratona, mas boa prática)
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;
    char command[10];
    char element;

    // Lê os comandos até o fim do arquivo (EOF)
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "I") == 0) {
            scanf(" %c", &element);
            root = insert(root, element);
        } else if (strcmp(command, "INFIXA") == 0) {
            int first = 1;
            infix(root, &first);
            printf("\n");
        } else if (strcmp(command, "PREFIXA") == 0) {
            int first = 1;
            prefix(root, &first);
            printf("\n");
        } else if (strcmp(command, "POSFIXA") == 0) {
            int first = 1;
            postfix(root, &first);
            printf("\n");
        } else if (strcmp(command, "P") == 0) {
            scanf(" %c", &element);
            if (search(root, element)) {
                printf("%c existe\n", element);
            } else {
                printf("%c nao existe\n", element);
            }
        }
    }

    freeTree(root);
    return 0;
}
