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
#define int long long
#define ll long long
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"

using namespace std;
struct triple {
    int x;
    int y;
    int z;

    triple() {};
    triple(int x, int y, int z) : x(x), y(y), z(z) {};
};

class SegmentTree {
public:
    vector<int> tree;
    vector<int> lazy;
    vector<bool> isSet;
    int n;

    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        int treeSize = (1 << (int)(log2(n) + 1));
        if (treeSize / 2 == n) treeSize = n;
        tree.resize(treeSize * 2);
        lazy.resize(treeSize, 0);
        isSet.resize(treeSize, false);
        n = treeSize;

        for (int i = 0; i < arr.size(); i++) {
            tree[i + treeSize] = arr[i];
        }

        for (int i = treeSize - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    int operation(int a, int b) {
        return a | b;
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
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
        update(1, 0, n - 1, index, index, val, true);
    }

    void setRange(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val, true);
    }

private:
    void update(int node, int currentl, int currentr, int l, int r, int val, bool set) {
        if (currentr < l || currentl > r) {
            return;
        }
        int mid = (currentl + currentr) / 2;
        if (currentl >= l && currentr <= r) {
            if (set) {
                tree[node] = val;
                if (currentl != currentr) {
                    lazy[node] = val;
                    isSet[node] = true;
                }
            } else {
                tree[node] += val;
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
            tree[node * 2] = lazy[node];
            tree[node * 2 + 1] = lazy[node];
            if (currentl != mid) {
                lazy[node * 2] = lazy[node];
                isSet[node * 2] = true;
            }
            if (currentr != mid + 1) {
                lazy[node * 2 + 1] = lazy[node];
                isSet[node * 2 + 1] = true;
            }
        } else {
            tree[node * 2] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
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

std::ostream& operator<<(std::ostream& s, const pair<int, int>& t) { 
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

std::ostream& operator<<(std::ostream& s, const triple& t) { 
    s << "(" << t.x << ", " << t.y << ", " << t.z << ")";
    return s;
}


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

string arrToString(int* arr, int size) {
    std::ostringstream result;  
    result << "[";              
    for (int i = 0; i < size; ++i) {
        result << arr[i];       
        if (i != size - 1) {
            result << ", ";   
        }
    }
    result << "]";              
    return result.str(); 
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {0, 4, 2, 0, 16, 0, 1 ,0};
    SegmentTree st(arr);
    cout << st.query(0, 7) << nl;
    st.setRange(0, 3, 8);
    cout << st.lazy << nl;
    cout << st.tree << nl;
    cout << st.query(0, 1) << nl;
    cout << st.lazy << nl;
    cout << st.tree << nl;
    st.setRange(0, 6, 4);
    cout << st.query(3, 6) << nl;
}
