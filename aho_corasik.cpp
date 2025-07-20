
// link node that has the max matched suffix
// outlink node that has the max matched suffix and (contains a pattern)
// next[i][c] at node i where to fail if we put char c
// out[i][] at node i what indices that i can match

class aho_corasick {
public:
    int MAX, P;
    const int A = 26;
    vector<vector<int> > next, out;
    vector<int> link, outlink;
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        outlink.emplace_back(0);
        out.emplace_back(0);
        return MAX++;
    }

    aho_corasick(): MAX(0), P(0) {
        node();
    }

    static int getchar(char c) {
        return c - 'a';
    }

    void add_pattern(const string &s, int idx) {
        int u = 0;
        for (char c: s) {
            if (!next[u][getchar(c)]) {
                next[u][getchar(c)] = node();
            }
            u = next[u][getchar(c)];
        }
        out[u].emplace_back(idx);
    }

    void calc() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            // v child, u ancestor
            for (int i = 0; i < A; i++) {
                int v = next[u][i];
                if (!v) {
                    next[u][i] = next[link[u]][i];
                } else {
                    link[v] = (u ? next[link[u]][i] : 0);
                    outlink[v] = out[link[v]].empty() ? outlink[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int advance(int u, char c) {
        while (u && !next[u][getchar(c)]) {
            u = link[u];
        }
        u = next[u][getchar(c)];
        return u;
    }
};
