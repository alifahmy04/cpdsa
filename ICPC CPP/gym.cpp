#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define ll long long
using namespace std;

struct triple {
    int first;
    int second;
    int third;

    triple() {};
    triple(int x, int y, int z) : first(x), second(y), third(z) {};
};

std::ostream &operator<<(std::ostream &s, const pair<int, int> &t) {
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

std::ostream &operator<<(std::ostream &s, const triple &t) {
    s << "(" << t.first << ", " << t.second << ", " << t.third << ")";
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
    // map.max_load_factor(0.25);
    //freopen("cross.in", "r", stdin);
    // freopen("calc.out", "w", stdout);
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    vector<int> color_map(128);
    vector<int> color_counts(4);
    unordered_map<triple, int> segment_hash;
    color_map['r'] = 1; color_map['g'] = 3; color_map['b'] = 5; color_map['w'] = 7;
    for (int i = 0; i < h; i++) {
        string s;
        cin >> s;
        grid[i] = s;
    }

    for (int i = 0; i < h; i++) {

    }


    if (possible) {
        cout << "possible\n";
    } else {
        cout << "impossible\n";
    }
}