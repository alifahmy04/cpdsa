#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <random>
#include <unordered_set>
#include <sstream>
#include <queue>
#define nl '\n'
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"

using namespace std;
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

    void printTree(int ver, bool onlyLeaves) {
        if (ver >= roots.size()) {
            cout << "Version " << ver << " does not exist." << endl;
            return;
        }
        queue<Node*> q;
        q.push(roots[ver]);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current == nullptr) {
                continue;
            }
            if (!onlyLeaves || onlyLeaves && current->left == nullptr && current->right == nullptr) {
                cout << current->val << " ";
            } 
            q.push(current->left);
            q.push(current->right);
        }
        cout << "\n";
    }

    void printTree(int version) {
        printTree(version, false);
    }

    void printLeaves(int version) {
        printTree(version, true);
    }
};

int main() {
    vector<int> hello = {1, 2, 3, 4, 5, 6, 7, 8};
    persistent_segment_tree pst(hello);

    cout << pst.query(0, 2, 0) << nl;
    pst.set(0, 2, 0);
    pst.printLeaves(0);
    pst.printTree(0);
    pst.printLeaves(1);
    cout << pst.query(0, 2, 0) << nl;
    cout << pst.query(0, 2, 1) << nl;
}