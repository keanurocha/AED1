#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POOL_SIZE 2000005
#define MAX_JEWELS 1000005

// Variáveis globais para alocação na área de dados estática (evita estouro de pilha/stack)
char stringPool[MAX_POOL_SIZE];
char *jewels[MAX_JEWELS];

// Função de comparação para o qsort
int compare(const void *a, const void *b) {
    // Cast para ponteiro de ponteiro de char, depois desreferencia para pegar as strings
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    return strcmp(strA, strB);
}

int main() {
    int n = 0;
    int poolIndex = 0;
    int len;
    int i;
    int distinctCount;

    // Lê strings até o fim do arquivo (EOF)
    // Lê diretamente para o pool na posição correta
    while (scanf("%s", &stringPool[poolIndex]) != EOF) {
        
        // Salva o ponteiro de onde começa essa jóia no array de ponteiros
        jewels[n] = &stringPool[poolIndex];
        
        // Calcula o tamanho da string lida
        len = strlen(jewels[n]);
        
        // Atualiza o índice do pool para a próxima posição livre.
        // O '+ 1' é crucial: ele pula o caractere '\0' que o scanf inseriu automaticamente
        // e garante que a próxima string não sobrescreva o terminador da atual.
        poolIndex += len + 1;
        
        // Incrementa contagem de jóias
        n++;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    // Ordena o array de ponteiros (as strings em si não mudam de lugar na memória, só os ponteiros)
    qsort(jewels, n, sizeof(char *), compare);

    // Conta quantos tipos distintos existem
    distinctCount = 1;
    for (i = 1; i < n; i++) {
        // Se a string atual é diferente da anterior (na lista ordenada), é um novo tipo
        if (strcmp(jewels[i], jewels[i-1]) != 0) {
            distinctCount++;
        }
    }

    printf("%d\n", distinctCount);

    return 0;
}