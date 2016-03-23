/*
LCA在线算法
节点是0~(n-1)
加边时:u.pb(v), v.pb(u)

memset(vis, false, sizeof(vis));
tot = 0; dir[0] = 0;
dfs(0, 1);
ST(2*n-1);
**/
/**************************************************************/
const int N = 50010;
const int M = 25;
int n, tot;
bool vis[N];
int ver[2*N], R[2*N], first[N], dir[N];
int dp[2*N][M];  //这个数组记得开到2*N，因为遍历后序列长度为2*n-1
struct node {
    int v, w;
    node(int a, int b)
    { v = a; w = b;}
};
vector<node> g[N];

void dfs(int u ,int dep) {
    vis[u] = true; ver[++tot] = u; first[u] = tot; R[tot] = dep;
    for (int i = 0; i < g[u].size(); i++)
        if(!vis[g[u][i].v]) {
            int v = g[u][i].v, w = g[u][i].w;
            dir[v] = dir[u]+w;
            dfs(v,dep+1);
            ver[++tot] = u; R[tot] = dep;
        }
}

void ST(int n) {
    for (int i = 1; i <= n; i++) dp[i][0] = i;
    for (int j = 1; (1<<j) <= n; j++)
        for (int i=1; i+(1<<j)-1 <= n; i++) {
            int a = dp[i][j-1], b = dp[i+(1<<j-1)][j-1];
            if (R[a] < R[b]) dp[i][j] = a;
            else dp[i][j] = b;
        }
}

int RMQ(int x, int y) {
    int K = (int)(log((double)(y-x+1))/log(2.0));
    int a = dp[x][K], b = dp[y-(1<<k)+1][K];
    if(R[a] < R[b]) return a;
    else return b;
}

int LCA(int u ,int v) {
    int x = first[u] , y = first[v];
    if(x > y) swap(x,y);
    int res = RMQ(x,y);
    return ver[res];
}

int cal(int u, int v) {
    int lca = LCA(u, v);
    return dir[x]+dir[y]-2*dir[lca];
}
/*****************************************************/
