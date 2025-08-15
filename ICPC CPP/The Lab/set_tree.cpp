#include <bits/stdc++.h>
using namespace std;

class segment_tree {
public: 
    int size = 1;
    vector<unordered_map<int, int>> tree;

public:
    segment_tree(const vector<int>& elements) {
        size = 1 << (int) ceil(log2(elements.size()));
        tree.resize(size << 1);
        for (int i = 0; i < elements.size(); i++) {
            tree[i + size][elements[i]] = 1;
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    unordered_map<int, int> operation(unordered_map<int, int>& a, unordered_map<int, int>& b) {
        unordered_map<int, int> res;
        for (auto& x : a) {
            res[x.first] = x.second;
        }
        for (auto& x : b) {
            if (a.find(x.first) == a.end()) {
                res[x.first] = 0;
            }
            res[x.first] += x.second;
        }
        return res;
    }

    bool find(int l, int r, int val) {
        return find(1, l, r, 0, size - 1, val);
    }

    bool find(int currentIndex, int l, int r, int currentl, int currentr, int val) {
        if (currentl >= l && currentr <= r) {
            return tree[currentIndex].find(val) != tree[currentIndex].end();
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            return find(currentIndex << 1, l, r, currentl, mid, val);
        }
        if (mid < l) {
            return find(currentIndex << 1 | 1, l, r, mid + 1, currentr, val);
        }
        bool leftChild = find(currentIndex << 1, l, r, currentl, mid, val);
        bool rightChild = find(currentIndex << 1 | 1, l, r, mid + 1, currentr, val);
        return leftChild | rightChild;
    }

    void set(int index, int val) {
        int old_val;
        for (auto& x : tree[index + size]) {
            old_val = x.first;
        }
        tree[index + size].clear();
        tree[index + size][val] = 1;
        index = (index + size) >> 1;
        while (index > 0) {
            if (tree[index].find(old_val) != tree[index].end() && tree[index][old_val] > 0) {
                tree[index][old_val]--;
                if (tree[index][old_val] == 0) {
                    tree[index].erase(old_val);
                }
            }
            if (tree[index].find(val) == tree[index].end()) {
                tree[index][val] = 0;
            }
            tree[index][val]++;
            index >>= 1;
        }
    }
};

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6};
    segment_tree st(a);
    st.set(2, 2);
    while (true) {
        int l, r, val;
        cin >> l >> r >> val;
        cout << st.find(l, r, val) << '\n';
    }
}