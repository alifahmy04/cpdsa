#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

struct state {
    int len;
    int link;
    int dictionaryLink;
    vector<int> stringEnding;
    int next[26];
    int count;

    state() : len(0), link(0), dictionaryLink(0), stringEnding(), count(0) {
        memset(next, 0, sizeof(next));
    }
};

class aho_corasick_automaton {
public:
    vector<state> states;
    int stringCount;
    int size;
    int last; 
 
    aho_corasick_automaton() : stringCount(0), size(1), last(0), states(1) {
        states[0].link = -1;
    }
 
    void build(const string& s) {
        int n = s.size();
        last = 0;
        for (int i = 0; i < n; i++) {
            extend(s[i]);
            states[last].count++;
        }
        states[last].stringEnding.push_back(stringCount);
        stringCount++;
    }   

    void buildLinks() {
        queue<int> q;
        states[0].link = 0;
        states[0].dictionaryLink = 0;
        q.push(0);
        while (!q.empty()) {
            int parent = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (states[parent].next[i] == 0) {
                    continue;
                }
                if (parent != 0) {
                    int child = states[parent].next[i];
                    int temp = states[parent].link;
                    while (temp != 0 && states[temp].next[i] == 0) {
                        temp = states[temp].link;
                    }
                    if (states[temp].next[i] != 0) {
                        states[child].link = states[temp].next[i];
                    }
                    if (!states[states[child].link].stringEnding.empty()) {
                        states[child].dictionaryLink = states[child].link;
                    } else {
                        states[child].dictionaryLink = states[states[child].link].dictionaryLink;
                    }
                }
                q.push(states[parent].next[i]);
            }
        }  
    }

    void extend(char c) {
        c -= 'a';
        if (states[last].next[c] != 0) {
            last = states[last].next[c];
            return;
        }
        int cur = size++;
        states.emplace_back(state());
        states[cur].len = states[last].len + 1;
        states[last].next[c] = cur;
        last = cur;
    }
    
    vector<pair<int, int>> search(string& s) {
        vector<pair<int, int>> result;
        int current = 0;
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            while (current != 0 && states[current].next[idx] == 0) {
                current = states[current].link;
            }
            if (states[current].next[idx] != 0) {
                current = states[current].next[idx];
            }
            int temp = current;
            while (temp != 0) {
                for (int x : states[temp].stringEnding) {
                    result.push_back({x, i - states[temp].len + 1});
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
        aho_corasick_automaton ac;
        vector<string> patterns(n);
        for (int i = 0; i < n; ++i) {
            cin >> patterns[i];
            ac.build(patterns[i]);
        }
        ac.buildLinks();
        string text;
        cin >> text;
        vector<pair<int, int>> result = ac.search(text);
        for (pair<int, int>& v : result) {
            cout << "{" << v.first << ", " << v.second << "}" << ' ';
        }
        cout << nl;
    }
    return 0;
} 