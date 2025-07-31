int lp[N + 1];
vector<int> pr;

void linear_seive() {
    for
    (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int) pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}
====================
const int siz = 100000000;
int Ktos[210], stoK[48];
ll isComposite[(siz + 209) / 210];
//bool isComposite[siz];
int nums[] = {2, 3, 5, 7};
void init() {
    memset(Ktos, -1, sizeof Ktos);
    int j = 0;
    for (int i = 0; i < 210; i ++) {
        for (auto p : nums) {
            if (i % p == 0)
                goto nxt;
        }
        Ktos[i] = j;
        stoK[j ++] = i;
        nxt:;
    }
}
void sieve_el_fashee5() {
    isComposite[0] = 1;
    // ba2fesh el start bta3 kol block with size 210
    for (int i = 0; !i || i <= siz / i; i += 210) {
        for (int j = 0; j < 48; j ++) {
            if (!((isComposite[i / 210] >> j) & 1)) {
                int k = i + stoK[j];
                for (int l = k * k; l < siz; l += k) {
                    int x = Ktos[l % 210];
                    if (x == -1)
                        continue;
                    isComposite[l / 210] |= (1LL << x);
                }
            }
        }
    }
}
===============================
bool segp[M];
int n;
bool np[M];
bool segprimes[1000005];
void sieve() {
    int d = 1, s = M;
    np[0] = np[1] = 1;

    for (ll i = 2; i < s; i += d, d = 2) {
        if (!np[i]) {
            for (ll j = i * i; j < s; j += i)
                np[j] = 1;
        }
    }
}
ll a, b;
int c1, c2, d1, d2;
void seg_sieve() {
    memset (segprimes, 0, sizeof segprimes);
    for (ll p = 2; p <= sqrt(b) + 1; p++) {
        if (!np[p]) {
            ll st = (a + p - 1) / p;
            st *= p;
            if (p > a)
                st = p;
            for (ll i = st == p ? st + p : st; i <= b; i += p)
                segprimes[i - a] = 1;
        }
    }
    if (a == 0)
        segprimes[0] = segprimes[1] = 1;
    if (a == 1)
        segprimes[0] = 1;
    int prv = -1, mx = 0, mn = LLONG_MAX;
    for (ll i = a; i <= b; i++) {
        if (!segprimes[i - a]) {
            if (prv == -1) {
                prv = i;
                continue;
            }
            if (i - prv > mx)
                mx = i - prv, c1 = i, c2 = prv;
            if (i - prv < mn)
                mn = i - prv, d1 = i, d2 = prv;
            prv = i;
        }
    }
}


==========================
int phi[N], mobius[N];
bitset<N> isPrime;

void init() {
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (int i = 1; i < N; i++) {
        phi[i] = 1;
        mobius[i] = 1;
    }
    int val = 1;
    for (int i = 2; i < N; i++) {
        if (!isPrime[i]) continue;
        for (int j = i; j < N; j += i) {
            int tmp = j;
            val = 1;
            while (tmp % i == 0) {
                tmp /= i;
                val *= i;
            }
            val /= i;
            val *= (i - 1);
            phi[j] *= val;
            if (i != j) isPrime[j] = false;
            if (j % (i * i) == 0) {
                mobius[j] = 0;
            }
            mobius[j] *= -1;
        }
    }
}
