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

vector<vector<int>> kmp(string& s) {
    vector<int> pi(s.size());
    for (int i = 1; i < s.size(); i++) {
        int parent = pi[i - 1];
        while (parent > 0 && s[parent] != s[i]) {
            parent = pi[parent - 1];
        }
        if (s[parent] == s[i]) {
            pi[i] = parent + 1;
        } else {
            pi[i] = 0;
        }
        for (int i : pi) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    vector<vector<int>> dp(s.size(), vector<int>(26));
    int n = s.size();
    dp[0][s[0] - 'a'] = 1;
    for (int i = 1; i < n; i++) {
        
    }
}

/*
int kmp_traverse(int i, const vector<int> &pi, char c, const string &s) {
    int j = i;
    while (j > 0 && s[j] != c)
        j = pi[j - 1];
    if (s[j] == c)
        j++;
    return j;
}

*/
/*
    vector<int> pi(pattern.size());
    for (int i = 1; i < pattern.size(); i++) {
        int parent = pi[i - 1];
        while (parent > 0 && pattern[parent] != pattern[i]) {
            parent = pi[parent - 1];
        }
        if (pattern[parent] == pattern[i]) {
            pi[i] = parent + 1;
        } else {
            pi[i] = 0;
        }
        for (int i : pi) {
            cout << i << ' ';
        }
        cout << '\n';
    }
*/

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
} 
