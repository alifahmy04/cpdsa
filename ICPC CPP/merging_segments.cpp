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

    state() : len(0), link(0), lastString(-1), count(0) {}
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
        addToCount(cur);
    }
 
    int containsSubstring(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!states[cur].next.count(s[i])) {
                return false;
            }
            cur = states[cur].next[s[i]];
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
            while (v && !states[v].next.count(s[i])) {
                v = states[v].link;
                l = states[v].len;
            }
            if (states[v].next.count(s[i]) && states[states[v].next[s[i]]].count == n) {
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

    void exploreLengths(vector<vector<int>>& ans, vector<int>& ans2) {
        for (int i = 1; i < size; i++) {
            int minLength = states[states[i].link].len + 1;
            int maxLength = states[i].len;
            ans[states[i].count - 1][minLength - 1]++;
            ans[states[i].count - 1][maxLength]--;
        }
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[i].size(); j++) {
                if (j > 0) {
                    ans[i][j] += ans[i][j - 1]; 
                }
                ans2[i] += (ans[i][j] > 0);
            }
        }
    }  
};

int getUniqueCount(vector<pair<int, int>>& segments) {
    int lastEndPoint = -1;
    int uniqueCount = 0;
    for (int i = 0; i < segments.size(); i++) {
        int start = max(lastEndPoint + 1, segments[i].first);
        uniqueCount += max(0, segments[i].second - start + 1);
        lastEndPoint = max(lastEndPoint, segments[i].second);
    }
    return uniqueCount;
}

int getUniqueCount2(vector<pair<int, int>>& intervals) {
    int curL = intervals[0].first;
    int curR = intervals[0].second;
    long long total = 0;
    for (size_t j = 1; j < intervals.size(); j++){
        int L = intervals[j].first, R = intervals[j].second;
        if(L <= curR + 1){
            curR = max(curR, R);
        } else {
            total += (curR - curL + 1);
            curL = L; 
            curR = R;
        }
    }
    total += (curR - curL + 1);
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        segments[i] = make_pair(l, r);
    }
    cout << getUniqueCount(segments) << nl;
    cout << getUniqueCount2(segments) << nl;
}