//MaximumBipartiteMatching
// O(VE) in worst case , but in practice i t runs in O(E) or O(sqrt (V)E)
vector<vector<int>> adj;
vector<int> rowAssign, colAssign, vis;//make v is array instance of vector
int test_id;
bool canMatch(int i) {
    if (vis[i] == test_id)
        return false;
    vis[i] = test_id;
    for (int j : adj[i]) {
        if (colAssign[j] == -1) {
            colAssign[j] = i;
            rowAssign[i] = j;
            return true;
        }
    }
    for (int j : adj[i]) {
        if (canMatch(colAssign[j])) {
            colAssign[j] = i;
            rowAssign[i] = j;
            return true;
        }
    }
    return false;
}
// O(rows ∗ edges) //number of operation could by s t r i c t l y l essthan order
int maximum_bipartite_matching(int rows, int cols) {
    int maxFlow = 0;
    rowAssign = vector<int>(rows, -1);
    colAssign = vector<int>(cols, -1);
    vis = vector<int>(rows);
    for (int i = 0; i < rows; i++) {
        test_id++;
        if (canMatch(i))
            maxFlow++;
    }
    vector<pair<int, int>> matches;
    for (int j = 0; j < cols; j++)
        if (~colAssign[j])
            matches.push_back( { colAssign[j], j });
    return maxFlow;
}
//
//Hopcroft−Karp algorithm for maximum b ipa r t i te matching
//O( sqrt (V) ∗ E)
struct Hopcroft_Karp {//1−based
#define NIL 0
#define INF INT_MAX
    int n, m;
    vector<vector<int>> adj;
    vector<int> rowAssign, colAssign, dist;
    bool bfs() {
        queue<int> q;
        dist = vector<int>(adj.size(), INF);
        for (int i = 1; i <= n; i++)
            if (rowAssign[i] == NIL) {
                dist[i] = 0;
                q.push(i);
            }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (dist[cur] >= dist[NIL])break;
            for (auto& nxt : adj[cur]) {
                if (dist[colAssign[nxt]] == INF) {
                    dist[colAssign[nxt]] = dist[cur] + 1;
                    q.push(colAssign[nxt]);
                }
            }
        }
        return dist[NIL] != INF;
    }
    bool dfs(int i) {
        if (i == NIL)
            return true;
        for (int j : adj[i]) {
            if (dist[colAssign[j]] == dist[i] + 1 && dfs(colAssign[j
            ])) {
                colAssign[j] = i;
                rowAssign[i] = j;
                return true;
            }
        }
        dist[i] = INF;
        return false;
    }
    Hopcroft_Karp(int n, int m)
    :n(n), m(m), adj(n + 1), rowAssign(n + 1), colAssign(m + 1)
    {
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    int maximum_bipartite_matching() {
        int rt = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++)
                if (rowAssign[i] == NIL && dfs(i))
                    rt++;
        }
        return rt;
    }
};
