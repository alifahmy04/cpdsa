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

pair<int, int> range_binary_search(vector<int>& nums, int x) {
    int l = 0, r = nums.size() - 1, m;
    pair<int, int> result;
    while (l <= r) {
        m = (l + r) >> 1;
        if (nums[m] == x && (m == 0 || nums[m - 1] != x)) {
            result.first = m;
            break;
        } else if (nums[m] >= x) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    if (l == nums.size() || (l > r && nums[l] != x)) {
        result.first = -1;
        result.second = -1;
        return result;
    }
    l = 0, r = nums.size() - 1;
    while (l <= r) {
        m = (l + r) >> 1;
        if (nums[m] == x && (m == nums.size() - 1 || nums[m + 1] != x)) {
            result.second = m;
            break;
        } else if (nums[m] > x) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return result;
}

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

int substring_count(string& s1, string& s2, vector<int>& sa) {
    if (s2.size() < s1.size()) {
        return 0;
    }
    int result_start = 0, result_end = s2.size() - 1;
    for (int i = 0; i < s1.size(); i++) {
        int l = result_start, r = result_end, m;
        int start = lower_bound(sa.begin() + l, sa.begin() + r, s1[i], [&](int idx, char b) {
            return idx + i >= s2.size() || s2[idx + i] < s1[i];
        }) - sa.begin();
        l = start;
        if (l > result_end || (s2[sa[l]] + i) != s1[i]) {
            return 0;
        }
        int end = upper_bound(sa.begin() + l, sa.begin() + r, s1[i], [&](int idx, char b) {
            return idx + i >= s2.size() || s2[idx + i] < s1[i];
        }) - sa.begin() - 1;
    }
    return result_end - result_start + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string s;
    cin >> s;
    vector<int> sa;
    calc(s, sa);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string pattern;
        cin >> pattern;
        cout << substring_count(pattern, s, sa) << nl;
    }
} 
