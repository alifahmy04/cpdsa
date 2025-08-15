#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

struct state {
    int len;
    int link;
    int prefix;
    int dictionaryLink;
    vector<int> stringEnding;
    int lastString;
    int next[26];
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
            for (int i = 0; i < 26; i++) {
                if (states[current].next[i] && states[current].len == states[states[current].next[i]].len - 1) {     
                    q.push(states[current].next[i]);
                }
            }
        }  
    }

    void extend(char c) {
        c -= 'a';
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
    
    vector<pair<int, int>> search(string s) {
        vector<pair<int, int>> result;
        int current = 0;
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            while (current != 0 && (states[current].next[idx] == 0 || states[current].len != states[states[current].next[idx]].len - 1)) {
                current = states[current].link;
            }
            if (states[current].next[idx] != 0 && states[current].len == states[states[current].next[idx]].len - 1) {
                current = states[current].next[idx];
            }
            int temp = current;
            while (temp != 0) {
                for (int x : states[temp].stringEnding) {
                    result.push_back({x, i - states[temp].len - 1});
                }
                temp = states[temp].dictionaryLink;
            }
        }
        return result;
    }
};