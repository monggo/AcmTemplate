#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int n, m, q;
int w[N], t[N];

void init_hash() {
    for(int i = 1; i <= n; i++) t[i]=w[i];
    sort(t+1, t+n+1);
    m = unique(t+1, t+n+1)-t-1;
}
int Hash(int x) {
    return lower_bound(t+1, t+m+1, x)-t;
}

/*              主席树部分           */
int rt[N], ls[N*20], rs[N*20], sum[N*20];
int tot;
void build(int l, int r, int& rt) {
    rt = tot++;
    sum[rt] = 0;
    if (l == r) return ;
    int m = (l+r)>>1;
    build(l, m, ls[rt]);
    build(m+1, r, rs[rt]);
}

void update(int pos, int l, int r, int last, int& rt) {
    rt = tot++;
    ls[rt] = ls[last]; rs[rt] = rs[last]; sum[rt] = sum[last]+1;
    if (l == r) return ;
    int m = (l+r)>>1;
    if (pos<=m) update(pos, l, m, ls[last], ls[rt]);
    else update(pos, m+1, r, rs[last], rs[rt]);
}

int query(int l, int r, int lrt, int rrt, int lcart, int lcapos, int k) {
    if (l == r) return l;
    int m = (l+r)>>1;
    int cnt = sum[ls[lrt]]+sum[ls[rrt]]-2*sum[ls[lcart]];
    cnt += (l<=lcapos&&lcapos<=m);
    if (cnt>=k) return query(l, m, ls[lrt], ls[rrt], ls[lcart], lcapos, k);
    else return query(m+1, r, rs[lrt], rs[rrt], rs[lcart], lcapos, k-cnt);
}
/*              主席树部分           */

/*              LCA部分            */
vector<int> g[N];
int depth = 0, b[N*2], cnt = 0;
int p[N], f[N];
void init() {
    tot = 0;
    depth = 0;
    cnt = 0;
    for(int i = 0; i < N; i++) g[i].clear();
}
void dfs(int u, int pre){
    int t = ++depth;
    b[++cnt] = t;
    f[t] = u;
    p[u] = cnt;
    update(Hash(w[u]), 1, m, rt[pre], rt[u]);
    for(int i = 0; i <g[u].size(); i++) {
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
/*              LCA部分            */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin>>n>>q) {
        init();
        for(int i = 1; i <= n; i++) cin>>w[i];
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        init_hash();
        build(1, m, rt[0]);
        dfs(1, 0);
        init_rmq(cnt);

        while(q--) {
            int u, v, k;
            cin>>u>>v>>k;
            int ans = t[ query(1, m, rt[u], rt[v], rt[lca(u,v)], Hash(w[lca(u,v)]), k) ];
            cout<<ans<<'\n';
        }
    }

    return 0;
}
