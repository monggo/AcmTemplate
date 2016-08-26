/*
    设匹配串长度为n，模式串共m个，第i个记为si。
    ac自动机时间复杂度：O(n + sum(length(si)))
    在线ac自动机时间复杂度：(n*sqrt(n))
*/

const int maxn = 100100;
const int sigma_size = 26;

struct Trie {
    int ch[maxn][sigma_size], val[maxn], f[maxn];
    int sz;

    void init(){
        sz = 1;
        memset(ch, 0, sizeof(ch));
        memset(val, 0, sizeof(val));
        memset(f, 0, sizeof(f));
    }
    int idx(char c) { return c-'a'; }
    void insert(char *s) {
        int u = 0;
        for(int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) ch[u][c] = sz++;
            u = ch[u][c];
        }
        val[u] = 1;
    }
    int search(char *s) {
        int u = 0;
        for(int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return val[u];
    }
    void getFail() {
        queue<int> q;
        for(int i = 0; i < sigma_size; i++)
            if(ch[0][i]) q.push(ch[0][i]);

        while(!q.empty()) {
            int r = q.front(); q.pop();
            for(int c = 0; c < sigma_size; c++){
                int u = ch[r][c];
                if(!u) continue;
                q.push(u);
                int v = f[r];
                while(v && ch[v][c] == 0) v = f[v];
                f[u] = ch[v][c];
            }
        }
    }
    int find(char *T) {
        int j = 0, ans = 0;
        for(int i = 0; T[i] ; i++) {
            int c = idx(T[i]);
            while(j && ch[j][c]==0) j = f[j];
            j = ch[j][c];

            int temp = j;
            while(temp && ~val[temp]) { // 单词结尾：while(temp && ~val[temp] && val[temp])
                ans += val[temp];
                // val[temp] = -1; // 统计过的单词不用再统计
                temp = f[temp];
            }
        }
        return ans;
    }
};
Trie ac, buf;
void dfs(int u, int v) {
    for(int i = 0;i < sigma_size; i++) {
        if(buf.ch[v][i]) {
            int e2 = buf.ch[v][i];
            if(!ac.ch[u][i]) {
                memset(ac.ch[ac.sz], 0, sizeof(ac.ch[ac.sz]));
                ac.ch[u][i] = ac.sz++;
            }
            int e1 = ac.ch[u][i];
            ac.val[e1] |= buf.val[e2];
            dfs(e1, e2);
        }
    }
}
void join(){
    dfs(0, 0);
    buf.init();
    ac.getFail();
}
