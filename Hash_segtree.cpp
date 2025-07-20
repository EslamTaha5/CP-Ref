mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int base, inv1, inv2, MOD1, MOD2, n;
vector<pair<int, int> > pw{{1, 1}}, invpw{{1, 1}};

int fix(long long x, int M) {
    return (x % M + M) % M;
}


static int add(int a, int b, int MOD) {
    return (a + b) % MOD;
}


static int sub(int a, int b, int MOD) {
    return ((a - b) % MOD + MOD) % MOD;
}


static int mul(int a, int b, int MOD) {
    return 1ll * a * b % MOD;
}

int power(int a, int p, int MD) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (res * a) % MD;
        }
        a = (a * a) % MD;
        p >>= 1;
    }
    return res;
}

void init() {
    MOD1 = 1e9 + 7;
    MOD2 = 1e9 + 9;
    base = rand(257, 10007);
    n = N;
    inv1 = power(base, MOD1 - 2, MOD1);
    inv2 = power(base, MOD2 - 2, MOD2);
    for (int i = 0; i < n; i++) {
        pw.push_back({
            mul(pw.back().first, base, MOD1),
            mul(pw.back().second, base, MOD2)
        });
        invpw.push_back({
            mul(invpw.back().first, inv1, MOD1),
            mul(invpw.back().second, inv2, MOD2)
        });
    }
}

class SegTree {
public:
    class Node {
    public:
        int len, h1, h2;

        Node() {
            len = h1 = h2 = 0;
        }

        Node(int len, int h1,int h2): len(len), h1(h1), h2(h2) {
        }
        bool operator==(const Node &other) const {
            return h1 == other.h1 && h2 == other.h2;
        }
        friend ostream &operator<<(ostream& out, Node nd) {
            out << nd.len <<" " << nd.h1 << " " << nd.h2;
        }
    };
    vector<Node> seg;

    SegTree(int n, string &s) {
        seg = vector<Node>(n * 4);
        build(1, 1, n, s);
    }

    pair<int, int> emp = {0, 0};

    Node combine(Node &l, Node&r) {
        if (!l.len) return r;
        if (!r.len) return l;

        Node par;
        par.len = l.len + r.len;
        par.h1 = (r.h1 * pw[l.len].first % MOD1 + l.h1) % MOD1;
        par.h2 = (r.h2 * pw[l.len].second % MOD2 + l.h2) % MOD2;
        return par;
    }

    void build(int i, int l, int r, string &s) {
        if (l == r) {
            seg[i] = {1, s[l], s[l]};
            return;
        }
        int mid = l + r >> 1;
        build(i * 2, l, mid, s);
        build(i * 2 + 1, mid + 1, r, s);
        seg[i] = combine(seg[i * 2], seg[i * 2 + 1]);
    }

    void update(int i, int l, int r, int idx, char c) {
        if (l > idx || r < idx) return;
        if (l == idx && r == idx) {
            seg[i] = {1, c, c};
            return;
        }
        int mid = l + r >> 1;
        update(i * 2, l, mid, idx, c);
        update(i * 2 + 1, mid + 1, r, idx, c);
        seg[i] = combine(seg[i * 2], seg[i * 2 + 1]);
    }

    Node query(int i, int l, int r, int s, int e) {
        if (l > e || r < s) return {0, 0, 0};
        if (l >= s && r <= e) return seg[i];
        int mid = l + r >> 1;
        auto p1 = query(i * 2, l, mid, s, e);
        auto p2 = query(i * 2 + 1, mid + 1, r, s, e);
        return combine(p1, p2);
    }
};
