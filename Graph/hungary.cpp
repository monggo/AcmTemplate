/*
二分图最小顶点覆盖 = 二分图最大匹配；
DAG图的最小路径覆盖 = 节点数（n）- 最大匹配数；
二分图最大独立集 = 节点数（n）- 最大匹配数；

一般图最大独立集 = 补图的最大团
*/

const int maxn = 555;

int n;  // 一侧的点数
vector<int> g[maxn];  // g[i]表示与左边点i相连的右边的点
int from[maxn];  // from[i]表示最大匹配中与右边点i相连的左边的点
int mx[maxn];  // mx[i]表示最大匹配中与左边边点i相连的右边边的点
bool use[maxn];

bool match(int x) {
    for(int i = 0; i < g[x].size(); ++i) {
        int v = g[x][i];
        if(!use[v]) {
            use[v] = true;
            if(from[v]==-1 || match(from[v])) {
                from[v] = x;
                mx[x] = v;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int tot = 0;
    memset(from, -1, sizeof(from));
    memset(mx, -1, sizeof(mx));
    for(int i = 1; i <= n; ++i) {
        memset(use, 0, sizeof(use));
        if(match(i)) tot++;
    }
    return tot;
}
