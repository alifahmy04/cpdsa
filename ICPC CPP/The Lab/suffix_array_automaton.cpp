#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

struct state {
    int len;
    int link;
    int next[27];
    int distance;
    int count;

    state() : len(0), link(0), distance(0), count(0) {
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
        extend('a' - 1);
        stringCount++;
    }

    void calculateDistance(int node) {
        if (states[node].distance != 0 || node == last) {
            return;
        }
        if (states[node].next[0]) {
            states[node].distance = 1;
        }
        int minDistance = INT_MAX;
        int addedCount = 0;
        for (int i = 0; i < 27; i++) {
            if (states[node].next[i] == 0) {
                continue;
            }
            if (states[states[node].next[i]].distance == 0) {
                calculateDistance(states[node].next[i]);
            }
            states[node].count += states[states[node].next[i]].count;
            minDistance = min(minDistance, states[states[node].next[i]].distance);
        }
        if (states[node].distance == 0) {
            states[node].distance = minDistance + 1;
        }
    }

    void calculateDistances() {
        states[last].count = 1;
        calculateDistance(0);
    }

    void extend(char c) {
        c = c - 'a' + 1;
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
        states[clone].link = states[q].link;
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
    }

    vector<int> constructSuffixArray() {
        vector<int> result;
        suffixArrayDfs(result, 0, 0);
        return result;
    }

    void suffixArrayDfs(vector<int>& result, int node, int depth) {
        if (states[node].count == 1) {
            if (states[node].distance + depth > 1) {
                result.push_back(states[last].len - states[node].distance - depth);
            }
            return;
        }
        for (int i = 0; i < 27; i++) {
            if (states[node].next[i] == 0) {
                continue;
            }
            suffixArrayDfs(result, states[node].next[i], depth + 1);
        }
    }
};

int main() {
    suffix_automaton sa;
    string s;
    cin >> s;
    sa.build(s);
    sa.calculateDistances();
    vector<int> a = sa.constructSuffixArray();
    for (int i : a) {
        cout << i << ' ';
    }
    cout << nl;
}