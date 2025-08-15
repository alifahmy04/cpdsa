
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

class persistent_segment_tree {
public:
    int n;
    vector<node*> roots;

    persistent_segment_tree(int n) : n(n) {
        roots.resize(n + 1, nullptr);
        roots[0] = build(0, n - 1);
    }

    int operation(int a, int b) {
        return a + b;
    }

    node* build(int l, int r) {
        if (l == r) {
            return new node(0);
        }
        int mid = (l + r) >> 1;
        node* leftChild = build(l, mid);
        node* rightChild = build(mid + 1, r);
        return new node(operation(leftChild->val, rightChild->val), leftChild, rightChild);
    }

    void set(int index, int val, int ver, int newVer) {
        roots[newVer] = update(roots[ver], val, 0, n - 1, index, true);
    }

    void add(int index, int val, int ver, int newVer) {
        roots[newVer] = update(roots[ver], val, 0, n - 1, index, false);
    }

    node* update(node* current, int val, int currentl, int currentr, int index, bool set) {
        if (currentl > index || currentr < index) {
            return current;
        }
        if (currentl == currentr) {
            int newVal = set ? val : current->val + val;
            return new node(newVal);
        }
        int mid = (currentl + currentr) >> 1;
        node* leftChild = update(current->left, val, currentl, mid, index, set);
        node* rightChild = update(current->right, val, mid + 1, currentr, index, set);
        return new node(operation(leftChild->val, rightChild->val), leftChild, rightChild);
    }

    int query(int l, int r, int ver) {
        return query(roots[ver], 0, n - 1, l, r);
    }

    int query(node* current, int currentl, int currentr, int l, int r) {
        if (currentl >= l && currentr <= r) {
            return current->val;
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) return query(current->left, currentl, mid, l, r);
        if (mid < l) return query(current->right, mid + 1, currentr, l, r);
        return operation(query(current->left, currentl, mid, l, r), query(current->right, mid + 1, currentr, l, r));
    }

    int kthMinimum(int currentl, int currentr, int u, int v, int lca, int lca_parent, int k) {
        node* u_node = roots[u];
        node* v_node = roots[v];
        node* lca_node = roots[lca];
        node* parent_node = roots[lca_parent];
        while (currentl != currentr) {
            int ones = u_node->left->val + v_node->left->val - lca_node->left->val - parent_node->left->val;
            int mid = (currentl + currentr) / 2;
            if (k <= ones) {
                u_node = u_node->left;
                v_node = v_node->left;
                lca_node = lca_node->left;
                parent_node = parent_node->left;
                currentr = mid;
            } else {
                k -= ones;
                u_node = u_node->right;
                v_node = v_node->right;
                lca_node = lca_node->right;
                parent_node = parent_node->right;
                currentl = mid + 1;
            }
        }
        return currentl;
    }

    int lessThanEquals(int u, int v, int lca, int lca_parent, int x) {
        return query(0, x, u) + query(0, x, v) - query(0, x, lca) - query(0, x, lca_parent);
    }

    int lessThan(int u, int v, int lca, int lca_parent, int x) {
        return query(0, x - 1, u) + query(0, x - 1, v) - query(0, x - 1, lca) - query(0, x - 1, lca_parent);
    }

    int greaterThanEquals(int u, int v, int lca, int lca_parent, int x) {
        return query(x, n - 1, u) + query(x, n - 1, v) - query(x, n - 1, lca) - query(x, n - 1, lca_parent);
    }

    int greaterThan(int u, int v, int lca, int lca_parent, int x) {
        return query(x + 1, n - 1, u) + query(x + 1, n - 1, v) - query(x + 1, n - 1, lca) - query(x + 1, n - 1, lca_parent);
    }

    int kthMinimum(int u, int v, int lca, int lca_parent, int k) {
        return kthMinimum(0, n - 1, u, v, lca, lca_parent, k);
    }

    void display(node* n) {
        if (n->left == nullptr && n->right == nullptr) {
            cout << n->val << ' ';
            return;
        }
        display(n->left);
        display(n->right);
    }
 
    void display(int version) {
        display(roots[version]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    // cout.tie(nullptr);
    // cin.tie(nullptr);
    
    persistent_segment_tree pst(10);
    
    pst.add(1, 1, 0, 1);
    pst.add(7, 1, 1, 2);
    pst.add(3, 1, 2, 3);
    pst.add(5, 1, 2, 4);
    pst.add(9, 1, 4, 5);
    pst.add(6, 1, 1, 6);

    cout << pst.lessThanEquals(3, 5, 2, 1, 5) << nl;
    cout << pst.lessThanEquals(3, 5, 2, 1, 6) << nl;
    cout << pst.lessThanEquals(3, 5, 2, 1, 7) << nl;
    cout << pst.lessThanEquals(3, 5, 2, 1, 8) << nl;
    cout << pst.lessThanEquals(3, 5, 2, 1, 9) << nl;
    cout << nl;
    cout << pst.kthMinimum(3, 5, 2, 1, 1) << nl;
    cout << pst.kthMinimum(3, 5, 2, 1, 2) << nl;
    cout << pst.kthMinimum(3, 5, 2, 1, 3) << nl;
    cout << pst.kthMinimum(3, 5, 2, 1, 4) << nl;
} 
