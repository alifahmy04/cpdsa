#include <bits/stdc++.h>
#define ll long long
#define nl '\n'

ll binpow(ll a, ll b, const int MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
            res %= MOD;
        a = a % MOD * a % MOD;
        a %= MOD;
        b >>= 1;
    }
    return res % MOD;
}

bool isPrime(int k) {
    if (k == 1) {
        return false;
    }
    for (int i = 2; i * i <= k; i++) {
        if (k % i == 0) {
            return false;
        }
    }
    return true;
}
