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

void getHeight() {
    int i, j, k = 0;
    for (i = 0; i < n; i++) ran[sa[i]] = i;
    for (i = 0; i < n; i++) {
        if (k) k--;
        j = sa[ran[i]-1];
        while (s[i+k] == s[j+k]) k++;
        height[ran[i]] = k;
    }
}
