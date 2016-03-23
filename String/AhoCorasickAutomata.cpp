const int maxn = 610000;
int ch[maxn][26], fail[maxn], val[maxn];
int root, sz;
char str[1000100];

int newnode() {
    memset(ch[sz], -1, sizeof(ch[sz]));
    val[sz++] = 0;
    return sz-1;
}
void init() {
    sz = 0;
    root = newnode();
}
void insert(char str[]) {
    int len = strlen(str);
    int now = root;
    for (int i = 0; i < len; i++) {
        int& temp = ch[now][str[i]-'a'];
        if(temp == -1) temp = newnode();
        now = temp;
    }
    val[now]++;
}
void build() {
    queue<int> q;
    fail[root] = root;
    for (int i = 0; i < 26; i++) {
        int& temp = ch[root][i];
        if(temp == -1) temp = root;
        else {
            fail[temp] = root;
            q.push(temp);
        }
    }
    while(!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = 0; i < 26; i++) {
            if (ch[now][i] == -1) ch[now][i] = ch[fail[now]][i];
            else {
                fail[ch[now][i]] = ch[fail[now]][i];
                q.push(ch[now][i]);
            }
        }
    }
}

int query(char str[]) {
    int len = strlen(str);
    int now = root;
    int ret = 0;
    for (int i = 0; i < len; i++) {
        now = ch[now][str[i]-'a'];
        int temp = now;
        while(temp != root && ~val[temp]) {
            ret += val[temp];
            val[temp] = -1;
            temp = fail[temp];
        }
    }
    return ret;
}
