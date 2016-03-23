const int maxNode = 4444;
struct Treap {
    int root, treapCnt, key[maxNode], priority[maxNode],
        childs[maxNode][2], cnt[maxNode], size[maxNode];

    Treap() {
        root = 0;
        treapCnt = 1;
        priority[0] = INT_MAX;
        size[0] = 0;
    }
    void update(int x) {
        size[x] = size[childs[x][0]]+cnt[x]+size[childs[x][1]];
    }
    void rotate(int& x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1^t];
        childs[y][1^t] = x;
        update(x);
        update(y);
        x = y;
    }
    void __insert(int& x, int k) {
        if(x) {
            if(key[x] == k) {
                cnt[x]++;
            } else {
                int t = key[x]<k;
                __insert(childs[x][t], k);
                if(priority[childs[x][t]] < priority[x]) rotate(x, t);
            }
        } else {
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);
    }
    void __erase(int& x, int k) {
        if(key[x] == k) {
            if(cnt[x] > 0) {
                cnt[x]--;
            } else {
                if(childs[x][0]==0 && childs[x][1]==0) {
                    x = 0;
                    return ;
                }
                int t = priority[childs[x][0]]>priority[childs[x][1]];
                rotate(x, t);
                __erase(x, k);
            }
        } else {
            __erase(childs[x][key[x]<k], k);
        }
        update(x);
    }
    int __getKth(int x, int k) {
        if(k <= size[childs[x][0]]) return __getKth(childs[x][0], k);
        k -= size[childs[x][0]]+cnt[x];
        if(k <= 0) return key[x];
        return __getKth(childs[x][1], k);
    }
    int __rank(int x, int k) {
        int r = size[childs[x][0]];
        if(k < key[x]) return __rank(childs[x][0], k);
        else if (k > key[x]) return __rank(childs[x][1], k)+r+cnt[x];
        return r;
    }
    int __prev(int x, int k) {
        if(x == 0) return INT_MIN;
        if(k <= key[x]) return __prev(childs[x][0], k);
        return max(key[x], __prev(childs[x][1], k));
    }
    int __next(int x, int k) {
        if(x == 0) return INT_MAX;
        if(k >= key[x]) return __next(childs[x][1], k);
        return min(key[x], __next(childs[x][0], k));
    }
    void insert(int k) { __insert(root, k); }
    void erase(int k) { __erase(root , k); }
    int getKth(int k) { __getKth(root, k); }
    int rank(int x) { return __rank(root, x); }
    int prev(int x) { return __prev(root, x); }
    int next(int x) { return __next(root, x);}
};