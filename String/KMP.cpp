const int N = 10010;
char s[100*N], p[N];
int F[N];

void getFail(char* p, int* f) {
    int m = strlen(p);
    f[0] = f[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = f[i];
        while (j && p[j]!=p[i]) j = f[j];
        f[i+1] = (p[i]==p[j]) ? j+1 : 0;
    }
}

int kmp(char* t, char* p, int* f) {
    int res = 0;
    int n = strlen(t), m = strlen(p);
    getFail(p, f);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j && p[j]!=t[i]) j = f[j];
        if (p[j] == t[i]) j++;
        if (j == m) {
            res++;
            //i-m+1
            j=f[j];
        }
    }
    return res;
}
