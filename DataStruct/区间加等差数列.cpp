int n;
LL sum[N];
LL addflag[N], addcnt[N];
void init() {
    memset(addflag, 0, sizeof addflag);
    memset(addcnt, 0, sizeof addcnt);
}
// 首项为v，公差为sub
void update(int l, int r, LL v, LL add) {
    addflag[l] += v;
    addcnt[l] += add;
    addflag[r+1] -= v+(r-l+1)*add;
    addcnt[r+1] -= add;
}
void gao() {
    for(int i = 1; i <= n; i++) {
        addflag[i] += addflag[i-1]+addcnt[i-1];
        addcnt[i] += addcnt[i-1];
        sum[i] = addflag[i];
    }
}
