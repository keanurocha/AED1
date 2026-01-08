#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10005
#define MEM_MAX 1000005
#define SIGMA 26

typedef struct {
    int tam;
    char *texto;
} Item;

int trie[MEM_MAX][SIGMA];
int falha[MEM_MAX];
int fim_id[MEM_MAX];
int atalho[MEM_MAX];
int nos_qtd;

char pool[MEM_MAX];
Item itens[N_MAX];
int dp[N_MAX];
int fila[MEM_MAX];

int comparar(const void *a, const void *b) {
    return ((Item *)a)->tam - ((Item *)b)->tam;
}

void limpar_no(int n) {
    memset(trie[n], 0, sizeof(trie[n]));
    falha[n] = 0;
    fim_id[n] = -1;
    atalho[n] = 0;
}

void inserir(char *s, int id) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[u][c]) {
            trie[u][c] = ++nos_qtd;
            limpar_no(nos_qtd);
        }
        u = trie[u][c];
    }
    fim_id[u] = id;
}

void construir_ac() {
    int h = 0, t = 0;
    for (int i = 0; i < SIGMA; i++) {
        if (trie[0][i]) fila[t++] = trie[0][i];
    }

    while (h < t) {
        int u = fila[h++];
        int f = falha[u];
        
        atalho[u] = (fim_id[f] != -1) ? f : atalho[f];

        for (int i = 0; i < SIGMA; i++) {
            if (trie[u][i]) {
                falha[trie[u][i]] = trie[f][i];
                fila[t++] = trie[u][i];
            } else {
                trie[u][i] = trie[f][i];
            }
        }
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        int offset = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", &pool[offset]);
            itens[i].texto = &pool[offset];
            itens[i].tam = strlen(itens[i].texto);
            offset += itens[i].tam + 1;
        }

        qsort(itens, n, sizeof(Item), comparar);

        nos_qtd = 0;
        limpar_no(0);

        for (int i = 0; i < n; i++) {
            inserir(itens[i].texto, i);
            dp[i] = 1;
        }

        construir_ac();

        int max_global = 0;
        for (int i = 0; i < n; i++) {
            int u = 0;
            char *s = itens[i].texto;
            
            for (int j = 0; s[j]; j++) {
                u = trie[u][s[j] - 'a'];
                int temp = (fim_id[u] != -1) ? u : atalho[u];

                while (temp > 0) {
                    int sub = fim_id[temp];
                    if (sub < i) {
                        if (dp[sub] + 1 > dp[i]) dp[i] = dp[sub] + 1;
                    } else if (sub == i && s[j+1] == '\0') {
                    }
                    temp = atalho[temp];
                }
            }
            if (dp[i] > max_global) max_global = dp[i];
        }
        printf("%d\n", max_global);
    }
    return 0;
}
