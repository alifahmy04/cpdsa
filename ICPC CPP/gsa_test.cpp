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

struct state {
    int len, link;
    int next[26];
    int count;

    state() : len(0), link(0), count(0) {
        memset(next, 0, sizeof(next));
    }
};

class suffix_automaton {
public:
    vector<state> states;
    int stringCount;
    int size;
    int last; 
 
    suffix_automaton() : stringCount(0), size(1), last(0), states(1) {
        states[0].link = -1;
    }
 
    void build(const string& s) {
        int n = s.size();
        last = 0;
        for (int i = 0; i < n; i++) {
            extend(s[i]);
        }
        stringCount++;
    }

    void extend(char c) {
        c -= 'a';
        if (states[last].next[c] != 0 && states[states[last].next[c]].len == states[last].len + 1) {
            last = states[last].next[c];
            return;
        }
        int cur = size++;
        states.emplace_back(state());
        states[cur].len = states[last].len + 1;
        int p = last;
        while (p != -1 && states[p].next[c] == 0) {
            states[p].next[c] = cur;
            p = states[p].link;
        }
        int oldLast = last;
        last = cur;
        if (p == -1) {
            return;
        }
        int q = states[p].next[c];
        if (states[q].len == states[p].len + 1) {
            states[cur].link = q;
            return;
        }
        int clone = p == oldLast ? cur : size++;
        if (clone != cur) {
            states.emplace_back(state());
        }
        states[clone] = states[q];
        states[clone].len = states[p].len + 1;
        while (p != -1 && states[p].next[c] == q) {
            states[p].next[c] = clone;
            p = states[p].link;
        } 
        states[q].link = clone;
        if (cur != clone) {
            states[cur].link = clone;
        }
    }
 
    int countSubstring(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            int currentIdx = s[i] - 'a';
            if (!states[cur].next[currentIdx]) {
                return 0;
            }
            cur = states[cur].next[currentIdx];
        }
        return states[cur].count;
    }
 
    long long get_diff_strings() {
        long long tot = 0;
        for(int i = 1; i < size; i++) {
            tot += states[i].len - states[states[i].link].len;
        }
        return tot;
    }

    string lcs(string& s, int n) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < s.size(); i++) {
            int currentIdx = s[i] - 'a';
            while (v && !(states[v].next[currentIdx] != 0 && states[states[v].next[currentIdx]].count >= n)) {
                v = states[v].link;
                l = states[v].len;
            }
            if (states[v].next[currentIdx] != 0 && states[states[v].next[currentIdx]].count >= n) {
                v = states[v].next[currentIdx];
                l++;
            }
            if (l > best && states[v].count == n) {
                best = l;
                bestpos = i;
            }
        }
        return s.substr(bestpos - best + 1, best);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
} 
