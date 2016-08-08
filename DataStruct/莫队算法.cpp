#include <bits/stdc++.h>
using namespace std;

typedef  long long LL;
const int N = 50010;

int n, m, bk;
int color[N], num[N];

struct  qnode{
    int l, r;
    int id;
    bool operator < (const qnode& cmp) const {
        return l/bk!=cmp.l/bk ? l/bk<cmp.l/bk : r < cmp.r;
    }
}q[N];

LL gcd(LL a, LL b) {
    return  b==0 ? a : gcd(b, a%b);
}

LL temp;

void update(int p, int v) {
    temp -= (LL)num[color[p]]*num[color[p]];
    num[color[p]] += v;
    temp += (LL)num[color[p]]*num[color[p]];
}


LL up[N], dw[N];

void solve() {
    memset(num, 0, sizeof(num));
    int l = 1, r = 0;
    temp = 0;
    for(int i = 0; i < m; i++) {
        int id = q[i].id;
        if(q[i].l >= q[i].r) {
            up[id] = 0, dw[id] = 1;
            continue;
        }
        while(r < q[i].r) { update(r+1, 1); r++; }
        while(r > q[i].r) { update(r, -1); r--; }
        while(l < q[i].l) { update(l, -1); l++; }
        while(l > q[i].l) { update(l-1, 1), l--; }
        up[id] = temp - (r-l+1);
        dw[id] = (LL)(r-l+1)*(r-l);
        LL d = gcd(up[id], dw[id]);
        if(d == 0) {
            up[id] =0; dw[id] = 1;
        } else {
            up[id] /= d; dw[id] /= d;
        }
    }
}

int main() {

    while(cin>>n>>m) {

        bk = (int)sqrt(1.0*n);

        for(int i = 1; i <= n; i++) cin>>color[i];
        for(int i = 0;i < m; i++) {
            cin>>q[i].l>>q[i].r;
            q[i].id = i;
        }
        sort(q, q+m);
        solve();
        for(int i = 0; i < m; i++) cout<<up[i]<<'/'<<dw[i]<<'\n';
    }



    return 0;
}
