struct modint
{
#define CUR (*this)
    static const int MOD = 998244353;
    int val;
    modint(const long long &a = 0)
    {
        val = a % MOD;
        if (val < 0)
            val += MOD;
    }
    modint &operator+=(const modint &a)
    {
        if ((val += a.val) >= MOD)
            val -= MOD;
        return CUR;
    }
    modint operator+(const modint &a) const
    {
        modint c = CUR;
        c += a;
        return c;
    }
    modint &operator-=(const modint &a)
    {
        if ((val -= a.val) < 0)
            val += MOD;
        return CUR;
    }
    modint operator-(const modint &a) const
    {
        modint c = CUR;
        c -= a;
        return c;
    }
    modint operator*(const modint &a) const
    {
        return modint((1LL * this->val * a.val) % MOD);
    }
    modint &operator*=(const modint &a)
    {
        CUR = CUR * a;
        return CUR;
    }
    modint operator/(const modint &a)
    {
        return CUR * power(a, MOD - 2);
    }
    modint &operator/=(const modint &a)
    {
        CUR = CUR / a;
        return CUR;
    }
    static modint power(modint x, long long y)
    {
        modint res = 1;
        while (y > 0)
        {
            if (y & 1)
                res *= x;
            x *= x;
            y >>= 1;
        }
        return res;
    }
    friend ostream &operator<<(ostream &out, const modint &a)
    {
        out << a.val;
        return out;
    }
#undef CUR
};
const int LGN = 22;
const int MOD = 998244353;
typedef valarray<modint> polynomial;
vector<modint> CM1[2][LGN + 1];
bool validRoot(modint root)
{
    modint rootinv = modint(1) / root;
    for (int invert = 0; invert <= 1; invert++)
    {
        for (int i = 1; i <= LGN; i++)
        {
            int N = 1 << i;
            assert((MOD - 1) % N == 0);
            int C = (MOD - 1) / N;
            modint cm2 = modint::power(invert ? root : rootinv, C);
            if (cm2.val <= 1)
                return false;
        }
    }
    return true;
}
 
void prepare()
{
    modint root = 2;
    while (!validRoot(root))
        root += 1;
    modint rootinv = modint(1) / root;
    for (int invert = 0; invert <= 1; invert++)
    {
        for (int i = 0; i <= LGN; i++)
        {
            int N = 1 << i;
            int C = (MOD - 1) / N;
            modint cm2 = modint::power(invert ? root : rootinv, C);
            modint cm1 = 1;
            set<int> st;
            for (int j = 0; j < N / 2; j++)
            {
                CM1[invert][i].push_back(cm1);
                cm1 *= cm2;
            }
        }
    }
}
void fft(polynomial &a, bool invert = 0)
{
    int N = a.size();
    int lgn = log2(N);
    for (int m = N; m >= 2; m >>= 1, lgn--)
    {
        int mh = m >> 1;
        for (int i = 0; i < mh; i++)
        {
            const modint &w = CM1[invert][lgn][i];
            for (int j = i; j < N; j += m)
            {
                int k = j + mh;
                modint x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
    }
    int i = 0;
    for (int j = 1; j < N - 1; j++)
    {
        for (int k = N >> 1; k > (i ^= k); k >>= 1)
            continue;
        if (j < i)
            swap(a[i], a[j]);
    }
}
void inv_fft(polynomial &a)
{
    int N = a.size();
    fft(a, 1);
    a /= N;
}
valarray<modint> mul(const polynomial &a, const polynomial &b)
{
    int adeg = (int)a.size() - 1, bdeg = (int)b.size() - 1;
    int N = 1;
    while (N <= adeg + bdeg)
        N <<= 1;
    polynomial A(N), B(N);
    for (int i = 0; i < a.size(); i++)
        A[i] = a[i];
    for (int i = 0; i < b.size(); i++)
        B[i] = b[i];
    fft(A);
    fft(B);
    polynomial rt = A * B;
    inv_fft(rt);
    int sz = rt.size();
    for(int i = (int)rt.size() - 1; i >= 0; i--){
        if(rt[i].val != 0){
            sz = i + 1;
            break;
        }
    }
    polynomial res(sz);
    for(int i = 0; i < sz; i++)
        res[i] = rt[i];
    return res;
}
 
 
polynomial power(polynomial & a , int n){
    if(n == 1)
        return a;
    
    polynomial res = power(a , n / 2);
    res = mul(res , res);
    if(n & 1)
        res = mul(res, a);
    return res;
}
