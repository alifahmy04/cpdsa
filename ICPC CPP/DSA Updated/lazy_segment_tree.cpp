#include <bits/stdc++.h>
using namespace std;

class lazy_segment_tree {
public:
    vector<int> tree;
    vector<int> lazy;
    vector<bool> isSet;
    int n;
    int treeSize;

    lazy_segment_tree(const vector<int>& arr) : n(arr.size()) {
        treeSize = 1 << (int) ceil(log2(arr.size()));
        tree.resize(treeSize << 1);
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
        return a + b;
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
                tree[node] = val * (currentr - currentl + 1);
                lazy[node] = val;
                isSet[node] = true;
            } else {
                tree[node] += val * (currentr - currentl + 1);
                lazy[node] += val;
            }
            return;
        }
        propagateNode(node, currentl, currentr);
        update(node * 2, currentl, mid, l, r, val, set);
        update(node * 2 + 1, mid + 1, currentr, l, r, val, set);
        tree[node] = operation(tree[node << 1], tree[node << 1 | 1]);
    }

    void propagateNode(int node, int currentl, int currentr) {
        int mid = (currentl + currentr) >> 1;
        if (isSet[node]) {
            tree[node * 2] = lazy[node] * (mid - currentl + 1);
            tree[node * 2 + 1] = lazy[node] * (currentr - mid);
            lazy[node * 2] = lazy[node];
            isSet[node * 2] = true;
            lazy[node * 2 + 1] = lazy[node];
            isSet[node * 2 + 1] = true;
        } else {
            tree[node * 2] += lazy[node] * (mid - currentl + 1);
            tree[node * 2 + 1] += lazy[node] * (currentr - mid);
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        isSet[node] = false;
        lazy[node] = 0;
    }
};

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    lazy_segment_tree st(a);

    while (true) {
        int x, l, r;
        cin >> x >> l >> r;
        if (x == 0) {
            int v;
            cin >> v;
            st.addRange(l, r, v);
        } else if (x == 1) {
            int v;
            cin >> v;
            st.setRange(l, r, v);
        } else if (x == 2) {
            cout << st.query(l, r) << '\n';
        }
    }
}
