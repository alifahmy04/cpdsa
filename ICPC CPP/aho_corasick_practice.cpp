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
    int prefix;
    int dictionaryLink;
    vector<int> stringEnding;
    int lastString;
    int next[128];
    int count;

    state() : len(0), link(0), prefix(0), dictionaryLink(0), stringEnding(), lastString(-1), count(0) {
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
        states[last].prefix++;
        for (int i = 0; i < n; i++) {
            extend(s[i]);
            states[last].prefix++;
        }
        states[last].stringEnding.push_back(stringCount);
        stringCount++;
    }   
    
    void addToCount(int node) {
        while (node != -1) {
            int lastString = states[node].lastString;
            if (lastString == stringCount) {
                return;
            }
            states[node].count++;
            states[node].lastString = stringCount;
            node = states[node].link;
        }
    }

    void buildDictionaryLinks() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int current = q.front(); q.pop();
            if (current != 0) {
                if (!states[states[current].link].stringEnding.empty()) {
                    states[current].dictionaryLink = states[current].link;
                } else {
                    states[current].dictionaryLink = states[states[current].link].dictionaryLink;
                }
            }
            for (int i = 0; i < 128; i++) {
                if (states[current].next[i] && states[current].len == states[states[current].next[i]].len - 1) {     
                    q.push(states[current].next[i]);
                }
            }
        }  
    }

    void extend(char c) {
        if (states[last].next[c] != 0 && states[states[last].next[c]].len == states[last].len + 1) {
            last = states[last].next[c];
            addToCount(last);
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
        states[clone].lastString = states[q].lastString;
        states[clone].count = states[q].count;
        memcpy(states[clone].next, states[q].next, sizeof(states[q].next));
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
 
    int countSubstring(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            int currentIdx = s[i];
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
            int currentIdx = s[i];
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
    
    vector<vector<int>> search(string& s, vector<string>& patterns) {
        vector<vector<int>> result(stringCount);
        int current = 0;
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i];
            while (current != 0 && (states[current].next[idx] == 0 || states[current].len != states[states[current].next[idx]].len - 1)) {
                current = states[current].link;
            }
            if (states[current].next[idx] != 0 && states[current].len == states[states[current].next[idx]].len - 1) {
                current = states[current].next[idx];
            }
            int temp = current;
            while (temp != 0) {
                for (int x : states[temp].stringEnding) {
                    result[x].push_back(i - patterns[x].size() + 1);
                }
                temp = states[temp].dictionaryLink;
            }
        }
        return result;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == -1) break;
        cin.ignore();
        suffix_automaton ac;
        vector<string> patterns(n);
        for (int i = 0; i < n; ++i) {
            getline(cin, patterns[i]);
            ac.build(patterns[i]);
        }
        ac.buildDictionaryLinks();
        string text;
        getline(cin, text);
        vector<vector<int>> result = ac.search(text, patterns);
        for (vector<int>& v : result) {
            for (int i : v) {
                cout << i << ' ';
            }
            cout << nl;
        }
    }
    return 0;
} 
//