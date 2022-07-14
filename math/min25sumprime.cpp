namespace Min25 {
    const int maxn = 1000010;
    int newN;
    int prime[maxn], totp, tot;
    ll sumprime[maxn];
    int notprime[maxn];
    ll quotient[maxn]; int totq;
    int id1[maxn], id2[maxn];
    ll g[maxn];
    void linear_seive(int n) {
        notprime[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!notprime[i]) {
                prime[++tot] = i;
                sumprime[tot] = sumprime[tot-1] + i;
            }
            for (int j = 1; j <= tot && 
                            i * prime[j] <= n; ++j) {
                notprime[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }
    ll calc(ll x) {
        return x * (x + 1) / 2 - 1;
    }
    int ID(ll n, ll x) {
        return x <= newN ? id1[x] : id2[n / x];
    }
    ll solve(ll n) {
        if (n <= 1) return n;
        newN = sqrt(n + 0.5);
        /*
            This make sure the linear seive be done 
            only once when there're multiple querys.
        */
        if (!tot) linear_seive(sqrt(10000000010));
        totq = 0;
        for (ll l = 1; l <= n; l = n / (n / l) + 1) {
            quotient[++totq] = n / l;
            if (quotient[totq] <= newN) {
                id1[quotient[totq]] = totq;
            } else {
                id2[n / quotient[totq]] = totq;
            }
            g[totq] = calc(quotient[totq]);
        }
        for (int i = 1; i <= tot 
            && 1ll * prime[i] * prime[i] <= n; ++i) {
            for (int j = 1; j <= totq && 
                1ll * prime[i] * prime[i] <= quotient[j]; 
                ++j) {
                g[j] = g[j] - prime[i] * 
                      (g[ID(n, quotient[j] / prime[i])] - 
                       sumprime[i - 1]);
            }
        }
        return g[ID(n, n)];
    }
}

// get sum of prime from 2 to n:
ll sum = Min25::solve(n)