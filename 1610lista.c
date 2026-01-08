#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 10005

typedef struct Elemento {
    int alvo;
    struct Elemento* proximo;
} Elemento;

Elemento* grafo[TAM_MAX];
int marcado[TAM_MAX];
int total_v, total_a;

void conectar(int origem, int destino) {
    Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
    novo->alvo = destino;
    novo->proximo = grafo[origem];
    grafo[origem] = novo;
}

void desalocar() {
    for (int i = 0; i <= total_v; i++) {
        Elemento* aux = grafo[i];
        while (aux != NULL) {
            Elemento* deletar = aux;
            aux = aux->proximo;
            free(deletar);
        }
        grafo[i] = NULL;
    }
}

int investigar(int n) {
    marcado[n] = 1;

    Elemento* it = grafo[n];
    while (it != NULL) {
        int vizinho = it->alvo;
        if (marcado[vizinho] == 1) return 1;
        if (marcado[vizinho] == 0) {
            if (investigar(vizinho)) return 1;
        }
        it = it->proximo;
    }

    marcado[n] = 2;
    return 0;
}

int main() {
    int casos;
    if (scanf("%d", &casos) != 1) return 0;

    while (casos--) {
        scanf("%d %d", &total_v, &total_a);

        for (int i = 0; i <= total_v; i++) {
            marcado[i] = 0;
            grafo[i] = NULL;
        }

        for (int i = 0; i < total_a; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            conectar(x, y);
        }

        int achou = 0;
        for (int i = 1; i <= total_v; i++) {
            if (marcado[i] == 0) {
                if (investigar(i)) {
                    achou = 1;
                    break;
                }
            }
        }

        if (achou) printf("SIM\n");
        else printf("NAO\n");

        desalocar();
    }

    return 0;
}
