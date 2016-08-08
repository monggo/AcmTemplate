typedef unsigned long long ULL;
const ULL MAGIC = 321;
vector<int> g[maxn];

ULL powMod(ULL a, int n) {
    ULL ret = 1ULL;
    while(n) {
        if(n&1) ret *= a;
        a *= a;
        n >>= 1;
    }
    return ret;
}
struct Hash {
    int o;
    int len; ULL value;
    Hash() :o(-1), len(0), value(0) {}
    Hash(char ch) :len(1), value(ch) {}
    Hash(int l, int v) :len(l), value(v) {}
    bool operator < (const Hash& b) const {
        return value < b.value;
    }
    bool operator == (const Hash& b) {
        return len == b.len && value == b.value;
    }
    Hash operator + (const Hash&b) {
        return Hash(len + b.len, value * powMod(MAGIC, b.len) + b.value);
    }
};
Hash self[maxn];
vector<Hash>child[maxn];
void getHash(int x, int fa) {
    child[x].clear();
    for(int i = g[x].size() - 1; ~i; --i) {
        int y = g[x][i];
        if (y == fa)continue;
        getHash(y, x, T);
        child[x].push_back(self[y]);
    }
    sort(child[x].begin(), child[x].end());
    self[x] = Hash();
    for (auto & it : child[x]) self[x] = self[x] + it;
    self[x] = Hash('(') + self[x] + Hash(')');
    self[x].o = x;
}
