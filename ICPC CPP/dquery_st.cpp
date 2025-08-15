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

class segment_tree {
public: 
    int size = 1;
    int n;
    vector<int> tree;

public:
    segment_tree(int n) : n(n) {
        size = 1 << (int) ceil(log2(n));
        tree.resize(size << 1, 0);
    }

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
            tree[index] = operation(tree[index << 1], tree[index << 1 | 1]);
            index >>= 1;
        }
    }

    void add(int index, int val) {
        set(index, tree[index + size] + val);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int q;
    cin >> q;
    vector<triple> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = triple(l, r, i);
    }  
    sort(queries.begin(), queries.end(), [](triple& a, triple& b) {
        return a.x < b.x;
    }); 

    unordered_map<int, int> occ_map;
    occ_map.reserve(1024);
    vector<pair<int, int>> prev_occ(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        prev_occ[i].second = i;
        if (occ_map.count(nums[i])) {
            prev_occ[i].first = occ_map[nums[i]];
        }
        occ_map[nums[i]] = i;
    }
    sort(prev_occ.begin(), prev_occ.end());
    segment_tree st(n);
    vector<int> ans(q);
    int idx = n - 1;
    for (int i = q - 1; i >= 0; i--) {
        triple& query = queries[i];
        query.x--; query.y--;
        while (prev_occ[idx].first >= query.x) {
            st.add(prev_occ[idx].second, 1);
            idx--;
        }
        ans[query.z] = (query.y - query.x + 1) - st.query(query.x, query.y);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << nl;
    }
} 
