#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> t) { 
    s << "[";
    for (int i = 0; i < t.size(); i++) {
        s << t[i];
        if (i != t.size() - 1) {
            s << ", ";
        }
    }
    return s << "]";
}

class persistent_segment_tree {
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

public:
    int n;
    vector<Node*> roots;

public:
    persistent_segment_tree(const vector<int>& arr) : n(arr.size()) {
        roots.push_back(build(arr, 0, n - 1));
    }

    int operation(int a, int b) {
        return a + b;
    }

    Node* build(const vector<int>& arr, int l, int r) {
        if (l == r) {
            return new Node(arr[l]);
        }
        int mid = (l + r) / 2;
        Node* leftChild = build(arr, l, mid);
        Node* rightChild = build(arr, mid + 1, r);
        return new Node(operation(leftChild->val, rightChild->val), leftChild, rightChild);
    }

    void set(int index, int val, int ver = -1) {
        if (ver == -1) ver = roots.size() - 1;
        roots.push_back(update(roots[ver], val, 0, n - 1, index, true));
    }

    void add(int index, int val, int ver = -1) {
        if (ver == -1) ver = roots.size() - 1;
        roots.push_back(update(roots[ver], val, 0, n - 1, index, false));
    }

    Node* update(Node* current, int val, int currentl, int currentr, int index, bool set) {
        if (currentl > index || currentr < index) {
            return current;
        }
        if (currentl == currentr) {
            int newVal = set ? val : current->val + val;
            return new Node(newVal);
        }
        int mid = (currentl + currentr) / 2;
        Node* leftChild = update(current->left, val, currentl, mid, index, set);
        Node* rightChild = update(current->right, val, mid + 1, currentr, index, set);
        return new Node(operation(leftChild->val, rightChild->val), leftChild, rightChild);
    }

    int query(int l, int r, int ver) {
        return query(roots[ver], 0, n - 1, l, r);
    }

    int query(Node* current, int currentl, int currentr, int l, int r) {
        if (currentl >= l && currentr <= r) {
            return current->val;
        }
        int mid = (currentl + currentr) / 2;
        if (mid >= r) return query(current->left, currentl, mid, l, r);
        if (mid < l) return query(current->right, mid + 1, currentr, l, r);
        return operation(query(current->left, currentl, mid, l, r), query(current->right, mid + 1, currentr, l, r));
    }

    int findKth(int currentl, int currentr, int k, int l, int r) {
        Node* leftNode = roots[l - 1];
        Node* rightNode = roots[r];

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
    
    int findKth(int k, int l, int r) {
        return findKth(0, n - 1, k, l, r);
    }

    int kquery(Node* leftNode, Node* rightNode, int currentl, int currentr, int k) {
        if (currentl > k) {
            return rightNode->val - leftNode->val;
        }
        int mid = (currentl + currentr) / 2;
        if (mid <= k) {
            return kquery(leftNode->right, rightNode->right, mid + 1, currentr, k);
        }
        int leftResult = kquery(leftNode->left, rightNode->left, currentl, mid, k);
        int rightResult = kquery(leftNode->right, rightNode->right, mid + 1, currentr, k);
        return leftResult + rightResult;
    }

    int kquery(int l, int r, int k) {
        return kquery(roots[l - 1], roots[r], 0, n - 1, k);
    }

    void printLeaves(int version) {
        printLeaves(roots[version]);
    }

    void printLeaves(Node* current) {
        if (current == nullptr) {
            return;
        }
        if (current->left == nullptr && current->right == nullptr) {
            cout << current->val << " ";
        }
        printLeaves(current->left);
        printLeaves(current->right);
    }
};

int findCompressedK(vector<int>& mapping, int k) {
    int l = 0, r = mapping.size() - 1, m = (l + r) / 2;
    while (l <= r) {
        if (mapping[m] <= k) {
            l = m + 1;
        } else {
            r = m - 1;
        }
        m = (l + r) / 2;
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
} 