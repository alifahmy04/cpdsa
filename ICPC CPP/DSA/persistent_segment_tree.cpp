#include <bits/stdc++.h>
#define nl '\n'
using namespace std;

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

    persistent_segment_tree(const vector<int>& arr) : n(arr.size()) {
        roots.push_back(build(arr, 0, n - 1));
    }

    int operation(int a, int b) {
        return a + b;
    }

    node* build(const vector<int>& arr, int l, int r) {
        if (l == r) {
            return new node(arr[l]);
        }
        int mid = (l + r) >> 1;
        node* leftChild = build(arr, l, mid);
        node* rightChild = build(arr, mid + 1, r);
        return new node(operation(leftChild->val, rightChild->val), leftChild, rightChild);
    }

    void set(int index, int val, int ver = -1) {
        if (ver == -1) ver = roots.size() - 1;
        roots.push_back(update(roots[ver], val, 0, n - 1, index, true));
    }

    void add(int index, int val, int ver = -1) {
        if (ver == -1) ver = roots.size() - 1;
        roots.push_back(update(roots[ver], val, 0, n - 1, index, false));
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

    int minMaxQuery(int currentl, int currentr, int l, int r, int k) {
        node* leftNode = roots[l - 1];
        node* rightNode = roots[r];
        while (currentl != currentr) {
            int ones = rightNode->left->val - leftNode->left->val;
            int mid = (currentl + currentr) / 2;
            if (k <= ones) {
                leftNode = leftNode->left;
                rightNode = rightNode->left;
                currentr = mid;
            } else {
                k -= ones;
                leftNode = leftNode->right;
                rightNode = rightNode->right;
                currentl = mid + 1;
            }
        }
        return currentl;
    }

    int kthMinimum(int l, int r, int k) {
        return minMaxQuery(0, n - 1, l + 1, r + 1, k);
    }

    int kthMaximum(int l, int r, int k) {
        return kthMinimum(l, r, r - l + 2 - k);
    }
    
    int frequency(int l, int r, int k) {
        return query(k, k, r + 1) - query(k, k, l);
    }

    int countGreater(int l, int r, int k) {
        return query(k + 1, n - 1, r + 1) - query(k + 1, n - 1, l);
    }

    int countGreaterEquals(int l, int r, int k) {
        return query(k, n - 1, r + 1) - query(k, n - 1, l);
    }

    int countLess(int l, int r, int k) {
        return query(0, k - 1, r + 1) - query(0, k - 1, l);
    }

    int countLessEquals(int l, int r, int k) {
        return query(0, k, r + 1) - query(0, k, l);
    }
};

int main() {
    vector<int> nums = {8, 9, 3, 5, 3, 1, 9};
    persistent_segment_tree pst(vector<int>(10));
    for (int i = 0; i < nums.size(); i++) {
        pst.add(nums[i], 1);
    }

    while (true) {
        int x;
        cin >> x;
        int k, l, r;
        cin >> k >> l >> r;
        if (x == 0) {
            cout << pst.kthMinimum(l, r, k) << nl;
        } else if (x == 1) {
            cout << pst.kthMaximum(l, r, k) << nl;
        } else if (x == 2) {
            cout << pst.frequency(l, r, k) << nl;
        } else if (x == 3) {
            cout << pst.countGreater(l, r, k) << nl;
        } else if (x == 4) {
            cout << pst.countGreaterEquals(l, r, k) << nl;
        } else if (x == 5) {
            cout << pst.countLess(l, r, k) << nl;
        } else if (x == 6) {
            cout << pst.countLessEquals(l, r, k) << nl;
        }
    }
}