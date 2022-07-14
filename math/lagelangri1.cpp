for (int i = 1; i <= n; i++){
    s1 = y[i]%mod; s2 = 1ll;
    for (int j = 1; j <= n; j++)
        if (i != j)
            s1 = s1 * (k - x[j]) % mod, s2 = s2 * ((x[i] - x[j] % mod) % mod) % mod;
    ans += s1 * inv(s2) % mod;
    ans = (ans + mod) % mod;
}