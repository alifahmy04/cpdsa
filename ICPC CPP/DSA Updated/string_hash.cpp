#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
using namespace std;

ll compute_hash(string const& s, const int P, const int MOD) {
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % MOD;
        p_pow = (p_pow * P) % MOD;
    }
    return hash_value;
}

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int mod_inverse(int a, const int MOD) {
    int x, y;
    int g = gcd(a, MOD, x, y);
    x = (x % MOD + MOD) % MOD;
    return x;
}

struct string_hash {
    const int P[3] = {31, 33, 53};
    const int MOD[3] = {(int) 1e9 + 7, (int) 1e9 + 9, (int) 1e9 + 39};
    int inv[3];
    ll pow[3] = {1, 1, 1};
    ll hash_values[3] = {0, 0, 0};

    string_hash() {
        for (int i = 0; i < 3; i++) {
            inv[i] = mod_inverse(P[i], MOD[i]);
        }
    }

    bool operator==(const string_hash& h) const {
        return hash_values[0] == h.hash_values[0] && hash_values[1] == h.hash_values[1] && hash_values[2] == h.hash_values[2];
    }

    void removeFirst(char c) {
        for (int i = 0; i < 3; i++) {
            hash_values[i] = (((hash_values[i] - (c - 'a' + 1) * pow[i]) % MOD[i]) + MOD[i]) % MOD[i];
            pow[i] = pow[i] * inv[i] % MOD[i];
        }
    }

    void removeLast(char c) {
        for (int i = 0; i < 3; i++) {
            hash_values[i] = (((hash_values[i] - (c - 'a' + 1)) % MOD[i]) + MOD[i]) % MOD[i];
            hash_values[i] = hash_values[i] * inv[i] % MOD[i];
            pow[i] = pow[i] * inv[i] % MOD[i];
        }
    }

    void addFirst(char c) {
        for (int i = 0; i < 3; i++) {
            pow[i] = pow[i] * P[i] % MOD[i];
            hash_values[i] = (hash_values[i] + (c - 'a' + 1) * pow[i]) % MOD[i];
        }
    }

    void addLast(char c) {
        for (int i = 0; i < 3; i++) {
            pow[i] = pow[i] * P[i] % MOD[i];
            hash_values[i] = (hash_values[i] * P[i] % MOD[i] + (c - 'a' + 1) * P[i]) % MOD[i];
        }
    }   

    void clear() {
        for (int i = 0; i < 3; i++) {
            hash_values[i] = 0;
            pow[i] = 1;
        }
    }
};

bool rabin_karp(string& s, const string_hash& sh, int len, int& l, int& r) {
    string_hash sh2;
    for (int i = 0; i < len; i++) {
        sh2.addLast(s[i]);
    }
    if (sh == sh2) {
        l = 0;
        r = len;
        return true;
    }
    for (int i = len; i < (int)s.size(); i++) {
        sh2.addLast(s[i]);
        sh2.removeFirst(s[i - len]);
        if (sh == sh2) {
            l = i - len + 1;
            r = i + 1;
            return true;
        }
    }
    return false;
}