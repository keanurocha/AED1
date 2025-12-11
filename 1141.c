#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_TOTAL_LEN 1000005
#define ALPHABET 26

// Estrutura para armazenar as strings e manter seus índices originais
typedef struct {
    int id;
    int len;
    char *str;
} StringInfo;

// Memória para o Trie (Aho-Corasick)
// trie[u][c]: próximo nó
// fail[u]: link de falha
// val[u]: índice da string que termina neste nó (ou -1)
// last[u]: atalho para o próximo nó terminal na cadeia de falhas (otimização)
int trie[MAX_TOTAL_LEN][ALPHABET];
int fail[MAX_TOTAL_LEN];
int val[MAX_TOTAL_LEN];
int last[MAX_TOTAL_LEN];
int nodes_count;

// Memória para as strings e DP
char string_pool[MAX_TOTAL_LEN];
StringInfo infos[MAX_N];
int dp[MAX_N];
int sorted_indices[MAX_N]; // Mapeia a ordem ordenada para o índice original

// Função para comparar strings pelo tamanho (para o qsort)
int cmp(const void *a, const void *b) {
    StringInfo *sa = (StringInfo *)a;
    StringInfo *sb = (StringInfo *)b;
    if (sa->len != sb->len)
        return sa->len - sb->len;
    // Critério de desempate para estabilidade, embora não estritamente necessário
    return strcmp(sa->str, sb->str); 
}

// Inicializa um novo nó do Trie
void init_node(int u) {
    memset(trie[u], 0, sizeof(trie[u]));
    fail[u] = 0;
    val[u] = -1;
    last[u] = 0;
}

// Insere uma string no Trie
void insert(char *s, int original_id) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[u][c]) {
            trie[u][c] = ++nodes_count;
            init_node(nodes_count);
        }
        u = trie[u][c];
    }
    val[u] = original_id;
}

// Fila simples para o BFS do Aho-Corasick
int q[MAX_TOTAL_LEN];

// Constrói os failure links e os last links
void build_ac() {
    int head = 0, tail = 0;
    
    // Nível 1 (filhos da raiz)
    for (int i = 0; i < ALPHABET; i++) {
        if (trie[0][i]) {
            q[tail++] = trie[0][i];
        }
    }

    while (head < tail) {
        int u = q[head++];
        
        // Otimização: last[u] aponta para o ancestral mais próximo que é final de palavra
        if (val[fail[u]] != -1) 
            last[u] = fail[u];
        else 
            last[u] = last[fail[u]];

        for (int i = 0; i < ALPHABET; i++) {
            if (trie[u][i]) {
                fail[trie[u][i]] = trie[fail[u]][i];
                q[tail++] = trie[u][i];
            } else {
                trie[u][i] = trie[fail[u]][i];
            }
        }
    }
}

int main() {
    int N;
    
    while (scanf("%d", &N) && N != 0) {
        int pool_ptr = 0;
        
        // Leitura
        for (int i = 0; i < N; i++) {
            scanf("%s", &string_pool[pool_ptr]);
            infos[i].str = &string_pool[pool_ptr];
            infos[i].len = strlen(infos[i].str);
            infos[i].id = i;
            pool_ptr += infos[i].len + 1;
        }

        // Ordenar por tamanho
        qsort(infos, N, sizeof(StringInfo), cmp);

        // Resetar Trie
        nodes_count = 0;
        init_node(0);

        // Inserir todas as strings no Trie e guardar mapeamento
        for (int i = 0; i < N; i++) {
            insert(infos[i].str, i); // Usamos 'i' (índice ordenado) como ID no trie
            // Inicializa DP para cada string (mínimo 1, ela mesma)
            dp[i] = 1; 
        }

        // Construir autômato
        build_ac();

        int max_seq = 0;

        // Processar DP
        for (int i = 0; i < N; i++) {
            int u = 0;
            char *s = infos[i].str;
            
            // Percorrer o autômato com a string atual
            for (int j = 0; s[j]; j++) {
                u = trie[u][s[j] - 'a'];
                
                int temp = u;
                // Se o nó atual não é terminal, pula para o próximo terminal via 'last'
                if (val[temp] == -1) temp = last[temp];

                // Percorrer os sufixos válidos (outras strings que são substrings desta)
                while (temp > 0) {
                    int id_substring = val[temp];
                    
                    // Se encontramos uma string válida que é menor (já processada)
                    // Note que como ordenamos por tamanho, id_substring < i é garantido se tamanhos forem distintos.
                    // Se tamanhos forem iguais, strings são distintas (pelo enunciado), então não pode ser substring.
                    if (id_substring < i) {
                        if (dp[id_substring] + 1 > dp[i]) {
                            dp[i] = dp[id_substring] + 1;
                        }
                    }
                    
                    temp = last[temp];
                }
            }
            if (dp[i] > max_seq) max_seq = dp[i];
        }

        printf("%d\n", max_seq);
    }

    return 0;
}