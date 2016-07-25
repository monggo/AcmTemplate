vector<int> g[maxn];
int pre[maxn], low[maxn], sccno[maxn], dfs_clock, scc_cnt;
stack<int> s;

void dfs(int u) {
    pre[u] = low[u] = ++dfs_clock;
    s.push(u);
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(!pre[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = min(low[u], pre[v]);
        }
    }
    if(low[u] == pre[u]) {
        scc_cnt++;
        for( ; ; ) {
            int x = s.top(); s.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}
void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for(int i = 0; i < n; i++)
        if(!pre[i]) dfs(i);
}
