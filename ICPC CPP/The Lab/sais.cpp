#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

void sais_core(int n, int m, const int* s, int* sa, char* type, int* lms, int* cnt) {
    int n1 = 0, ch = -1;
    type[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i)
        type[i] = s[i] == s[i + 1] ? type[i + 1] : s[i] < s[i + 1];
    fill(cnt, cnt + m, 0);
    for (int i = 0; i < n; ++i) ++cnt[s[i]];
    partial_sum(cnt, cnt + m, cnt);
    auto induced_sort = [&](const int v[]) {
        fill(sa, sa + n, 0);
        int *cur = cnt + m;
        auto push_S = [&](const int x) { sa[--cur[s[x]]] = x; };
        auto push_L = [&](const int x) { sa[cur[s[x]]++] = x; };
        copy(cnt, cnt + m, cur);
        for (int i = n1 - 1; i >= 0; --i) push_S(v[i]);
        copy(cnt, cnt + m - 1, cur + 1);
        for (int i = 0; i < n; ++i)
            if (sa[i] > 0 && type[sa[i] - 1] == 0)
                push_L(sa[i] - 1);
        copy(cnt, cnt + m, cur);
        for (int i = n - 1; i >= 0; --i)
            if (sa[i] > 0 && type[sa[i] - 1])
                push_S(sa[i] - 1);
    };
    for (int i = 1; i < n; ++i)
        if (type[i - 1] == 0 && type[i] == 1)
            type[i] = 2, lms[n1++] = i;
    induced_sort(lms);
    auto lms_equal = [&](int x, int y) {
        if (s[x] == s[y])
            while (s[++x] == s[++y] && type[x] == type[y])
                if (type[x] == 2 || type[y] == 2)
                    return true;
        return false;
    };

    int* s1 = remove_if(sa, sa + n, [&](const int x) { return type[x] != 2; });
    for (int i = 0; i < n1; ++i)
        s1[sa[i] >> 1] = ch += ch <= 0 || !lms_equal(sa[i], sa[i - 1]);
    for (int i = 0; i < n1; ++i)
        s1[i] = s1[lms[i] >> 1];

    if (ch + 1 < n1)
        sais_core(n1, ch + 1, s1, sa, type + n, lms + n1, cnt + m);
    else
        for (int i = 0; i < n1; ++i)
            sa[s1[i]] = i;

    for (int i = 0; i < n1; ++i)
        lms[n1 + i] = lms[sa[i]];
    induced_sort(lms + n1);
}

void calc(string& str, vector<int>& sa) {
    vector<int> v(str.size());
    for (int i = 0; i < str.size(); i++) {
        v[i] = str[i] - 'a';
    }
    vector<int> s(v);
    for (int& i : s) i++;
    s.emplace_back(0);
    int n = s.size();
    int m = *max_element(s.begin(), s.end()) + 1;
    vector<int> lms(n), cnt(2 * max(n, m));
    vector<char> type(2 * n);
    sa.resize(n);
    sais_core(n, m, s.data(), sa.data(), type.data(), lms.data(), cnt.data());
    n--;
    for (int i = 0; i < n; i++) {
        sa[i] = sa[i + 1];
    }
    sa.resize(n);
}

void solve() {
    string s;
    cin >> s;
    vector<int> sa;
    calc(s, sa);
    for (int i : sa) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cout.tie(0);

    solve();
}