#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó para a lista encadeada
typedef struct Node {
    int valor;
    struct Node *proximo;
} Node;

// Função para criar e inserir um novo nó no final da lista
void inserir(Node **tabela, int indice, int valor) {
    // Aloca memória para o novo nó
    Node *novoNo = (Node *)malloc(sizeof(Node));
    novoNo->valor = valor;
    novoNo->proximo = NULL;

    // Se a lista naquele índice estiver vazia, o novo nó será a cabeça
    if (tabela[indice] == NULL) {
        tabela[indice] = novoNo;
    } else {
        // Se não, percorre até o final da lista para inserir
        Node *atual = tabela[indice];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

// Função para imprimir a tabela
void imprimirTabela(Node **tabela, int M) {
    for (int i = 0; i < M; i++) {
        printf("%d -> ", i);
        
        Node *atual = tabela[i];
        while (atual != NULL) {
            printf("%d -> ", atual->valor);
            atual = atual->proximo;
        }
        // O caractere '\' é especial, então usamos '\\' para imprimir uma barra invertida
        printf("\\\n");
    }
}

// Função para liberar a memória alocada
void liberarTabela(Node **tabela, int M) {
    for (int i = 0; i < M; i++) {
        Node *atual = tabela[i];
        while (atual != NULL) {
            Node *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

int main() {
    int N; // Quantidade de casos de teste
    scanf("%d", &N);

    while (N--) {
        int M, C;
        // M = endereços-base (tamanho da tabela)
        // C = quantidade de chaves
        scanf("%d %d", &M, &C);

        // Cria a tabela hash (array de ponteiros para Nodes)
        // Calloc inicializa tudo com NULL
        Node *tabela[100]; // O problema diz que M <= 100, então estático é seguro e rápido
        for(int i = 0; i < M; i++) tabela[i] = NULL;

        // Leitura e inserção das chaves
        for (int i = 0; i < C; i++) {
            int chave;
            scanf("%d", &chave);
            int indice = chave % M; // Função de dispersão h(x) = x mod M
            inserir(tabela, indice, chave);
        }

        // Imprime o resultado formatado
        imprimirTabela(tabela, M);

        // Libera a memória usada neste caso de teste
        liberarTabela(tabela, M);

        // Se houver mais casos de teste, imprime uma linha em branco entre eles
        if (N > 0) {
            printf("\n");
        }
    }

    return 0;
}