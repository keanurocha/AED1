#include <stdio.h>

void dfs(int u);

int g[1000][1000];
int used[1000];
int n, count;

int main() {

    int t;
    scanf("%d", &t);

    while (t--) {
        int start, m, a, b;
        scanf("%d %d %d", &start, &n, &m);

        for (int i = 0; i < n; i++) {
            used[i] = 0;
            for (int j = 0; j < n; j++)
                g[i][j] = 0;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            g[a][b] = g[b][a] = 1;
        }

        count = 0;
        dfs(start);

        printf("%d\n", count);
    }

    return 0;
}

void dfs(int u) {
    used[u] = 1;
    for (int v = 0; v < n; v++) {
        if (g[u][v] && !used[v]) {
            count++;
            dfs(v);
            count++;
        }
    }
}
