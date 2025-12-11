#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1005

// Definição do Nó da Lista
typedef struct No {
    char dado;
    struct No *prox;
} No;

// Definição da Pilha (ponteiro para o topo)
typedef struct {
    No *topo;
} PilhaLista;

// Inicializa a pilha
void inicializar(PilhaLista *p) {
    p->topo = NULL;
}

// Verifica se está vazia
int vazia(PilhaLista *p) {
    return p->topo == NULL;
}

// Empilhar (Push)
void push(PilhaLista *p, char item) {
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo) {
        novoNo->dado = item;
        novoNo->prox = p->topo;
        p->topo = novoNo;
    }
}

// Desempilhar (Pop)
void pop(PilhaLista *p) {
    if (!vazia(p)) {
        No *temp = p->topo;
        p->topo = p->topo->prox;
        free(temp); // Libera a memória do nó removido
    }
}

// Limpa toda a pilha (caso sobrem itens)
void limpar(PilhaLista *p) {
    while (!vazia(p)) {
        pop(p);
    }
}

// Função principal de verificação
const char* verificarExpressao(char *expressao) {
    PilhaLista p;
    inicializar(&p);
    int erroEncontrado = 0;
    
    int tamanho = strlen(expressao);
    
    for (int i = 0; i < tamanho; i++) {
        if (expressao[i] == '(') {
            push(&p, '(');
        } else if (expressao[i] == ')') {
            if (vazia(&p)) {
                erroEncontrado = 1;
                break; // Fecha parênteses sem abertura prévia
            }
            pop(&p);
        }
    }
    
    const char* resultado;
    
    if (!erroEncontrado && vazia(&p)) {
        resultado = "correct";
    } else {
        resultado = "incorrect";
    }
    
    // Importante: Liberar memória residual se a expressão for incorreta (pilha não vazia)
    limpar(&p); 
    
    return resultado;
}

int main() {
    char expressao[MAX];
    
    // Lê expressões até o final do arquivo (EOF)
    while (scanf("%s", expressao) != EOF) {
        printf("%s\n", verificarExpressao(expressao));
    }
    
    return 0;
}