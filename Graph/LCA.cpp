/*
倍增法
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

// dfs+ST在线算法
int depth = 0, b[N*2], cnt = 0;
int p[N], f[N];
void dfs(int u, int pre){
    int t = ++depth;
    b[++cnt] = t;
    f[t] = u;
    p[u] = cnt;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(v == pre) continue;
        dfs(v, u);
        b[++cnt] = t;
    }
}
int dp[N*2][20];
void init_rmq(int n) {
    for(int i = 1; i <= n; i++) dp[i][0] = b[i];
    int m = floor(log(n*1.0)/log(2.0));
    for(int j = 1; j <= m; j++)
        for(int i = 1;i <= n-(1<<j)+1; i++)
            dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
}
int rmq(int l, int r){
    int k = floor(log((r-l+1)*1.0)/log(2.0));
    return min(dp[l][k], dp[r-(1<<k)+1][k]);
}
int lca(int a ,int b) {
    if(p[a] > p[b]) swap(a,b);
    return f[rmq(p[a], p[b])];
}
/*
dfs(1, 0);
init_rmq(cnt);
*/
