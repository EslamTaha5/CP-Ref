mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

class SHash {
    int base, inv, MOD, n;
    vector<int> pw{1}, invpw{1}, pref{0};

    SHash() {
    };

    SHash(const string &s, int a, int b) {
        n = s.size();
        base = a;
        inv = 1;
        MOD = b;
        int cur = base, p = MOD - 2;
        while (p) {
            if (p & 1) {
                inv = (inv * cur) % MOD;
            }
            cur = (cur * cur) % MOD;
            p >>= 1;
        }
        for (int i = 0; i < n; i++) {
            pw.push_back(pw.back() * base % MOD);
            invpw.push_back(invpw.back() * inv % MOD);
            pref.push_back((pref.back() + s[i] * pw[i]) % MOD);
        }
    }

    int get(int l, int r) { // one-based
        return ((pref[r + 1] - pref[l]) % MOD + MOD) * invpw[l] % MOD;
    }
};

// Double
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

class DHash {
    static int base, inv1, inv2, MOD1, MOD2;
    int n;
    static vector<pair<int, int> > pw, invpw;
    vector<pair<int, int>> pref{{0, 0}};

public:
    DHash() {
    };
    static int power(int a, int p, int MD) {
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


    static int fix(long long x, int M) {
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
    static void init() {
        pw.push_back({1, 1});
        invpw.push_back({1, 1});
        MOD1 = 1e9 + 7;
        MOD2 = 1e9 + 9;
        base = rand(257, 10007);
        inv1 = power(base, MOD1 - 2, MOD1);
        inv2 = power(base, MOD2 - 2, MOD2);
        for (int i = 0; i < N; i++) {
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
    DHash(const string &s) {

        n = s.size();

        for (int i = 0; i < n; i++) {

            pref.push_back({
                add(pref.back().first, s[i] * pw[i].first, MOD1),
                add(pref.back().second, s[i] * pw[i].second, MOD2)
            });
        }
    }

    pair<int, int> get(int l, int r) {
        // zero-based
        return make_pair(fix(1ll * invpw[l].first * (pref[r + 1].first - pref[l].first), MOD1),
                         fix(1ll * invpw[l].second * (pref[r + 1].second - pref[l].second), MOD2));
    }
};
int DHash::base, DHash::inv1, DHash::inv2, DHash::MOD1, DHash::MOD2;
vector<pair<int, int>> DHash::pw, DHash::invpw;

struct myHash {
    size_t operator()(const pair<ll, ll> &a) const noexcept {
        size_t h1 = hash<ll>{}(a.first);
        size_t h2 = hash<ll>{}(a.second);
        return (h1 ^ (h2 << 1));
    }
};

