#define key_value ch[ch[root][1]][0]
const int maxn=110000;

int n, a[maxn];

int ch[maxn][2], rev[maxn], add[maxn], sz[maxn], pre[maxn], key[maxn], minn[maxn];
int root, tot;
int sss[maxn], tot2;

void erase(int r) {
    if(r) sss[++tot2] = r;
}
void newNode(int& r, int father, int k) {
    if(tot2) {
        r = sss[tot2--];
        erase(ch[r][0]);
        erase(ch[r][1]);
    }
    else r = ++tot;
    ch[r][0]=ch[r][1]=rev[r]=add[r]=0;
    sz[r]=1; pre[r]=father; key[r]=minn[r]=k;
}
void updRev(int r) {
    if(!r) return ;
    swap(ch[r][0],ch[r][1]);
    rev[r] ^= 1;
}
void updAdd(int r, int d) {
    if(!r) return ;
    key[r]+=d; minn[r]+=d; add[r]+=d;
}
void pushUp(int r) {
    sz[r] = sz[ch[r][1]]+sz[ch[r][0]]+1;
    minn[r] = key[r];
    if(ch[r][0]) minn[r] = min(minn[r], minn[ch[r][0]]);
    if(ch[r][1]) minn[r] = min(minn[r], minn[ch[r][1]]);
}
void pushDown(int r) {
    if(rev[r]) {
        updRev(ch[r][0]); updRev(ch[r][1]);
        rev[r] = 0;
    }
    if(add[r]) {
        updAdd(ch[r][0],add[r]); updAdd(ch[r][1],add[r]);
        add[r] = 0;
    }
}
void build(int& x, int l, int r, int fa) {
    if(l > r) return ;
    int mid = (l+r)>>1;
    newNode(x, fa, a[mid]);
    build(ch[x][0], l, mid-1, x);
    build(ch[x][1], mid+1, r, x);
    pushUp(x);
}
void init() {
    root=tot=tot2=0;
    ch[root][0]=ch[root][1]=pre[root]=sz[root]=0;
    minn[root]=key[root]=INT_MAX;
    newNode(root, 0, INT_MAX);
    newNode(ch[root][1], root, INT_MAX);
    build(key_value, 1, n, ch[root][1]);
    pushUp(ch[root][1]);
    pushUp(root);
}
void rotate(int r, int kind) {
    int y = pre[r];
    pushDown(y); pushDown(r);
    ch[y][!kind] = ch[r][kind];
    pre[ch[r][kind]] = y;
    if(pre[y]) ch[pre[y]][ch[pre[y]][1]==y] = r;
    pre[r] = pre[y];
    pre[y] = r;
    ch[r][kind] = y;
    pushUp(y);
}
void splay(int r, int goal) {
    pushDown(r);
    while(pre[r] != goal) {
        int y = pre[r];
        if(pre[y] == goal) {
            pushDown(y); pushDown(r);
            rotate(r, ch[y][0]==r);
        } else {
            pushDown(pre[y]); pushDown(y); pushDown(r);
            int kind = (ch[pre[y]][0]==y);
            if(ch[y][kind] == r) rotate(r, !kind);
            else rotate(y, kind);
            rotate(r, kind);
        }
    }
    pushUp(r);
    if(goal == 0) root = r;
}
int getKth(int r, int k) {
    pushDown(r);
    int t = sz[ch[r][0]]+1;
    if(k == t) return r;
    if(t < k) return getKth(ch[r][1], k-t);
    else return getKth(ch[r][0], k);
}
int getMin(int r) {
    pushDown(r);
    while(ch[r][0]) {
        r = ch[r][0];
        pushDown(r);
    }
    return r;
}
int getMax(int r) {
    pushDown(r);
    while(ch[r][1]) {
        r = ch[r][1];
        pushDown(r);
    }
    return r;
}
void removeRoot() {
    if(ch[root][1]==0 || ch[root][0]==0) {
        root = ch[root][0]+ch[root][1];
        pre[root] = 0;
        return ;
    }
    int k = getMin(ch[root][1]); // 找到右子树中最小的
    splay(k, root); // 旋转过来，使得右子树没有左孩子
    key_value = ch[root][0];
    root = ch[root][1];
    pre[ch[root][0]] = root;
    pre[root] = 0;
    pushUp(root);
}
/*****************DEBUG*********************/
void SHOW(int x) {
    pushDown(x);
    if(ch[x][0]) SHOW(ch[x][0]);
    printf("x: %d size: %d pre: %d left: %d right: %d key: %d\n",x,sz[x],pre[x],ch[x][0],ch[x][1],key[x]);
    if(ch[x][1]) SHOW(ch[x][1]);
}
void DEBUG() {
    cout<<"..........debug.............."<<endl;
    SHOW(root);
    cout<<"..........debug.............."<<endl;
}
/*****************DEBUG*********************/
