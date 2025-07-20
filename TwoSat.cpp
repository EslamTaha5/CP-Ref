class TwoSatSolver {
public:
    // one_based
    int n, id;
    vector<vector<int> > adj, comps;
    vector<int> inStack, low, dfs_n, comp, assigned_val, comp_value, comp_root;
    stack<int> sk;

    TwoSatSolver(int _n) {
        n = _n;
        id = 0;
        adj = vector<vector<int> >(2 * n + 2);
        inStack = dfs_n = low = comp = comp_root = vector<int>(2 * n + 2);
        assigned_val = comp_value = vector<int>(2 * n + 2, -1);
    }

    void dfs(int i) {
        low[i] = dfs_n[i] = ++id;
        inStack[i] = 1;
        sk.push(i);
        for (auto &it: adj[i]) {
            if (!dfs_n[it]) {
                dfs(it);
                low[i] = min(low[i], low[it]);
            } else if (inStack[it]) {
                low[i] = min(low[i], dfs_n[it]);
            }
        }
        if (low[i] == dfs_n[i]) {
            comps.push_back(vector<int>());
            int x = -1;
            while (x != i) {
                x = sk.top();
                sk.pop();
                inStack[x] = 0;
                comps.back().push_back(x);
                comp[x] = comps.size();
            }
            comp_root[comp[i]] = i;
        }
    }

     int get_not(int x) {
        return (x <= n ? x + n : x - n);
    }

    void add_edge_or(int u, int v) {
        adj[get_not(u)].push_back(v);
        adj[get_not(v)].push_back(u);
    }

    bool solve() {
        for (int i = 1; i <= 2 * n; i++) {
            if (dfs_n[i] == 0)dfs(i);
        }

        for (int i = 1; i <= n; i++) {
            if (comp_root[comp[i]] == comp_root[comp[get_not(i)]]) {
                return false;
            }
        }
        for (int i = 1; i <= comps.size(); i++) {
            if (comp_value[i] == -1) {
                comp_value[i] = 1;
                int not_ithcomp = comp[get_not(comp_root[i])];
                comp_value[not_ithcomp] = 0;
            }
        }
        for (int i = 1; i <= 2 * n; i++) {
            assigned_val[i] = comp_value[comp[i]];

        }
        return 1;
    }
};
