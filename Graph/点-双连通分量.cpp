
struct Edge{
    int u, v;
    Edge() {}
    Edge(int u, int v) : u(u), v(v) {}
};

vector<int> g[maxn], bcc[maxn];
int pre[maxn], low[maxn], iscut[maxn], bccno[maxn], dfs_clock, bcc_cnt;
stack<Edge> s;

void tarjan(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        Edge e = Edge(u, v);
        if(!pre[v]) {
            s.push(e);
            child++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] == pre[u]) {
                iscut[u] = 1;
                bcc_cnt++;
                bcc[bcc_cnt].clear();
                for( ; ; ) {
                    Edge x = s.top(); s.pop();
                    if(bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if(bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if(x.u==u && x.v==v) break;
                }
            } else if(low[v] > pre[u]) {
                s.pop();
            }
        }
        else if(pre[v]<pre[u] && v != fa) {
            s.push(e);
            low[u] = min(low[u], pre[v]);
        }
    }

    if(fa==-1 && child==1) iscut[u] = 0;
}
void find_bcc() {
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for(int i = 0; i < n; i++)
        if(!pre[i]) tarjan(i, -1);
}
