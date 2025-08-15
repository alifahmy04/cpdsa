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
    int len;
    int link;
    int suffix;
    map<int, int> next;
    int count;

    state() : len(0), link(0), suffix(0), count(0), next() {}
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
        states[last].suffix++;
        stringCount++;
    }   
    
    void addToCount(int node) {
        states[node].count++;
    }

    void propagateCounts() {
        vector<int> q(states.size());
        int head = 0, tail = 0;
        q[tail++] = 0;
        while (tail < states.size()) {
            int current = q[head++];
            for (auto& x : states[current].next) {
                if (states[current].len == states[x.second].len - 1) {     
                    q[tail++] = x.second;
                }
            }
        }
        for (int i = states.size() - 1; i > 0; i--) {
            int current = q[i];
            states[states[current].link].count += states[current].count;
            states[states[current].link].suffix += states[current].suffix;
        }
    }   

    void extend(char c) {
        c -= 'a';
        if (states[last].next.count(c) && states[states[last].next[c]].len == states[last].len + 1) {
            last = states[last].next[c];
            addToCount(last);
            return;
        }
        int cur = size++;
        states.emplace_back(state());
        states[cur].len = states[last].len + 1;
        int p = last;
        while (p != -1 && !states[p].next.count(c)) {
            states[p].next[c] = cur;
            p = states[p].link;
        }
        int oldLast = last;
        last = cur;
        if (p == -1) {
            addToCount(cur);
            return;
        }
        int q = states[p].next[c];
        if (states[q].len == states[p].len + 1) {
            states[cur].link = q;
            addToCount(cur);
            return;
        }
        int clone = p == oldLast ? cur : size++;
        if (clone != cur) {
            states.emplace_back(state());
        }
        states[clone].link = states[q].link;
        states[clone].next = states[q].next;
        states[clone].len = states[p].len + 1;
        while (p != -1 && states[p].next[c] == q) {
            states[p].next[c] = clone;
            p = states[p].link;
        } 
        states[q].link = clone;
        if (cur != clone) {
            states[cur].link = clone;
        }
        addToCount(cur);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);

    suffix_automaton sa;
    string s;
    cin >> s;
    sa.build(s);
    sa.propagateCounts();
    int ans = -1;
    int currentNode = 0;
    int maxLen = 0;
    for (int i = 0; i < s.size(); i++) {
        currentNode = sa.states[currentNode].next[s[i] - 'a'];
        if (sa.states[currentNode].suffix && sa.states[currentNode].count > 2 && sa.states[currentNode].len > maxLen) {
            ans = i + 1;
        }
    }
    if (ans == -1) {
        cout << "Just a legend\n";
    } else {
        cout << s.substr(0, ans);
    }
} 
