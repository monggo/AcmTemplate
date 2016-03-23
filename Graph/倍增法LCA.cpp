/*
2^17=131072;
2^18=262144;
*/
const int maxh = 18;
void dfs(int u, int fa) {
    d[u] = d[fa]+1;
    p[u][0] = fa;
    for (int i = 1; i < maxh; i++) p[u][i] = p[p[u][i-1]][i-1];
    int sz = edge[u].size();
    for (int i = 0; i < sz; i++){
        int v = edge[u][i];
        if (v == fa) continue;
        dfs(v, u);
    }
}
int lca(int a, int b) {
    if(d[a] > d[b]) swap(a, b);
    if(d[a] < d[b]){
        int del = d[b]-d[a];
        for (int i = 0; i < maxh; i++)
            if (del&(1<<i)) b = p[b][i];
    }
    if (a != b) {
        for (int i = maxh-1; i >= 0; i--)
            if(p[a][i] != p[b][i])
                 a = p[a][i], b = p[b][i];
        a = p[a][0]; b = p[b][0];
    }
    return a;
}
