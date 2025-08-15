#include <bits/stdc++.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#define nl '\n'
#define int long long
const long double PI = acosl(-1);
#define cd complex<long double>
#define vi vector<int>

//#define double
using namespace __gnu_pbds;

typedef long double ld;
template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& t) { 
    int last = t.size() - 1;
    s << "[";
    for (int i = 0; i < t.size(); i++) {
        s << t[i];
        if (i != last) {
            s << ", ";
        }
    }
    return s << "]";
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

void printPrimeFact(int d) {
    vector<int> p;
    vector<int> pc;
    bool valid = true;
    for (int i = 2; i <= d; i++) {
        if (d % i == 0 && isPrime(i)) {
            int temp = d;
            int f1 = i;
            if (isPrime(i)) {
                p.push_back(i);
                pc.push_back(0);
                while (temp % f1 == 0 && temp > 1) {
                    temp /= f1;
                    pc[pc.size() - 1]++;
                    if (pc[pc.size() - 1] > 2) {
                    }
                }  
            }
        }
    }
    // cout << p << nl;
    cout << d << " " << p << " " << pc << nl;
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int testcases = 1;
    
    int n = 20;
    
    for (int i = 1; i < n; i++) {
        set<int> factors;
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                factors.insert(j);
                factors.insert(i / j);
            }
        }
        long long p = 1;
        for (int f : factors) {
            // cout << i << ' ';
            p *= f;
        }
        cout << nl;
        cout << i << " ";
        printPrimeFact(p);
    }
}