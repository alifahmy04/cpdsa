#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

struct state {
    int len, link;
    map<char, int> next;

    state() : len(0), link(0) {}
};

class suffix_automaton {
public:
    vector<state> states;
    int size;
    int last;

    suffix_automaton(const string& s) : size(1), last(0), states(2 * s.size()) {
        states[0].link = -1;
        build(s);
    }

    void build(const string& s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            extend(s[i]);
        }
    }

    void extend(char c) {
        int cur = size++;
        states[cur].len = states[last].len + 1;
        int p = last;
        while (p != -1 && !states[p].next.count(c)) {
            states[p].next[c] = cur;
            p = states[p].link;
        }
        last = cur;
        if (p == -1) {
            return;
        }
        int q = states[p].next[c];
        if (states[q].len == states[p].len + 1) {
            states[cur].link = q;
            return;
        }
        int clone = size++;
        states[clone] = states[q];
        states[clone].len = states[p].len + 1;
        while (p != -1 && states[p].next[c] == q) {
            states[p].next[c] = clone;
            p = states[p].link;
        } 
        states[q].link = clone;
        states[cur].link = clone;
    }

    bool containsSubstring(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!states[cur].next.count(s[i])) {
                return false;
            }
            cur = states[cur].next[s[i]];
        }
        return true;
    }

    long long get_diff_strings() {
        long long tot = 0;
        for(int i = 1; i < size; i++) {
            tot += states[i].len - states[states[i].link].len;
        }
        return tot;
    }

    void distinctSubstringLength(vector<int>& ans) {
        for (int i = 1; i < size; i++) {
            int minLength = states[states[i].link].len + 1;
            int maxLength = states[i].len;
            ans[minLength - 1]++;
            ans[maxLength]--;
        }
        for (int i = 1; i < ans.size(); i++) {
            ans[i] += ans[i - 1];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string s;
    cin >> s;
    suffix_automaton sa(s);
    vector<int> ans(s.size() + 1);
    sa.distinctSubstringLength(ans);
    for (int i = 0; i < s.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << nl;
}