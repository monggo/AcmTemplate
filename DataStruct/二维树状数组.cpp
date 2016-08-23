int n;
int c[MAXN][MAXN];
int lowbit(int x) {
    return x&(-x);
}
void add(int x, int y, int val) {
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= n; j += lowbit(j))
            c[i][j] += val;
}
int sum(int x, int y) {
    int ret = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        for(int j = y; j > 0; j -= lowbit(j))
            ret += c[i][j];
    return ret;
}
