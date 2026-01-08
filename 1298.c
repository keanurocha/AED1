#include <stdio.h>
#include <stdlib.h>

#define LIM 305
#define TAM_G (2 * LIM)
#define MAX_PT (TAM_G + 5) * (TAM_G + 10)
#define MAX_LIG MAX_PT * 2

typedef struct {
    int a, b, p;
} Ligacao;

Ligacao lista[MAX_LIG];
int chefes[MAX_PT];
int dim, alt, lar;

int calcular_id(int r, int c) {
    return r * (lar + 1) + c;
}

int eh_limite(int r, int c) {
    return (r == 0 || r == alt || c == 0 || c == lar);
}

int procurar(int i) {
    if (chefes[i] == i) return i;
    return chefes[i] = procurar(chefes[i]);
}

void associar(int i, int j) {
    int r1 = procurar(i);
    int r2 = procurar(j);
    if (r1 != r2) chefes[r1] = r2;
}

int ordenar(const void* x, const void* y) {
    return ((Ligacao*)x)->p - ((Ligacao*)y)->p;
}

int main() {
    while (scanf("%d", &dim) != EOF) {
        alt = 2 * dim;
        lar = 2 * dim + 1;
        
        int nodo_mestre = calcular_id(alt + 1, lar + 1);
        for (int i = 0; i <= nodo_mestre; i++) chefes[i] = i;

        int e_total = 0;
        char linha[LIM + 5];

        for (int i = 1; i < alt; i++) {
            scanf("%s", linha);
            for (int j = 1; j <= dim; j++) {
                int r = i;
                int c = (i % 2 != 0) ? (2 * j - 1) : (2 * j);
                char sentido = linha[j - 1];

                int u_v = calcular_id(r - 1, c);
                int v_v = calcular_id(r + 1, c);
                if (eh_limite(r - 1, c)) u_v = nodo_mestre;
                if (eh_limite(r + 1, c)) v_v = nodo_mestre;

                lista[e_total].a = u_v;
                lista[e_total].b = v_v;
                lista[e_total].p = (sentido == 'V') ? 0 : 1;
                e_total++;

                int u_h = calcular_id(r, c - 1);
                int v_h = calcular_id(r, c + 1);
                if (eh_limite(r, c - 1)) u_h = nodo_mestre;
                if (eh_limite(r, c + 1)) v_h = nodo_mestre;

                lista[e_total].a = u_h;
                lista[e_total].b = v_h;
                lista[e_total].p = (sentido == 'H') ? 0 : 1;
                e_total++;
            }
        }

        qsort(lista, e_total, sizeof(Ligacao), ordenar);

        int resultado = 0;
        for (int i = 0; i < e_total; i++) {
            if (procurar(lista[i].a) != procurar(lista[i].b)) {
                associar(lista[i].a, lista[i].b);
                resultado += lista[i].p;
            }
        }
        printf("%d\n", resultado);
    }
    return 0;
}
