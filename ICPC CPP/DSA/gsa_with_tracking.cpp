#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

struct state {
    int len, link;
    map<char, int> next;
    vector<int> sources;

    state() : len(0), link(0) {}
};

class suffix_automaton {
public:
    vector<state> states;
    int stringCount;
    int size;
    int last;
 
    suffix_automaton(const string& s) : stringCount(0), size(1), last(0), states(2 * s.size()) {
        states[0].link = -1;
        build(s);
    }

    suffix_automaton(int capacity) : stringCount(0), size(1), last(0), states(capacity) {
        states[0].link = -1;
    }
 
    void build(const string& s) {
        string temp = s + ".";
        int n = s.size();
        last = 0;
        for (int i = 0; i < n; i++) {
            extend(s[i]);
        }
        stringCount++;
    }
    
    void insertToSources(int node, int stringIdx) {
        while (node != -1) {
            vector<int>& sources = states[node].sources;
            if (sources.size() != 0 && sources[sources.size() - 1] == stringIdx) {
                return;
            }
            sources.push_back(stringIdx);
            node = states[node].link;
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
        insertToSources(cur, stringCount);
        if (p == -1) {
            return;
        }
        int q = states[p].next[c];
        if (states[q].len == states[p].len + 1) {
            states[cur].link = q;
            insertToSources(q, stringCount);
            return;
        }
        int clone = size++;
        states[clone] = states[q];
        states[clone].len = states[p].len + 1;
        while (p != -1 && states[p].next[c] == q) {
            states[p].next[c] = clone;
            p = states[p].link;
        } 
        insertToSources(clone, stringCount);
        states[q].link = clone;
        states[cur].link = clone;
    }
 
    int containsSubstring(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!states[cur].next.count(s[i])) {
                return false;
            }
            cur = states[cur].next[s[i]];
        }
        return states[cur].sources.size();
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
            while (v && !states[v].next.count(s[i])) {
                v = states[v].link;
                l = states[v].len;
            }
            if (states[v].next.count(s[i]) && states[states[v].next[s[i]]].sources.size() == n) {
                v = states[v].next[s[i]];
                l++;
            }
            if (l > best && states[v].sources.size() == n) {
                best = l;
                bestpos = i;
            }
        }
        return s.substr(bestpos - best + 1, best);
    }
};