#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& t) { 
    int last = t.size() - 1;
    s << "[";
    for (int i = 0; i < t.size(); i++) {
        s << t[i];
        if (i != last) {
            s << ", ";
        }
    }
    return s << "]";
}

struct state {
    int len, link;
    map<char, int> next;
    int lastString;
    int count;
    char lastLetter;
    int prev;

    state() : len(0), link(0), lastString(-1), count(0) {}
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
            extend(s[i]);
        }
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

    void extend(char c) {
        if (states[last].next.count(c) && states[states[last].next[c]].len == states[last].len + 1) {
            last = states[last].next[c];
            addToCount(last);
            return;
        }
        int cur = size++;
        states.emplace_back(state());
        states[cur].lastLetter = c;
        states[cur].prev = last;

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
        states[clone] = states[q];
        states[clone].prev = p;
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
            if (!states[cur].next.count(s[i])) {
                return false;
            }
            cur = states[cur].next[s[i]];
        }
        return states[cur].count;
    }

    string getSubstring(int node) {
        stringstream ss;
        while (node != 0) {
            ss << states[node].lastLetter;
            node = states[node].prev;
        }
        string result = ss.str();
        reverse(result.begin(), result.end());
        return result;
    }
 
    long long get_diff_strings() {
        long long tot = 0;
        for(int i = 1; i < size; i++) {
            tot += states[i].len - states[states[i].link].len;
        }
        return tot;
    }

    void printAllCommonSubstrings() {
        for (int i = 1; i < size; i++) {
            if (states[i].count == stringCount) {
                cout << getSubstring(i) << nl;
            }
        }
    }

    string lcs(string& s, int n) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < s.size(); i++) {
            while (v && !(states[v].next.count(s[i]) && states[states[v].next[s[i]]].count >= n)) {
                v = states[v].link;
                l = states[v].len;
            }
            if (states[v].next.count(s[i]) && states[states[v].next[s[i]]].count >= n) {
                v = states[v].next[s[i]];
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

bool isSubstring(const string& mainStr, const string& subStr) {
    return mainStr.find(subStr) != std::string::npos;
}

int findSubstringCount(vector<string>& strings, string s) {
    vector<int> temp;
    int count = 0;
    for (int i = 0; i < strings.size(); i++) {
        string a = strings[i];
        if (isSubstring(a, s)) {
            count++;
            temp.push_back(i);
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    suffix_automaton sa;
    vector<string> strings;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        sa.build(s);
        strings.push_back(s);
    }
    for (int i = 0; i < sa.size; i++) {
        cout << sa.states[i].prev << " ";
    }
    cout << nl;
    sa.printAllCommonSubstrings();
    while (true) {
        int n;
        cin >> n;
        cout << sa.getSubstring(n) << nl;
    }
}