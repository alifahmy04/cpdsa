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

class union_find {
public:
    vector<int> parent;
    vector<int> rank;
    union_find(int n) : parent(n), rank(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (rank[px] >= rank[py]) {
            parent[py] = px;
        } else {
            parent[px] = py;
        }
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }
};

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
        vector<vector<int>> lcps(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> lcps[i][j];
            }
        }
        union_find groups(2 * n);
        vector<int> string_a(n);
        vector<int> string_b(n);
        for (int i = 0; i < n; i++) {
            string_a[i] = i;
            string_b[i] = i + n;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (lcps[i][j]) {
                    groups.join(string_a[i], string_b[j]);
                }
            }
        }
        unordered_set<int> seen;
        for (int i = 0; i < 2 * n; i++) {
            seen.insert(groups.find(i));
        }
        ll ans = 1;
        int remaining = 26;
        for (int i = 0; i < seen.size(); i++) {
            ans *= remaining--;
            ans %= (int)(1e9+7);
        }
        cout << ans << nl;
    }
} 
