#include <bits/stdc++.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <utility>
#include <fstream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#define nl '\n'
//#define int long long
const long double PI = acosl(-1);

//#define double
using namespace __gnu_pbds;

typedef long double ld;

int pow (int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}


void solve(int n, int &x, int &y, int &z) {
    if (n % 3 == 0) {
        x = y = z = n / 3;
    } else if (n % 2 == 0) {
        int m = n / 2;
        int a, b, c;
        solve(m, a, b, c);
        x = a * 2;
        y = b * 2;
        z = c * 2;
    } else {
        x = 1;
        y = (n - 1) / 2;
        z = (n - 1) / 2;
    }
}

signed main() {
    // unless you include these
    // unordered_map<int,int>map;
    // map.reserve(1024);
    // map.max_load_factor(0.25);
    //freopen("flags.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcases = 1;
    cin >> testcases;
    while (testcases--) {
        int n;
        cin >> n;
        int best = 0;
        int a,b,c;
        a = b = 0;
        for (int i = 1; i * i <= n; i++) {
            if (n%i == 0) {
                int x = i;
                int y = x;
                int z = n-2*x;
                if (z > 0) {
                    int v = gcd(x,y) + gcd(y,z) + gcd(x,z);
                    if (v > best) {
                        best = v;
                        a = min(x,z);
                        b = max(x,z);
                    }
                }
                y = (n-x)/2;
                z = (n-x)/2;
                if (z > 0) {
                    int v = gcd(x,y) + gcd(y,z) + gcd(x,z);
                    if (v > best) {
                        best = v;
                        a = min(x,z);
                        b = max(x,z);
                    }
                }

                x = n/i;
                y = x;
                z = n-2*x;
                if (z > 0) {
                    int v = gcd(x,y) + gcd(y,z) + gcd(x,z);
                    if (v > best) {
                        best = v;
                        a = min(x,z);
                        b = max(x,z);
                    }
                }

                y = (n-x)/2;
                z = (n-x)/2;
                if (z > 0) {
                    int v = gcd(x,y) + gcd(y,z) + gcd(x,z);
                    if (v > best) {
                        best = v;
                        a = min(x,z);
                        b = max(x,z);
                    }
                }
            }
        }
        if (a + 2*b == n)
            cout << a << " " << b << " " << b;
        else
            cout << a << " " << a << " " << b;

        int x, y, z;
        solve(n, x, y, z);
        cout << n << ": " << x << " " << y << " " << z << "\n";
        int a2 = min({x, y, z});
        int b2 = max({x, y, z});
        if (a != b) {
            
        }
        cout << nl;
    }
}