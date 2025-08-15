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

void print_pq(priority_queue<int>& pq) {
    vector<int> buffer;
    while (!pq.empty()) {
        cout << pq.top() << ' ';
        buffer.push_back(pq.top());
        pq.pop();
    }
    for (int i : buffer) {
        pq.push(i);
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> matrix(n, vector<int>(m));
        vector<priority_queue<int>> cols(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> matrix[i][j];
                cols[j].push(matrix[i][j]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int current = INT_MIN;
            bool good = true;
            for (int j = 0; j < m; j++) {
                if (cols[j].top() < current) {
                    good = false;
                    cout << "failed";
                    break;
                }
                current = cols[j].top(); cols[j].pop();
                cout << current << ' ';
            }
            cout << nl;
            ans += good;
        }
        cout << ans << nl;
    }
} 
