vector<int> insk, low, idx, ans;
int id, n, m, cnt;
vector<vector<int> > adj, scc;
stack<int> sk;
set<pair<int, int> > bridge;
void tarjan_dfs(int i) {
    low[i] = idx[i] = ++id;
    insk[i] = 1;
    sk.push(i);
    for (auto &it: adj[i]) {
        if (!idx[it]) {
            tarjan_dfs(it);
            low[i] = min(low[i], low[it]);
            if (low[it] > idx[i]) {
                bridge.insert({it, i});
            }
        } else if (insk[it]) low[i] = min(low[i], idx[it]);
    }
    if (low[i] == idx[i]) {
        cnt++;
        scc.push_back(vector<int>());
        while (1) {
            int x = sk.top();
            ans[x] = cnt;
            sk.pop();
            scc.back().push_back(x);
            insk[x] = 0;
            if (x == i) break;
        }
    }
}


void tarjan(int i) {
    low = idx = insk = ans = vector<int>(n + 2);
    tarjan_dfs(i);
}