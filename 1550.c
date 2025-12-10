#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10005

// Estrutura para a fila da BFS
typedef struct {
    int val;
    int steps;
} Node;

// Função para inverter o número
int inverte(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int bfs(int start, int target) {
    bool visitado[MAX];
    memset(visitado, false, sizeof(visitado));
    
    Node fila[MAX * 2]; // Tamanho seguro para a fila
    int inicio = 0, fim = 0;
    
    // Insere o estado inicial
    fila[fim].val = start;
    fila[fim].steps = 0;
    fim++;
    visitado[start] = true;
    
    while (inicio < fim) {
        Node atual = fila[inicio++];
        
        if (atual.val == target) {
            return atual.steps;
        }
        
        // Operação 1: Adicionar 1
        int proximo = atual.val + 1;
        if (proximo < MAX && !visitado[proximo]) {
            visitado[proximo] = true;
            fila[fim].val = proximo;
            fila[fim].steps = atual.steps + 1;
            fim++;
        }
        
        // Operação 2: Inverter
        proximo = inverte(atual.val);
        if (proximo < MAX && !visitado[proximo]) {
            visitado[proximo] = true;
            fila[fim].val = proximo;
            fila[fim].steps = atual.steps + 1;
            fim++;
        }
    }
    return -1; // Não deve acontecer dados os limites do problema
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int A, B;
        scanf("%d %d", &A, &B);
        printf("%d\n", bfs(A, B));
    }
    
    return 0;
}