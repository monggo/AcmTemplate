/**
节点i表示的回文串是以节点i为右端点的回文串
cnt[i]  节点i表示的最长回文串出现的次数(count后)
num[i]  以节点i结尾的回文串个数(长度不等)
len[i]  节点i表示的最长回文串的长度
p       添加节点的个数,p-2为本质不同的回文串个数
n       添加字符的个数

空间复杂度为O(N*字符集大小),时间复杂度为O(N*log(字符集大小))
*/
const int maxn = 330000;
const int C = 30;

int Next[maxn][C];
int fail[maxn];
int cnt[maxn];
int num[maxn];
int len[maxn];
int s[maxn];
int last;
int p;
int n;

int newnode(int x) {
	for (int i = 0; i < C; i++) Next[p][i] = 0;
	cnt[p] = 0; num[p] = 0; len[p] = x;
	return p++;
}
void init() {
	p = 0;
	newnode(0); newnode(-1);
	last = 0; n = 0;
	s[0] = -1; fail[0] = 1;
}
int get_fail(int x) {
	while(s[n-len[x]-1] != s[n]) x = fail[x];
	return x;
}
void add(int c) {
	c -= 'a';
	s[++n] = c;
	int cur = get_fail(last);
	if (!Next[cur][c]) {
		int now = newnode(len[cur]+2);
		fail[now] = Next[get_fail(fail[cur])][c];
		Next[cur][c] = now;
		num[now] = num[fail[now]]+1;
	}
	last = Next[cur][c];
	cnt[last]++;
}

void count() {
	for (int i = p-1; i >= 0; i--) cnt[fail[i]] += cnt[i];
}
