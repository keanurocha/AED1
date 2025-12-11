#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1005

// Definição da Pilha baseada em vetor
typedef struct {
    char itens[MAX];
    int topo;
} PilhaVetor;

// Inicializa a pilha
void inicializar(PilhaVetor *p) {
    p->topo = -1;
}

// Verifica se está vazia
int vazia(PilhaVetor *p) {
    return p->topo == -1;
}

// Empilhar (Push)
void push(PilhaVetor *p, char item) {
    if (p->topo < MAX - 1) {
        p->itens[++(p->topo)] = item;
    }
}

// Desempilhar (Pop)
void pop(PilhaVetor *p) {
    if (!vazia(p)) {
        p->topo--;
    }
}

// Função principal de verificação
const char* verificarExpressao(char *expressao) {
    PilhaVetor p;
    inicializar(&p);
    
    int tamanho = strlen(expressao);
    
    for (int i = 0; i < tamanho; i++) {
        if (expressao[i] == '(') {
            push(&p, '(');
        } else if (expressao[i] == ')') {
            if (vazia(&p)) {
                return "incorrect"; // Tentou fechar mas não tinha aberto
            }
            pop(&p);
        }
    }
    
    if (vazia(&p)) {
        return "correct";
    } else {
        return "incorrect"; // Sobraram parênteses abertos
    }
}

int main() {
    char expressao[MAX];
    
    // Lê expressões até o final do arquivo (EOF)
    // O scanf com %s lê a string até o primeiro espaço ou quebra de linha
    while (scanf("%s", expressao) != EOF) {
        printf("%s\n", verificarExpressao(expressao));
    }
    
    return 0;
}