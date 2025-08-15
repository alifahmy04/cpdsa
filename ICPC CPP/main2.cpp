#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <cstdint>
#include <unordered_map>
#define nl '\n'
#define ll long long
#define int long long
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"

using namespace std;
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

class SegmentTree {
public:
    vector<int> tree;
    vector<int> lazy;
    vector<int> leaves;
    vector<bool> isSet;
    int n;

    SegmentTree(vector<int>& arr) {
        n = arr.size();
        int treeSize = (1 << (int)(log2(n) + 1));
        if (treeSize / 2 == n) treeSize = n;
        tree.resize(treeSize * 2);
        leaves.resize(n);
        lazy.resize(treeSize, 0);
        isSet.resize(treeSize, false);
        build(arr, 1, 0, n - 1);
    }

    int build(vector<int>& elements, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = elements[l];
            leaves[l] = idx;
        } else {
            int mid = (l + r) / 2;
            int leftChild = build(elements, idx << 1, l, mid);
            int rightChild = build(elements, idx << 1 | 1, mid + 1, r);
            tree[idx] = operation(leftChild, rightChild);
        }
        return tree[idx];
    }

    int operation(int a, int b) {
        return a + b;
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    int query(int node, int currentl, int currentr, int l, int r) {
        if (currentl >= l && currentr <= r) {
            return tree[node];
        }
        int mid = (currentl + currentr) >> 1;
        propagateNode(node, currentl, currentr);

        if (mid >= r) {
            return query(node << 1, currentl, mid, l, r);
        }
        if (mid + 1 <= l) {
            return query(node << 1, mid + 1, currentr, l, r);
        }
        return operation(query(node << 1, currentl, mid, l, r), query(node << 1 | 1, mid + 1, currentr, l, r));
    }

    void set(int index, int val) {
        update(1, 0, n - 1, index, index, val, true);
    }

    void setRange(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val, true);
    }

    void add(int index, int val) {
        update(1, 0, n - 1, index, index, val, false);
    }

    void addRange(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val, false);
    }

private:
    void update(int node, int currentl, int currentr, int l, int r, int val, bool set) {
        if (currentr < l || currentl > r) {
            return;
        }
        int mid = (currentl + currentr) / 2;
        if (currentl >= l && currentr <= r) {
            if (set) {
                tree[node] = val * (currentr - currentl + 1);
                if (currentl != currentr) {
                    lazy[node] = val;
                    isSet[node] = true;
                }
            } else {
                tree[node] += val * (currentr - currentl + 1);
                if (currentl != currentr) {
                    lazy[node] += val;
                }
            }
            return;
        }
        propagateNode(node, currentl, currentr);
        update(node * 2, currentl, mid, l, r, val, set);
        update(node * 2 + 1, mid + 1, currentr, l, r, val, set);
        tree[node] = operation(tree[node * 2], tree[node * 2 + 1]);
    }

    void propagateNode(int node, int currentl, int currentr) {
        int mid = (currentl + currentr) / 2;
        if (isSet[node]) {
            tree[node * 2] = lazy[node] * (mid - currentl + 1);
            tree[node * 2 + 1] = lazy[node] * (currentr - mid);
            if (currentl != mid) {
                lazy[node * 2] = lazy[node];
                isSet[node * 2] = true;
            }
            if (currentr != mid + 1) {
                lazy[node * 2 + 1] = lazy[node];
                isSet[node * 2 + 1] = true;
            }
        } else {
            tree[node * 2] += lazy[node] * (mid - currentl + 1);
            tree[node * 2 + 1] += lazy[node] * (currentr - mid);
            if (currentl != mid) {
                lazy[node * 2] += lazy[node];
            }
            if (currentr != mid + 1) {
                lazy[node * 2 + 1] += lazy[node];
            }
        }

        isSet[node] = false;
        lazy[node] = 0;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> nums = {1, 2, 3, 4, 5, 6};
    SegmentTree st(nums);
    
    cout << st.tree << nl;
    cout << st.leaves << nl;
    return 0;
}
