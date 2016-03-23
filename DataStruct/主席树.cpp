/*
HDU 2665 Kth number
主席树 求静态区间第k小
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, m;
int rt[N], ls[N*20], rs[N*20], sum[N*20];
int a[N], b[N];
int tot;

void build(int l, int r, int& rt) {
    rt = tot++;
    sum[rt] = 0;
    if (l == r) return ;
    int m = (l+r)>>1;
    build(l, m, ls[rt]);
    build(m+1, r, rs[rt]);
}

void update(int pos, int l, int r, int last, int& rt) {
    rt = tot++;
    ls[rt] = ls[last]; rs[rt] = rs[last]; sum[rt] = sum[last]+1;
    if (l == r) return ;
    int m = (l+r)>>1;
    if (pos<=m) update(pos, l, m, ls[last], ls[rt]);
    else update(pos, m+1, r, rs[last], rs[rt]);
}

int query(int l, int r, int last, int rt, int k) {
    if (l == r) return l;
    int m = (l+r)>>1;
    int cnt = sum[ls[rt]]-sum[ls[last]];
    if (cnt>=k) return query(l, m, ls[last], ls[rt], k);
    else return query(m+1, r, rs[last], rs[rt], k-cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) { scanf("%d", &a[i]); b[i] = a[i]; }
        sort(b, b+n);
        int bn = 1;
        for (int i = 1; i < n; i++) if (b[i] != b[i-1]) b[bn++] = b[i];
        tot = 0;
        build(0, bn-1, rt[0]);
        for (int i = 0; i < n; i++) {
            int pos = lower_bound(b, b+bn, a[i])-b;
            update(pos, 0, bn-1, rt[i], rt[i+1]);
        }
        while (m--) {
            int l, r, k;
            scanf("%d %d %d", &l, &r, &k);
            int index = query(0, bn-1, rt[l-1], rt[r], k);
            printf("%d\n", b[index]);
        }
    }


    return 0;
}
