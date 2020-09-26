#include <bits/stdc++.h>

#define REP(i, a, b) for (int i = a, i##_end_ = b; i <= i##_end_; ++i)
#define DREP(i, a, b) for (int i = a, i##_end_ = b; i >= i##_end_; --i)
#define debug(x) cout << #x << "=" << x << " "
#define fi first
#define se second
#define mk make_pair
#define pb push_back
typedef long long ll;

using namespace std;

template <typename T>
void read(T &_)
{
    _ = 0;
    T fl = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            fl = -1;
    for (; isdigit(ch); ch = getchar())
        _ = (_ << 1) + (_ << 3) + (ch ^ '0');
    _ *= fl;
}

const int maxn = 1e5 + 10;
const int mod = 998244353;

ll qpow(ll x, ll y)
{
    ll ret = 1;
    x %= mod;
    while (y)
    {
        if (y & 1)
            ret = ret * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ret;
}

struct ksslbh
{
    int lim, cnt, dn[maxn << 2];
    ll g[maxn << 2], ig[maxn << 2];
    void ntt(ll *A, int ty)
    {
        REP(i, 0, lim - 1)
        if (i < dn[i]) swap(A[i], A[dn[i]]);
        for (int len = 1; len < lim; len <<= 1)
        {
            ll w = ty == 1 ? g[len << 1] : ig[len << 1];
            for (int L = 0; L < lim; L += len << 1)
            {
                ll wk = 1;
                REP(i, L, L + len - 1)
                {
                    ll u = A[i], v = A[i + len] * wk % mod;
                    A[i] = (u + v) % mod;
                    A[i + len] = (u - v) % mod;
                    wk = wk * w % mod;
                }
            }
        }
    }
    void work(int n, int m, ll *a, ll *b)
    {
        lim = 1, cnt = 0;
        while (lim <= n + m)
            lim <<= 1, ++cnt;
        if (!cnt)
            cnt = 1;
        REP(i, 0, lim)
        {
            dn[i] = dn[i >> 1] >> 1 | ((i & 1) << (cnt - 1));
            if (i > n)
                a[i] = 0;
            if (i > m)
                b[i] = 0;
        }
        g[lim] = qpow(3, (mod - 1) / lim);
        ig[lim] = qpow(g[lim], mod - 2);
        for (int i = lim >> 1; i; i >>= 1)
        {
            g[i] = g[i << 1] * g[i << 1] % mod;
            ig[i] = ig[i << 1] * ig[i << 1] % mod;
        }
        ntt(a, 1), ntt(b, 1);
        REP(i, 0, lim - 1)
        a[i] = a[i] * b[i] % mod;
        ntt(a, -1);
        ll inv = qpow(lim, mod - 2);
        REP(i, 0, lim - 1)
        a[i] = a[i] * inv % mod;
    }
} T;

int n;
ll f[maxn << 2], g[maxn << 2], a[maxn << 2], b[maxn << 2];

void divide(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    divide(l, mid);
    int nn = mid - l, mm = r - l - 1;
    REP(i, 0, nn)
    a[i] = f[l + i];
    REP(i, 0, mm)
    b[i] = g[i + 1];
    T.work(nn, mm, a, b);
    REP(i, mid + 1, r)
    f[i] = (f[i] + a[i - 1 - l]) % mod;
    divide(mid + 1, r);
}

//know: g[1...n-1],f[0]=1
//question: f[i]=sigma_{j=1,i} f[i-j]*g[j]

int main()
{
    read(n);
    REP(i, 1, n - 1)
    read(g[i]);
    f[0] = 1;
    divide(0, n);
    REP(i, 0, n - 1)
    printf("%lld ", (f[i] + mod) % mod);
    return 0;
}