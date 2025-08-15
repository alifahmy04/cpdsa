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

class lazy_segment_tree {
public:
    vector<int> tree;
    vector<int> lazy;
    vector<bool> isSet;
    int n;
    int treeSize;

    lazy_segment_tree(const vector<int>& arr) : n(arr.size()) {
        treeSize = 1 << (int) ceil(log2(arr.size()));
        tree.resize(treeSize << 1, -100);
        lazy.resize(treeSize << 1, 0);
        isSet.resize(treeSize << 1, false);

        for (int i = 0; i < arr.size(); i++) {
            tree[i + treeSize] = arr[i];
        }
        for (int i = treeSize - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    int operation(int a, int b) {
        return max(a, b);
    }

    int query(int l, int r) {
        return query(1, 0, treeSize - 1, l, r);
    }

    int query(int node, int currentl, int currentr, int l, int r) {
        if (currentl >= l && currentr <= r) {
            return tree[node];
        }
        int mid = (currentl + currentr) / 2;
        propagateNode(node, currentl, currentr);
        if (mid >= r) {
            return query(node * 2, currentl, mid, l, r);
        }
        if (mid + 1 <= l) {
            return query(node * 2 + 1, mid + 1, currentr, l, r);
        }
        return operation(query(node * 2, currentl, mid, l, r), query(node * 2 + 1, mid + 1, currentr, l, r));
    }

    void set(int index, int val) {
        update(1, 0, treeSize - 1, index, index, val, true);
    }

    void setRange(int l, int r, int val) {
        update(1, 0, treeSize - 1, l, r, val, true);
    }

    void add(int index, int val) {
        update(1, 0, treeSize - 1, index, index, val, false);
    }

    void addRange(int l, int r, int val) {
        update(1, 0, treeSize - 1, l, r, val, false);
    }

private:
    void update(int node, int currentl, int currentr, int l, int r, int val, bool set) {
        if (currentr < l || currentl > r) {
            return;
        }
        int mid = (currentl + currentr) >> 1;
        if (currentl >= l && currentr <= r) {
            if (set) {
                if (tree[node] != tree[1] || tree[node] == 0) {
                    return;
                }
                if (currentl == currentr) {
                    tree[node] = 0;
                    return;
                }
            } else {
                tree[node] += val;
                lazy[node] += val;
                return;
            }
        }
        propagateNode(node, currentl, currentr);
        update(node * 2, currentl, mid, l, r, val, set);
        update(node * 2 + 1, mid + 1, currentr, l, r, val, set);
        tree[node] = operation(tree[node << 1], tree[node << 1 | 1]);
    }

    void propagateNode(int node, int currentl, int currentr) {
        int mid = (currentl + currentr) >> 1;
        if (isSet[node]) {
            tree[node * 2] = lazy[node];
            tree[node * 2 + 1] = lazy[node];
            lazy[node * 2] = lazy[node];
            isSet[node * 2] = true;
            lazy[node * 2 + 1] = lazy[node];
            isSet[node * 2 + 1] = true;
        } else {
            tree[node * 2] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        isSet[node] = false;
        lazy[node] = 0;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    lazy_segment_tree st(nums);
    for (int i = 0; i < k; i++) {
        string type;
        int l, r;
        cin >> type >> l >> r;
        l--; r--;
        if (type == "Q") {
            cout << st.query(l, r) << nl;
        } else if (type == "A") {
            st.addRange(l, r, 1);
        } else {
            st.setRange(l, r, 0);
        }
    }
} 
