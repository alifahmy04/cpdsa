#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define int long long
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

bool checkExists(int start, int end, vector<int>& letters) {
    for (int i = start; i <= end; i++) {
        if (letters[i]) {
            return true;
        }
    }
    return false;
}

int findEarliestPosition(string& a, string& b, vector<int> b_letters) {
    int bestPos = -1;
    for (int i = 0; i < a.size(); i++) {
        if (b_letters[a[i] - 'a']) {
            if (checkExists(a[i] - 'a' + 1, 25, b_letters)) {
                bestPos = i;
            }
            b_letters[a[i] - 'a']--;
            if (i == a.size() - 1) {
                return a.size();
            }
        } else {
            if (checkExists(a[i] - 'a' + 1, 25, b_letters)) {
                return i;
            }
            return bestPos;
        }
    }
    return bestPos;
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int n;
    cin >> n;
    bool ans = true;
    vector<string> all_strings(n);
    for (int i = 0; i < n; i++) {
        cin >> all_strings[i];
    }
    string& a = all_strings[0];
    stringstream ss_a;
    vector<int> first_letters(26);
    for (int i = 0; i < a.size(); i++) {
        first_letters[a[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        while (first_letters[i]) {
            ss_a << (char)(i + 'a');
            first_letters[i]--;
        }
    }
    all_strings[0] = ss_a.str();
    for (int i = 0; i < n - 1; i++) {
        string& a = all_strings[i];
        string& b = all_strings[i + 1];
        vector<int> b_letters(26);
        for (int i = 0; i < b.size(); i++) {
            b_letters[b[i] - 'a']++;
        }
        int pos = findEarliestPosition(a, b, b_letters);
        if (pos == -1) {
            cout << -1;
            ans = false;
            break;
        }
        stringstream ss;
        for (int i = 0; i < pos; i++) {
            ss << a[i];
            b_letters[a[i] - 'a']--;
        }
        int letter;
        if (pos < a.size()) {
            for (int i = a[pos] - 'a' + 1; i < 26; i++) {
                if (b_letters[i]) {
                    letter = i;
                    break;
                }
            }
            ss << (char)(letter + 'a');
            b_letters[letter]--;
        }
        for (int i = 0; i < 26; i++) {
            while (b_letters[i]) {
                ss << (char)(i + 'a');
                b_letters[i]--;
            }
        }
        all_strings[i + 1] = ss.str();
    }
    if (ans) {
        for (string& s : all_strings) {
            cout << s << nl;
        }
    }
} 
