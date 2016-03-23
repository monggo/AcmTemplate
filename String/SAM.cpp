/** 一点性质
 * 1.代码中 p->len 变量，它表示该状态能够接受的最长的字符串长度。
 *   该状态能够接受的最短的字符串长度等于该状态的 fa 指针指向的结点的 len + 1。
 *   (p->len)-(p->fa->len)：表示该状态能够接受的不同的字符串数,不同的字符串之间是连续的,
 *   既:p 和 p->fa 之间 有最长的公共后缀长度 p->fa->len
 * 2.从root到每一个接收态表示一个后缀,到每一个普通节点表示一个子串
 * 3.totol表示不同子串的数量
 * 4.一个子串的起始下标为sam.e[p].len-len+1(p为表示该子串的状态)
*/

struct Node {
    int ch[26];
    int f, len;
    void init() {
        f = -1, len = 0;
        memset(ch, 0xff, sizeof(ch));
    }
};
struct SAM {
    Node e[N<<1];
    int idx, last, totol;
    void init() {
        idx = last = totol = 0;
        e[idx++].init();
    }
    int newnode() {
        e[idx].init();
        return idx++;
    }
    void add(int c) {
        int end = newnode();
        e[end].len = e[last].len+1;
        int tmp = last;
        for ( ; tmp!=-1 && e[tmp].ch[c]==-1; tmp = e[tmp].f)
            e[tmp].ch[c] = end;
        if (tmp == -1) {
            e[end].f = 0;
            //totol += e[end].len-e[e[end].f].len;
        }
        else {
            int nxt = e[tmp].ch[c];
            if (e[tmp].len+1 == e[nxt].len) {
                e[end].f = nxt;
                //totol += e[end].len-e[e[end].f].len;
            }
            else {
                int np = newnode();
                //totol -= e[tmp].len-e[e[tmp].f].len;
                //totol -= e[nxt].len-e[e[nxt].f].len;
                e[np] = e[nxt];
                e[np].len = e[tmp].len + 1;
                e[end].f = e[nxt].f = np;
                //totol += e[tmp].len-e[e[tmp].f].len;
                //totol += e[nxt].len-e[e[nxt].f].len;
                //totol += e[np].len-e[e[np].f].len;
                //totol += e[end].len-e[e[end].f].len;
                for (; tmp!=-1 && e[tmp].ch[c]==nxt; tmp = e[tmp].f)
                    e[tmp].ch[c] = np;
            }
        }
        last = end;
    }
};

/********************************************************************/
// 使用记忆化搜索按字典序输出后缀或子串
string temp[N<<1];  // 临时保存字符串(不是保存子串)
int a[N<<1];        // 表示节点是否是可接受态、
temp[0] = "";
memset(a, 0, sizeof(a));
int p = sam.last;
while (p != -1) { a[p] = 1; p = sam.e[p].f; }
dfs(0);
void dfs(int x) {
    for (int i = 0; i < 26; i++) {
        int t = sam.e[x].ch[i];
        if (t != -1) {
            temp[t] = temp[x]+(char)(i+'a');
            if(a[t] == 1) cout<<temp[t]<<endl; // 输出后缀
            //cout<<temp[t]<<endl;             // 输出子串
            dfs(t);
        }
    }
}
/********************************************************************/

/********************************************************************/
// 统计每个节点出现的次数
int pk[N<<1];   // pk[i]表示排名为i的节点编号
int w[N];       // w[i]表示值为i的数出现了多少次
int num[N<<1];  // num[i]表示i号节点表示的最长子串能够被包含多少次
memset(num, 0, sizeof(num));
int len = strlen(str);
// 按照每个节点所能够承载的最长子串进行排序
for (int i = 0; i <= len; i++) w[i] = 0;
for (int i = 1; i < sam.idx; i++) w[sam.e[i].len]++;
for (int i = 1; i <= len; i++) w[i] += w[i-1];
for (int i = sam.idx-1; i > 0; i--) pk[w[sam.e[i].len]--] = i;
// 初始化原始的后缀
for (int i = 0, p = 0; i < len; i++) num[p = sam.e[p].ch[str[i]-'a']] = 1;
for (int i = sam.idx-1; i > 0; --i) { // 长度长的后缀能够更新与其拥有相同后缀的较短的后缀
    if (sam.e[pk[i]].f > 0) num[sam.e[pk[i]].f] += num[pk[i]];
}
/********************************************************************/

/********************************************************************/
// 所有的子串按照字典序排序并去重后，求第K大的子串.
int len = strlen(str);
// 按照每个节点所能够承载的最长子串进行排序(代码如上)
// 初始化每个节点的dp[]值为1，然后根据按照len值排序的节点顺序进行更新
for (int i = 1; i < sam.idx; i++) dp[i] = 1;
for (int i = sam.idx-1; i > 0; i--) {
    int t = pk[i];
    for (int j = 0; j < 26; j++) {
        if (sam.e[t].ch[j] != -1) dp[t] += dp[sam.e[t].ch[j]];
    }
}
// 求第K大的子串
int idx = 0, p = 0;
while (k) {
    for (int i = 0; i < 26; i++) {
        if (dp[sam.e[p].ch[i]] < k) k -= dp[sam.e[p].ch[i]];
        else {
            ans[idx++] = i;
            k--;
            p = sam.e[p].ch[i];
            break;
        }
    }
}
for (int i = 0; i < idx; i++) printf("%c", ans[i]+'a');
/********************************************************************/