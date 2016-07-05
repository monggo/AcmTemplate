/*
在这类问题中建边的规则就是“必须”，对于边<i，j>，它的意义就是选择了i就必须选j。
对于题目中给出的每对关系都可以化成下面的几种形式：

A,B不能同时取　　<A,B'><B,A'>

A,B不能都不取　　<A',B><B',A>

A,B必须都取或者都不取　　<A,B><B,A><A',B'><B',A'>

必须取A　　<A',A>

不能取A    <A,A'>
*/

// 递归+回溯，时间复杂度O(n*m), 求字典序最小的解。
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
    // <x, y>, x(y)val==0表示x(y), x(y)val==1表示x'(y')
    void add_edge(int x, int xval, int y, int yval) {
        x = x*2+xval;
        y = y*2+yval;
        g[x].push_back(y);
    }
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
}towsat;
