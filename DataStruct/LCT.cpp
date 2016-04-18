/*  HDOJ 4010 */
//切割、合并子树,路径上所有点的点权增加一个值,查询路径上点权的最大值
#include <bits/stdc++.h>

using namespace std;

const int maxn=330000;

int ch[maxn][2], pre[maxn], key[maxn];
int add[maxn], rev[maxn], Max[maxn];
bool rt[maxn];

void update_add(int r, int d) {
    if(!r) return ;
    key[r] += d;
    add[r] += d;
    Max[r] += d;
}
void update_rev(int r) {
    if(!r) return ;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}
void push_down(int r) {
    if(add[r]) {
        update_add(ch[r][0], add[r]);
        update_add(ch[r][1], add[r]);
        add[r] = 0;
    }
    if(rev[r]) {
        update_rev(ch[r][0]);
        update_rev(ch[r][1]);
        rev[r]=0;
    }
}
void push_up(int r) {
    Max[r] = max(max(Max[ch[r][0]],Max[ch[r][1]]), key[r]);
}
void Rotate(int x) {
    int y=pre[x], kind=(ch[y][1]==x);
    ch[y][kind] = ch[x][!kind];
    pre[ch[y][kind]] = y;
    pre[x] = pre[y];
    pre[y] = x;
    ch[x][!kind] = y;
    if(rt[y]) rt[y]=false, rt[x]=true;
    else ch[pre[x]][ch[pre[x]][1]==y] = x;
    push_up(y);
}
void P(int r) {
    if(!rt[r]) P(pre[r]);
    push_down(r);
}
void Splay(int r) {
    P(r);
    while(!rt[r]) {
        int f=pre[r], ff=pre[f];
        if(rt[f]) Rotate(r);
        else if((ch[ff][1]==f)==(ch[f][1]==r)) Rotate(f), Rotate(r);
        else Rotate(r), Rotate(r);
    }
    push_up(r);
}
int Access(int x) {
    int y = 0;
    for( ; x; x = pre[y=x]) {
        Splay(x);
        rt[ch[x][1]] = true;
        rt[ch[x][1]=y] = false;
        push_up(x);
    }
    return y;
}
int findroot(int u) {
    while(pre[u]) u = pre[u];
    return u;
}
void mroot(int r) {
    Access(r);
    Splay(r);
    update_rev(r);
}
void link(int u, int v) {
    if(findroot(u) == findroot(v)) {
        puts("-1");
        return ;
    }
    mroot(u);
    pre[u] = v;
}
// make the node x be the root,cut the edge between node y and its parent.
void cut(int u, int v) {
    if(u==v || findroot(u)!=findroot(v)) {
        puts("-1");
        return ;
    }
    mroot(u);
    Splay(v);
    pre[ch[v][0]] = pre[v];
    pre[v] = 0;
    rt[ch[v][0]] = true;
    ch[v][0] = 0;
    push_up(v);
}
void Add(int u, int v, int w) {
    if(findroot(u) != findroot(v)) {
        puts("-1");
        return ;
    }
    mroot(u);
    Access(v);
    Splay(v);
    update_add(v, w);
}
void query(int u, int v) {
    if(findroot(u) != findroot(v)) {
        puts("-1");
        return ;
    }
    mroot(u);
    Access(v);
    Splay(v);
    printf("%d\n", Max[v]);
}

int n;
vector<int> edge[maxn];

void init() {
    for(int i = 1; i <= n; i++) edge[i].clear();
    for(int i = 1; i <= n; i++) {
            pre[i] = 0;
            ch[i][0] = ch[i][1] = 0;
            rev[i] = 0;
            add[i] = 0;
            rt[i] = true;
        }
}

void dfs(int u) {
    for(int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i];
        if(pre[v] != 0) continue;
        pre[v] = u;
        dfs(v);
    }
}

int main() {
    while(scanf("%d", &n) != EOF) {

        init();

        for(int i = 0; i < n-1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }

        pre[1] = -1;
        dfs(1);
        pre[1] = 0;

        for(int i = 1; i <= n; i++) {
            scanf("%d", key+i);
            Max[i] = key[i];
        }

        int q;
        scanf("%d", &q);
        while(q--) {
            int op;
            scanf("%d", &op);
            if(op == 1) {
                int x, y;
                scanf("%d %d", &x, &y);
                link(x, y);
            } else if(op == 2) {
                int x, y;
                scanf("%d %d", &x, &y);
                cut(x, y);
            } else if(op == 3) {
                int x, y, w;
                scanf("%d %d %d", &w, &x, &y);
                Add(x, y, w);
            } else if(op == 4) {
                int x, y;
                scanf("%d %d", &x, &y);
                query(x, y);
            }
        }
        putchar(10);
    }
    return 0;
}

