#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

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

struct state {
    int len, link;
    int next[26];
    int lastString;
    int count;
    vector<vector<int>> end;

    state() : len(0), link(0), lastString(-1), count(0), end() {
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
        string temp = s + ".";
        int n = s.size();
        last = 0;
        for (int i = 0; i < n; i++) {
            extend(s[i], i);
        }
        stringCount++;
    }
    
    void addToCount(int node, int i) {
        while (node != 0) {
            int lastString = states[node].lastString;
            if (lastString != stringCount) {
                states[node].end.emplace_back(vector<int>());
            }
            states[node].end[states[node].end.size() - 1].push_back(i);
            states[node].count++;
            states[node].lastString = stringCount;
            node = states[node].link;
        }
    }
 
    // void propagate() {
    //     queue<int> q;
    //     stack<int> reverse;
    //     q.push(0);
    //     while (!q.empty()) {
    //         int current = q.front(); q.pop();
    //         if (current != 0) {
    //             reverse.push(current);
    //         }
    //         for (int i = 0; i < 26; i++) {
    //             if (states[current].next[i] && states[current].len == states[states[current].next[i]].len - 1) {     
    //                 q.push(states[current].next[i]);
    //             }
    //         }
    //     } 
    //     cout << "done\n";
    //     while (!reverse.empty()) {
    //         int current = reverse.top(); reverse.pop();
    //         if (states[current].link == 0) {
    //             continue;
    //         }
    //         for (int i = 0; i < states[current].end.size(); i++) {
    //             for (int x : states[current].end[i]) {
    //                 while (states[states[current].link].end.size() <= i) {
    //                     states[states[current].link].end.emplace_back(vector<int>());
    //                 }
    //                 states[states[current].link].end[i].push_back(x);
    //                 states[states[current].link].count++;
    //             }
    //         }
    //     }
    // }

    void extend(char c, int i) {
        c -= 'a';
        if (states[last].next[c] != 0 && states[states[last].next[c]].len == states[last].len + 1) {
            last = states[last].next[c];
            addToCount(last, i);
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
            addToCount(cur, i);
            return;
        }
        int q = states[p].next[c];
        if (states[q].len == states[p].len + 1) {
            states[cur].link = q;
            addToCount(cur, i);
            return;
        }
        int clone = p == oldLast ? cur : size++;
        if (clone != cur) {
            states.emplace_back(state());
        }
        states[clone].link = states[q].link;
        states[clone].lastString = states[q].lastString;
        states[clone].end = states[q].end;
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
        addToCount(cur, i);
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        suffix_automaton a;
        string s;
        int n;
        cin >> n >> s;
        a.build(s);
        int maxLen = 0;
        for (int i = 0; i < a.states.size(); i++) {
            if (a.states[i].count >= 3) {
                int len = a.states[i].len;
                vector<int>& endPosList = a.states[i].end[0];
                int last = endPosList.size() - 1;
                if (endPosList[last] - len <= endPosList[0]) {
                    continue;
                }
                int limit = lower_bound(endPosList.begin(), endPosList.end(), endPosList[last] - len) - endPosList.begin() - 1;
                if (limit <= 0) {
                    continue;
                }
                // cout << endPosList[0] << ' ' << endPosList[limit] << ' ' << endPosList[last] << '\n';
                int l = endPosList[0] - (endPosList[limit] - len);
                if (l == 0) {
                    l++;
                }
                if (l == len) {
                    continue;
                }
                l = max(0, l);
                int aceStringLen = endPosList[endPosList.size() - 1] - (endPosList[0] - len) - l;
                maxLen = max(aceStringLen, maxLen);
                // cout << aceStringLen << ' ' << s.substr(endPosList[0] - len + l + 1, aceStringLen) << '\n';
            }
        }
        cout << maxLen << '\n';
    }
}