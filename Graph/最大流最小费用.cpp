const int INF = 0x3f3f3f3f;
const int N = 110;

struct edge{
    int from, to, cap, flow, cost;
};

struct MCMF{
    int n, m, s, t, flow, cost;
    vector<edge> edges;
    vector<int> g[N];
    int inq[N];
    int d[N];
    int p[N];
    int a[N];

    void init(int n) {
        this->n = n;
        flow = cost = 0;
        for (int i = 0; i < n; i++) g[i].clear();
        edges.clear();
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back((edge){from, to, cap, 0, cost});
        edges.push_back((edge){to, from, 0, 0, -cost});
        m = edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }

    bool BellmanFord(int s, int t, int& flow, int& cost) {
        for (int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (int i = 0; i < g[u].size(); i++) {
                edge& e = edges[g[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u]+e.cost) {
                    d[e.to] = d[u]+e.cost;
                    p[e.to] = g[u][i];
                    a[e.to] = min(a[u], e.cap-e.flow);
                    if (!inq[e.to]) { q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += a[t];
        cost += d[t]*a[t];
        int u = t;
        while (u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }

    int Mincost(int s, int t) {
        while (BellmanFord(s, t, flow, cost)) ;
    }
}mcmf;

