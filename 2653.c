#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10007

typedef struct Registro {
    char *chave;
    struct Registro *proximo;
} Registro;

Registro *tabela_hash[HASH_SIZE];

unsigned int calcular_hash(char *s) {
    unsigned int h = 0;
    while (*s) {
        h = (h * 31) + *s++;
    }
    return h % HASH_SIZE;
}

int verificar_presenca(char *s) {
    unsigned int h = calcular_hash(s);
    Registro *atual = tabela_hash[h];
    while (atual) {
        if (strcmp(atual->chave, s) == 0) return 1;
        atual = atual->proximo;
    }
    return 0;
}

void inserir_na_tabela(char *s) {
    unsigned int h = calcular_hash(s);
    Registro *novo = (Registro*) malloc(sizeof(Registro));
    novo->chave = (char*) malloc(strlen(s) + 1);
    strcpy(novo->chave, s);
    novo->proximo = tabela_hash[h];
    tabela_hash[h] = novo;
}

int main() {
    char buffer[1000001];
    int contador = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        tabela_hash[i] = NULL;
    }

    while (scanf("%s", buffer) != EOF) {
        if (!verificar_presenca(buffer)) {
            inserir_na_tabela(buffer);
            contador++;
        }
    }

    printf("%d\n", contador);

    return 0;
}
