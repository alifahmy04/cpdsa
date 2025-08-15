#include <bits/stdc++.h>
using namespace std;


class segment_tree {
public: 
    int size;
    vector<int> tree;

public:
    segment_tree(const vector<int>& elements) {
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
            tree[index] = tree[index << 1] + tree[index << 1 | 1];
            index >>= 1;
        }
    }

    void add(int index, int val) {
        set(index, tree[index + size] + val);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    segment_tree st(nums);
    while (true) {
        string x;
        cin >> x;
        if (x == "stop") {
            return 0;
        } else if (x == "set") {
            int i, val;
            cin >> i >> val;
            st.set(i, val);
        } else if (x == "add") {
            int i, val;
            cin >> i >> val;
            st.add(i, val);
        } else if (x == "query") {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << '\n';
        }
    }
}


    