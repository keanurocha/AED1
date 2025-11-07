#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void printPre(Node* root) {
    if (root == NULL) return;
    printf(" %d", root->value); 
    printPre(root->left);
    printPre(root->right);
}

void printIn(Node* root) {
    if (root == NULL) return;
    printIn(root->left);
    printf(" %d", root->value); 
    printIn(root->right);
}

void printPost(Node* root) {
    if (root == NULL) return;
    printPost(root->left);
    printPost(root->right);
    printf(" %d", root->value); 
}

int main() {
    int C, N, i, j, value;
    scanf("%d", &C);

    for (i = 1; i <= C; i++) {
        scanf("%d", &N);

        Node* root = NULL;
        for (j = 0; j < N; j++) {
            scanf("%d", &value);
            root = insert(root, value);
        }

        printf("Case %d:\n", i);
        
        
        printf("Pre.:");
        printPre(root);
        printf("\n");

        printf("In..:");
        printIn(root);
        printf("\n");

        printf("Post:");
        printPost(root);
        printf("\n\n"); 
        
        freeTree(root);
    }

    return 0;
}