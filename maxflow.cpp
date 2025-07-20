//Edmonds_Karp => O(V*E^2)
int n;
int capacity[101][101];
int getPath(int src, int dest, vector<int> &parent) {
    parent = vector<int>(n + 1, -1);
    queue<pair<int, int> > q;
    q.push({src, INF});
    while (q.size()) {
        int cur = q.front().first, flow = q.front().second;
        q.pop();
        if (cur == dest)
            return flow;
        for (int i = 1; i <= n; i++){
            if (parent[i] == -1 && capacity[cur][i]) {
                parent[i] = cur;
                q.push({i, min(flow, capacity[cur][i])});
                if (i == dest)
                    return q.back().second;
            }
	}
    }
    return 0;
}

int Edmonds_Karp(int source, int sink) {
    int max_flow = 0;
    int new_flow = 0;
    vector<int> parent(n + 1, -1);
    while (new_flow = getPath(source, sink, parent)) {
        max_flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        };
    }
    return max_flow;
}
// Dinic
struct Dinic {
    struct flowEdge {
        int from, to;
        ll cap, flow = 0;
        flowEdge(int from, int to, ll cap) :
        from(from), to(to), cap(cap) {
        }
    };
    vector<flowEdge> edges;
    int n, m = 0, source, sink;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    Dinic(int n, int source, int sink) :
    n(n), source(source), sink(sink), adj(n), level(n), ptr(n) {
    }
    void addEdge(int u, int v, ll cap) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }
    bool bfs() {
        queue<int> q;
        level = vector<int>(n, -1);
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &id : adj[cur]) {
                if (edges[id].cap - edges[id].flow <= 0)
                    continue;
                int nxt = edges[id].to;
                if (level[nxt] != -1)
                    continue;
                level[nxt] = level[cur] + 1;
                q.push(nxt);
            }
        }
        return level[sink] != -1;
    }
    ll dfs(int node, ll cur_flow) {
        if (cur_flow == 0 || node == sink)
            return cur_flow;
        for (int &cid = ptr[node]; cid < adj[node].size(); cid++) {
            int id = adj[node][cid];
            int nxt = edges[id].to;
            if (level[node] + 1 != level[nxt]|| edges[id].cap - edges[id].flow <= 0)
                continue;
            ll tmp = dfs(nxt, min(cur_flow, edges[id].cap - edges[id].flow));
            if (tmp == 0)
                continue;
            edges[id].flow += tmp;
            edges[id ^ 1].flow -= tmp;
            return tmp;
        }
        return 0;
    }
    ll flow() {
        ll max_flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(source, INF))
                max_flow += pushed;
        }
        return max_flow;
    }
};
//MinCut

struct MCMF {
    //0−based
    struct edge {
        int from, to, cost, cap, flow, backEdge;

        edge() {
            from = to = cost = cap = flow = backEdge = 0;
        }

        edge(int from, int to, int cost, int cap, int flow, int backEdge) : from(from), to(to), cost(cost), cap(cap), flow(flow),
                         backEdge(backEdge) {
        }

        bool operator <(const edge &other) const {
            return cost < other.cost;
        }
    };

    int n, src, dest;
    vector<vector<edge> > adj;
    const int OO = 1e9;

    MCMF(int n, int src, int dest) : n(n), src(src), dest(dest), adj(n) {
    }

    void addEdge(int u, int v, int cost, int cap) {
        edge e1 = edge(u, v, cost, cap, 0, adj[v].size());
        edge e2 = edge(v, u, -cost, 0, 0, adj[u].size());
        adj[u].push_back(e1);
        adj[v].push_back(e2);
    }

    pair<int, int> minCostMaxFlow() {
        int maxFlow = 0, cost = 0;
        while (true) {
            vector<pair<int, int> > path = spfa();
            if (path.empty())
                break;
            int new_flow = OO;
            for (auto &it: path) {
                edge &e = adj[it.first][it.second];
                new_flow = min(new_flow, e.cap - e.flow);
            }
            for (auto &it: path) {
                edge &e = adj[it.first][it.second];
                e.flow += new_flow;
                cost += new_flow * e.cost;
                adj[e.to][e.backEdge].flow -= new_flow;
            }
            maxFlow += new_flow;
        }
        return {maxFlow, cost};
    }

    enum visit {
        finished, in_queue, not_visited
    };

    vector<pair<int, int> > spfa() {
        vector<int> dis(n, OO), prev(n, -1), from_edge(n), state(n,
                                                                 not_visited);
        deque<int> q;
        dis[src] = 0;
        q.push_back(src);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            state[u] = finished;
            for (int i = 0; i < adj[u].size(); i++) {
                edge e = adj[u][i];
                if (e.flow >= e.cap || dis[e.to] <= dis[u] + e.cost)
                    continue;
                dis[e.to] = dis[u] + e.cost;
                prev[e.to] = u;
                from_edge[e.to] = i;
                if (state[e.to] == in_queue)
                    continue;
                if (state[e.to] == finished
                    || (!q.empty() && dis[q.front()] > dis[e.to]))
                    q.push_front(e.to);
                else
                    q.push_back(e.to);
                state[e.to] = in_queue;
            }
        }
        if (dis[dest] == OO)
            return {};
        vector<pair<int, int> > path;
        int cur = dest;
        while (cur != src) {
            path.push_back({prev[cur], from_edge[cur]});
            cur = prev[cur];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

