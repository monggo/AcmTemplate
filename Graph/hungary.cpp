/*
����ͼ��С���㸲�� = ����ͼ���ƥ�䣻
DAGͼ����С·������ = �ڵ�����n��- ���ƥ������
����ͼ�������� = �ڵ�����n��- ���ƥ������

һ��ͼ�������� = ��ͼ�������
*/

const int maxn = 555;

int n;  // һ��ĵ���
vector<int> g[maxn];  // g[i]��ʾ����ߵ�i�������ұߵĵ�
int from[maxn];  // from[i]��ʾ���ƥ�������ұߵ�i��������ߵĵ�
int mx[maxn];  // mx[i]��ʾ���ƥ��������߱ߵ�i�������ұ߱ߵĵ�
bool use[maxn];

bool match(int x) {
    for(int i = 0; i < g[x].size(); ++i) {
        int v = g[x][i];
        if(!use[v]) {
            use[v] = true;
            if(from[v]==-1 || match(from[v])) {
                from[v] = x;
                mx[x] = v;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int tot = 0;
    memset(from, -1, sizeof(from));
    memset(mx, -1, sizeof(mx));
    for(int i = 1; i <= n; ++i) {
        memset(use, 0, sizeof(use));
        if(match(i)) tot++;
    }
    return tot;
}
