const int maxn = 100;
const int INF = 0x3f3f3f3f;
struct Edge {
    int from, to, cap, flow;
};
struct Dinic {
    int m, s, t;
    vector<Edge> edges;
    vector<int> g[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

	void init() {
		edges.clear();
		for(int i = 0; i < maxn; i++) g[i].clear();
	}

	void addEdge(int from, int to, int cap) {
		edges.push_back((Edge){from, to, cap, 0});
		edges.push_back((Edge){to, from, 0, 0});
		m = edges.size();
		g[from].push_back(m-2);
		g[to].push_back(m-1);
	}

    bool bfs() {
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int i = 0; i < g[x].size(); i++) {
                Edge& e = edges[g[x][i]];
                if(!vis[e.to] && e.cap>e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x]+1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x, int a) {
        if(x==t || a==0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i<g[x].size(); i++) {
            Edge& e = edges[g[x][i]];
            if(d[x]+1==d[e.to] && (f=dfs(e.to, min(a, e.cap-e.flow)))>0) {
                e.flow += f;
                edges[g[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s, int t) {
        this->s = s; this->t = t;
        int flow = 0;
        while(bfs()) {
            memset(cur, 0, sizeof cur);
            flow += dfs(s, INF);
        }
        return flow;
    }
};
