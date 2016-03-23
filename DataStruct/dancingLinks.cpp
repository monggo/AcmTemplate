// 行列坐标都是从1开始
// 精确覆盖
const int maxnode = 500010;
const int MaxM = 1010;
const int MaxN = 510;
struct DLX
{
    int n, m, size;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd;
    void init(int _n, int _m)
    {
        n = _n;
        m = _m;
        for(int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1; i <= n; i++) H[i] = -1;
    }
    void Link(int r, int c) {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0) H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c) {
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    void Dance(int d) {
        if(ansd != -1 && ansd <= d)return;
        if(R[0] == 0) {
            if(ansd == -1)ansd = d;
            else if(d < ansd)ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(S[i] < S[c]) c = i;
        remove(c);
        for(int i = D[c];i != c;i = D[i]) {
            for(int j = R[i];j != i;j = R[j])remove(Col[j]);
            Dance(d+1);
            for(int j = L[i];j != i;j = L[j])resume(Col[j]);
        }
        resume(c);
    }
};

// 重复覆盖
struct DLX
{
    int n, m, size;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd;
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        for (int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for (int i = 1; i <= n; i++)  H[i] = -1;
    }
    void Link(int r,int c) {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)  H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c) {
        for (int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c) {
        for (int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[MaxM];
    int f() {
        int ret = 0;
        for (int c = R[0]; c != 0; c = R[c])  v[c] = true;
        for (int c = R[0]; c != 0; c = R[c])
            if (v[c]) {
                ret++;
                v[c] = false;
                for (int i = D[c]; i != c; i = D[i])
                    for(int j = R[i]; j != i; j = R[j])
                        v[Col[j]] = false;
            }
        return ret;
    }
    void Dance(int d) {
        if (d + f() >= ansd)  return;
        if (R[0] == 0) {
            if (d < ansd)  ansd = d;
            return;
        }
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i])
            if (S[i] < S[c])  c = i;
        for (int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for (int j = R[i]; j != i; j = R[j])  remove(j);
            Dance(d+1);
            for (int j = L[i]; j != i; j = L[j])  resume(j);
            resume(i);
        }
    }
};
