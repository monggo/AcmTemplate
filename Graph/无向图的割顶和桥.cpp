vector<int> g[maxn];
int pre[maxn], low[maxn], iscut[maxn], dfs_clock;
void dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < g[i].size(); i++) {
        int v = g[u][i];
        if(!pre[v]) {
            child++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= pre[u]) {
                iscut[u] = 1;
            }
        }
        else if(pre[v]<pre[u] && v != fa) {
            low[u] = min(low[u], pre[v]);
        }
    }

    if(fa==-1 && child>1) iscut[u] = 1;
}
