#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g[30][30], vis[30], lst[30];
int n_v, n_e, p;

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void explorar(int u) {
    vis[u] = 1;
    lst[p++] = u;
    for (int v = 0; v < n_v; v++) {
        if (g[u][v] && !vis[v]) {
            explorar(v);
        }
    }
}

int main() {
    int t, idx = 1;
    if (scanf("%d", &t) != 1) return 0;

    while (t--) {
        scanf("%d %d", &n_v, &n_e);
        memset(g, 0, sizeof(g));
        memset(vis, 0, sizeof(vis));

        for (int i = 0; i < n_e; i++) {
            char o, d;
            scanf(" %c %c", &o, &d);
            g[o - 'a'][d - 'a'] = g[d - 'a'][o - 'a'] = 1;
        }

        printf("Case #%d:\n", idx++);
        int c_count = 0;

        for (int i = 0; i < n_v; i++) {
            if (!vis[i]) {
                p = 0;
                explorar(i);
                qsort(lst, p, sizeof(int), cmp);
                for (int j = 0; j < p; j++) {
                    printf("%c,", lst[j] + 'a');
                }
                printf("\n");
                c_count++;
            }
        }
        printf("%d connected components\n\n", c_count);
    }
    return 0;
}
