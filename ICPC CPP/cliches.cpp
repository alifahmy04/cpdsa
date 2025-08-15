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

struct node {
    int val;
    node* left;
    node* right;
    node(int val, node* left = nullptr, node* right = nullptr) : val(val), left(left), right(right) {}
};

class segment_tree {
public: 
    int size = 1;
    int n;
    vector<int> tree;

public:
    segment_tree() {}

    segment_tree(const vector<int>& elements) : n(elements.size()) {
        size = 1 << (int) ceil(log2(elements.size()));
        tree.resize(size << 1);
        for (int i = 0; i < elements.size(); i++) {
            tree[i + size] = elements[i];
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    int operation(int a, int b) {
        return a + b;
    }

    int query(int l, int r) {
        return query(1, l, r, 0, size - 1);
    }

    int query(int currentIndex, int l, int r, int currentl, int currentr) {
        if (currentl >= l && currentr <= r) {
            return tree[currentIndex];
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            return query(currentIndex << 1, l, r, currentl, mid);
        }
        if (mid < l) {
            return query(currentIndex << 1 | 1, l, r, mid + 1, currentr);
        }
        int leftChild = query(currentIndex << 1, l, r, currentl, mid);
        int rightChild = query(currentIndex << 1 | 1, l, r, mid + 1, currentr);
        return operation(leftChild, rightChild);
    }

    void set(int index, int val) {
        tree[index + size] = val;
        index = (index + size) >> 1;
        while (index > 0) {
            tree[index] = tree[index << 1] + tree[index << 1 | 1];
            index >>= 1;
        }
    }

    void add(int index, int val) {
        set(index, tree[index + size] + val);
    }

    int kthOne(int k) {
        int current = 1;
        if (tree[1] < k) {
            return n - 1;
        }
        if (k <= 0) {
            return -1;
        }
        while (current < size) {
            int ones = tree[current * 2];
            if (k <= ones) {
                current = current * 2;
            } else {
                k -= ones;
                current = current * 2 + 1;
            }
        }
        return current - size;
    }
};

struct query2 {
    int v, l, r, k, idx;
    char c, d;

    query2(int v, int l, int r, int k, char c, char d, int idx) {
        this->v = v;
        this->l = l;
        this->r = r;
        this->k = k;
        this->c = c;
        this->d = d;
        this->idx = idx;
    }
};

std::ostream &operator<<(std::ostream &s, const query2 &q) {
    s << "(" << q.v << ", " << q.l << ", " << q.r << ", " << q.k << ", " << q.c << ", " << q.d << ", " << q.idx << ")";
    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    string s;
    int q;
    cin >> s >> q;
    vector<char> current(s.size() + 1);
    for (int i = 0; i < s.size(); i++) {
        current[i + 1] = s[i];
    }
    vector<vector<int>> chars(26, vector<int>(s.size() + 2));
    for (int i = 0; i < s.size(); i++) {
        chars[s[i] - 'a'][i + 1]++;
    }

    vector<segment_tree> current_version(26);
    for (int i = 0; i < 26; i++) {
        current_version[i] = segment_tree(chars[i]);
    }

    vector<pair<int, char>> updates;
    vector<query2> queries;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx;
            char x;
            cin >> idx >> x;
            updates.emplace_back(make_pair(idx, x));
        } else {
            int v, l, r, k;
            char c, d;
            cin >> v >> l >> r >> k >> c >> d;
            queries.emplace_back(query2(v, l, r, k, c, d, queries.size()));
        }
    }

    sort(queries.begin(), queries.end(), [](query2& a, query2& b) {
        if (a.v == b.v) {
            return a.idx < b.idx;
        }
        return a.v < b.v;
    });

    vector<int> ans(queries.size());
    int version = 0;
    for (int i = 0; i < queries.size(); i++) {
        while (version < queries[i].v && version < updates.size()) {
            pair<int, char>& u = updates[version];
            char y = current[u.first];
            current[u.first] = u.second;
            current_version[y - 'a'].set(u.first, 0);
            current_version[u.second - 'a'].set(u.first, 1);
            version++;
        }
        query2& q = queries[i];
        int outsideLeft = current_version[q.c - 'a'].query(0, q.l - 1);
        int c_rank = outsideLeft + q.k;
        int c_idx = min(q.r, max(q.l, current_version[q.c - 'a'].kthOne(c_rank)));
        int next_c_idx = min(q.r, max(q.l, current_version[q.c - 'a'].kthOne(c_rank + 1)));
        int outsideRight = current_version[q.d - 'a'].query(q.r + 1, s.size() + 1);
        int d_rank = current_version[q.d - 'a'].tree[1] - q.k + 1 - outsideRight;
        int d_idx = min(q.r, max(q.l, current_version[q.d - 'a'].kthOne(d_rank)));
        int left_endpoint = c_idx;
        int right_endpoint = min(d_idx, next_c_idx);
        ans[queries[i].idx] = max(0, right_endpoint - left_endpoint);
    }

    for (int i : ans) {
        cout << i << nl;
    }

    cout << nl;
}

