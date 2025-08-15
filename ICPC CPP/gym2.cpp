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

unordered_map<int, int> saved;

int get_value(int x, int y) {
    int key = (x << 16) | y;
    if (saved.count(key)) {
        return saved[key];
    }
    int val;
    cout << "? " << x << ' ' << y << endl;
    cin >> val;
    saved[key] = val;
    return val;
}

int dfs(int x, int y, int ly, int ry, int n) {
    if (y < ly || y > ry) {
        return -1;
    }
    int max_val = get_value(x, y);
    int left = -1;
    if (x - 1 >= 1) {
        left = get_value(x - 1, y);
    }
    int right = -1;
    if (x + 1 <= n) {
        right = get_value(x + 1, y);
    }
    int down = -1;
    if (y - 1 >= ly) {
        down = get_value(x, y - 1);
    }
    int up = -1;
    if (y + 1 <= ry) {
        up = get_value(x, y + 1);
    }    
    if (left > max_val) {
        max_val = max(dfs(x - 1, y, ly, ry, n), max_val);
    }
    if (right > max_val) {
        max_val = max(dfs(x + 1, y, ly, ry, n), max_val);
    }
    if (up > max_val) {
        max_val = max(dfs(x, y + 1, ly, ry, n), max_val);
    }
    if (down > max_val) {
        max_val = max(dfs(x, y - 1, ly, ry, n), max_val);
    }
    return max_val;
}  

signed main() {
    // map.max_load_factor(0.25);
    //freopen("cross.in", "r", stdin);
    // freopen("calc.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int ly = 1, ry = n;
    int c = 0;
    int half_y;
    int next;
    pair<int, int> horizontal;
    while (c < 10) {
        half_y = (ry + ly) >> 1;
        horizontal = {0, 0};
        for (int i = 1; i <= n; i++) {
            int x = get_value(i, half_y);
            if (x > horizontal.first) {
                horizontal.first = x;
                horizontal.second = i;
            }
        }
        int px1 = -1;
        // horz.sec, half
        if (ly == ry) {
            cout << "! " << horizontal.first << endl;
            exit(0);
        }
        if (half_y + 1 <= n) {
            px1 = get_value(horizontal.second, half_y + 1);
        }
        int px2 = -1;
        if (half_y - 1 > 0) {
            px2 = get_value(horizontal.second, half_y - 1);
        }
        int mx_x = max(px1, px2);
        if (horizontal.first > mx_x) {
            cout << "! " << horizontal.first << endl;
            exit(0);
        }
        if (mx_x == px1) {
            ly = half_y + 1;
            next = ly;
        } else {
            ry = half_y - 1;
            next = ry;
        }
        c++;
    }
    int ans = dfs(horizontal.second, next, ly, ry, n);
    cout << "! " << ans << endl;
}

/*
4 fixed
1 2 3 4
8 14 16 9
6 11 15 13
5 10 12 7
*/