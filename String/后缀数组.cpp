char s[N];
int sa[N], t[N], t2[N], c[N], n;
int ran[N], height[N];

void build_sa(int m) {
    int i, *x = t, *y = t2;
    for (i = 0; i < m; i++) c[i] = 0;
    for (i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (i = 1; i < m; i++) c[i] += c[i-1];
    for (i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (i = n-k; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i]-k;
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[y[i]]]++;
        for (i = 0; i < m; i++) c[i] += c[i-1];
        for (i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for (i = 1; i < n; i++)
            x[sa[i]] = y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
        if (p >= n) break;
        m = p;
    }
}

int m;
int cmp_suffix(char* pattern, int p) {
    return strncmp(pattern, s+sa[p], m);
}

int find(char* P) {
    m = strlen(P);
    if (cmp_suffix(P, 0) < 0) return -1;
    if (cmp_suffix(p, n-1) > 0) return -1;
    int L = 0, R = n-1;
    while (R >= L) {
        int M = L+(R-L)/2;
        int res = cmp_suffix(P, M);
        if (!res) return M;
        if (res < 0) R = M-1;
        else L = M+1;
    }
}

void get_height() {
    int i, j, k = 0;
    for (i = 0; i < n; i++) ran[sa[i]] = i;
    for (i = 0; i < n; i++) {
        if (k) k--;
        j = sa[ran[i]-1];
        while (s[i+k] == s[j+k]) k++;
        height[ran[i]] = k;
    }
}

int d[maxn][20], Log[maxn];
void rmq_init() {
    Log[0] = -1;
    for(int i=1;i<=maxn;i++)
        Log[i] = (i&(i-1)) ? Log[i-1] : Log[i-1]+1;

    for(int i = 0; i < n; i++) d[i][0] = height[i];
    for(int i = 1; i <= Log[n]; i++)
        for(int j = 0; j+(1<<i)-1 < n; j++)
            d[j][i] = min(d[j][i-1], d[j+(1<<(i-1))][i-1]);
}

int lcp(int l, int r) {
    if(l == r) return n-1-l;
    l = ran[l]; r = ran[r];
    if(l > r) swap(l, r);
    int a = l+1, b = r;
    int k = Log[b-a+1];
    /// k = floor(log(b-a+1.0)/log(2.0));
    return min(d[a][k], d[b-(1<<k)+1][k]);
}
