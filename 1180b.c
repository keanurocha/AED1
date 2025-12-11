#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    int indiceOriginal;
    struct No *proximo;
} No;

void push(No **topo, int val, int idx) {
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = val;
    novo->indiceOriginal = idx;
    novo->proximo = *topo;
    *topo = novo;
}

No* pop(No **topo) {
    if (*topo == NULL) return NULL;
    No *aux = *topo;
    *topo = (*topo)->proximo;
    return aux;
}

int main() {
    int N, val, i;
    No *pilha = NULL;
    
    scanf("%d", &N);
    
    // Empilha todos os elementos
    for (i = 0; i < N; i++) {
        scanf("%d", &val);
        push(&pilha, val, i);
    }
    
    // Processa o primeiro elemento desempilhado
    No *temp = pop(&pilha);
    int menor = temp->valor;
    int posicao = temp->indiceOriginal;
    free(temp);
    
    // Desempilha o restante comparando
    while (pilha != NULL) {
        temp = pop(&pilha);
        if (temp->valor < menor) {
            menor = temp->valor;
            posicao = temp->indiceOriginal;
        }
        free(temp);
    }
    
    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);
    
    return 0;
}