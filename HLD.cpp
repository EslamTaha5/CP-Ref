class HLD {
private:
    int n, timer;
    int nodeId[N], size[N], top[N], depth[N], parent[N], in[N], out[N];

    vector<int> graph[N];
    segment_tree<int> sg;

public:
    HLD(int nodes) : n(nodes), timer(1), sg(nodes) {
        for (int i = 1; i <= n; i++) {
            size[i] = 1;
        }
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void init(int root = 1) {
        dfs_size(root, 0);
        dfs_decompose(root, root);
    }

    void updateNode(int node, int val) {
        int l = nodeId[node], r = out[node];
        sg.update(l, r, val);
    }

    int queryPath(int u, int v) {
        int result = LLONG_MIN;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]])
                swap(u, v);

            int start = top[u];
           // result = max(result, sg.query(nodeId[start], nodeId[u]));
            u = parent[start];
        }

        if (depth[u] > depth[v])
            swap(u, v);
       // result = max(result, sg.query(nodeId[u], nodeId[v]));

        return result;
    }

private:
    void dfs_size(int node, int par) {
        parent[node] = par;

        if (par)
            depth[node] = depth[par] + 1;

        for (auto &next: graph[node]) {
            if (next != par) {
                dfs_size(next, node);
                size[node] += size[next];
                if (graph[node][0] == par || size[next] > size[graph[node][0]])
                    swap(graph[node][0], next);
            }
        }
    }

    void dfs_decompose(int node, int chain_top) {
        nodeId[node] = timer++;
        top[node] = chain_top;
        for (auto next: graph[node]) {
            if (next != parent[node]) {
                if (next == graph[node][0])
                    dfs_decompose(next, chain_top);
                else
                    dfs_decompose(next, next);
            }
        }
        out[node] = timer - 1;
    }
};
