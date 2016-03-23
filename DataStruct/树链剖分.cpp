siz[N]，用来保存以x为根的子树节点个数
son[N]，用来保存重儿子
dep[N]，用来保存当前节点的深度
fa[N]，用来保存当前节点的父亲
top[N]，用来保存当前节点的所在链的顶端节点
tid[N]，用来保存树中每个节点剖分后的新编号
rank[N]，用来保存当前节点在线段树中的位置

int tim;
int siz[N], son[N], dep[N], fa[N], top[N], tid[N], rank[N];
vector<int> edge[N];

void init() {
    tim = 0;
    memset(son, -1, sizeof(son));
}
// 第一次dfs：记录所有的重边
void dfs1(int u, int father, int d) {
    dep[u] = d;
    fa[u] = father;
    siz[u] = 1;
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i];
        if (v != father) {
            dfs1(v, u, d+1);
            siz[u] += siz[v];
            if (son[u]==-1 || siz[v]>siz[son[u]]) son[u] = v;
        }
    }
}
// 第二次dfs：连重边成重链；要初始化tim
void dfs2(int u, int tp) {
    top[u] = tp;
    tid[u] = tim++;
    rank[tid[u]] = u;
    if (son[u]  == -1) return ;
    dfs2(son[u], tp);
    for (int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i];
        if (v!=son[u] && v!=fa[u]) dfs2(v, v);
    }
}

void query(int u, int v) {
    int tp1= top[u], tp2 = top[v];
    while (tp1 != tp2) {
        if (dep[tp1] < dep[tp2]) {
            swap(tp1, tp2);
            swap(u, v);
        }
        query(tid[tp1], tid[u], 0, n-1, 1);
        u = fa[tp1];
        tp1 = top[u];
    }

    if (dep[u] > dep[v]) swap(u, v);
    query(tid[u], tid[v], 0, n-1, 1);
}
