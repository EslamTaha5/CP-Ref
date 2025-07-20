mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int base, inv1, inv2, MOD1, MOD2;

vector<pair<int, int> > pw{{1, 1}}, invpw{{1, 1}};

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

int add(int a, int b, int MOD) {
    return (a + b) % MOD;
}


int sub(int a, int b, int MOD) {
    return ((a - b) % MOD + MOD) % MOD;
}


int mul(int a, int b, int MOD) {
    return 1ll * a * b % MOD;
}

pair<int, int> operator+(pair<int, int> &a, pair<int, int> &b) {
    return make_pair(add(a.first, b.first, MOD1),
                     add(a.second, b.second, MOD2));
}

pair<int, int> operator-(pair<int, int> &a, pair<int, int> &b) {
    return make_pair(sub(a.first, b.first, MOD1), sub(a.second, b.second, MOD2));
}

pair<int, int> operator/(pair<int, int> &a, int x) {
    int left = mul(a.first, invpw[x].first, MOD1);
    int right = mul(a.second, invpw[x].second, MOD2);
    return make_pair(left, right);
}

pair<int, int> operator*(pair<int, int> &a, int x) {
    int left = mul(a.first, pw[x].first, MOD1);
    int right = mul(a.second, pw[x].second, MOD2);
    return make_pair(left, right);
}

void init() {
    MOD1 = 1e9 + 7;
    MOD2 = 1e9 + 9;
    base = rand(257, 10007);
    inv1 = power(base, MOD1 - 2, MOD1);
    inv2 = power(base, MOD2 - 2, MOD2);

    for (int i = 0; i < M; i++) {
        pw.push_back({
            (pw.back().first * base) % MOD1,
            (pw.back().second * base) % MOD2
        });
        invpw.push_back({
            (invpw.back().first * inv1) % MOD1,
            (invpw.back().second * inv2) % MOD2
        });
    }
}

class TwoDHash {
public:
    vector<vector<pair<int, int> > > pref;


    TwoDHash(vector<string> &v) {
        int n = v.size();
        int m = v[0].size();
        pref = vector<vector<pair<int, int> > >(n + 1, vector<pair<int, int> >(m + 1));
        cout << n << " " << m << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pref[i][j] = make_pair(v[i - 1][j - 1],
                                       v[i - 1][j - 1]);
                pref[i][j] = pref[i][j] * i;
                pref[i][j] = pref[i][j] * j;

                pref[i][j] = pref[i][j] + pref[i - 1][j];
                pref[i][j] = pref[i][j] + pref[i][j - 1];
                pref[i][j] = pref[i][j] - pref[i - 1][j - 1];
            }
        }
    }

    pair<int, int> get(int x1, int y1, int x2, int y2) {
        // one-based
        pair<int, int> lower_right = pref[x2][y2];

        pair<int, int> upper_left = pref[x1 - 1][y1 - 1];

        pair<int, int> upper_right = pref[x1 - 1][y2];

        pair<int, int> lower_left = pref[x2][y1 - 1];

        lower_right = lower_right - upper_left;
        lower_right = lower_right - lower_left;
        lower_right = lower_right + upper_right;
        lower_right = lower_right / x1;
        lower_right = lower_right / y1;

        return lower_right;
    }
};

