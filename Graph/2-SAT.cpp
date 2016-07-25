const int maxn = 2010;

struct TwoSAT {
    int n;
    vector<int> g[maxn*2];
    bool mark[maxn*2];
    int s[maxn*2], c;
    bool dfs(int x) {
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        s[c++] = x;
        for(int i = 0; i < g[x].size(); i++)
            if(!dfs(g[x][i])) return false;
        return true;
    }
    void init(int n) {
        this->n = n;
        for(int i = 0; i < n*2; i++) g[i].clear();
        memset(mark, 0, sizeof(mark));
    }
    // <x, y>, x(y)val==1表示x'(y')
    void add_edge(int x, int xval, int y, int yval) {
        x = x*2+xval;
        y = y*2+yval;
        g[x].push_back(y);
    }

    // O(n*m)
    bool solve() {
        for(int i = 0; i < n*2; i += 2) {
            if(!mark[i] && !mark[i+1]) {
                c = 0;
                if(!dfs(i)) {
                    while(c > 0) mark[s[--c]] = false;
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }

    int pre[maxn*2], low[maxn*2], sccno[maxn*2], dfs_clock, scc_cnt;
    stack<int> S;
    void dfs1(int u) {
        pre[u] = low[u] = ++dfs_clock;
        S.push(u);
        for(int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if(!pre[v]) {
                dfs1(v);
                low[u] = min(low[u], low[v]);
            } else if (!sccno[v]) {
                low[u] = min(low[u], pre[v]);
            }
        }
        if(low[u] == pre[u]) {
            scc_cnt++;
            for( ; ; ) {
                int x = S.top(); S.pop();
                sccno[x] = scc_cnt;
                if(x == u) break;
            }
        }
    }
    void find_scc() {
        dfs_clock = scc_cnt = 0;
        memset(sccno, 0, sizeof(sccno));
        memset(pre, 0, sizeof(pre));
        for(int i = 0; i < n*2; i++)
            if(!pre[i]) dfs1(i);
    }

    // O(m)
    bool solve1() {
        find_scc();
        for(int i = 0; i < n; i++) {
            if(sccno[i*2] == sccno[i*2+1]) return false;
        }

        for(int i = 0; i < 2*n; i+=2){
            if(scc[i] < scc[i+1]) { mark[i]=true; mark[i+1]=false; }
            else { mark[i]=false; mark[i+1]=true; }
        }

        return true;
    }

}towsat;
