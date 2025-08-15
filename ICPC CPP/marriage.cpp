#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define ll long long
using namespace std;

struct triple {
    int x;
    int y;
    int z;

    triple() {};
    triple(int x, int y, int z) : x(x), y(y), z(z) {};
};

std::ostream &operator<<(std::ostream &s, const pair<int, int> &t) {
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

std::ostream &operator<<(std::ostream &s, const triple &t) {
    s << "(" << t.x << ", " << t.y << ", " << t.z << ")";
    return s;
}

template <typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &t) {
    int last = t.size() - 1;
    s << "[";
    for (int i = 0; i < t.size(); i++)
    {
        s << t[i];
        if (i != last)
        {
            s << ", ";
        }
    }
    return s << "]";
}

template <typename T, typename K>
std::ostream &operator<<(std::ostream &s, const pair<T, K> &t) {
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

string arrToString(int *arr, int size) {
    std::ostringstream result;
    result << "[";
    for (int i = 0; i < size; ++i)
    {
        result << arr[i];
        if (i != size - 1)
        {
            result << ", ";
        }
    }
    result << "]";
    return result.str();
}

int gcd(int a, int b) {
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> boys(n);
        vector<int> girls(n);
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            cin >> boys[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> girls[i];
            diff[i] = boys[i] - girls[i];
        }

        vector<int> boys_sum(n + 1);
        vector<int> girls_sum(n + 1);
        vector<int> diff_sum(n + 1);
        for (int i = 1; i <= n; i++) {
            boys_sum[i] = boys_sum[i - 1] + boys[i - 1];
            girls_sum[i] = girls_sum[i - 1] + girls[i - 1];
            diff_sum[i] = boys_sum[i] - girls_sum[i];
        }
        cout << boys << nl;
        cout << girls << nl;
        cout << diff << nl;
        
        cout << boys_sum << nl;
        cout << girls_sum << nl;
        cout << diff_sum << nl;
    }
} 
