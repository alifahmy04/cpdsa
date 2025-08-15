#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
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

class segment_tree_2d {
public: 
    int size = 1;
    int colSize = 1;
    vector<vector<int>> tree;

public:
    segment_tree_2d(const vector<vector<int>>& elements) {
        size = 1 << (int) ceil(log2(elements.size()));
        colSize = 1 << (int) ceil(log2(elements[0].size()));
        tree.resize(size << 1, vector<int>(colSize << 1, 0));
        for (int i = 0; i < elements.size(); i++) {
            for (int j = 0; j < elements[i].size(); j++) {
                tree[i + size][j + colSize] = elements[i][j];
            }

            for (int j = colSize - 1; j > 0; j--) {
                tree[i + size][j] = operation(tree[i + size][j << 1], tree[i + size][j << 1 | 1]);
            }
        }

        for (int i = size - 1; i > 0; i--) {
            for (int j = 1; j < tree[i].size(); j++) {
                tree[i][j] = operation(tree[i << 1][j], tree[i << 1 | 1][j]);
            }
        }
    }

    int operation(int a, int b) {
        return a + b;
    }

    int query(int l, int r, int l2, int r2) {
        return query(1, -1, l, r, l2, r2, 0, size - 1, true);
    }

    int query(int currentIndex, int rowIndex, int l, int r, int l2, int r2, int currentl, int currentr, bool isRow) {
        if (currentl >= l && currentr <= r) {
            if (isRow) {
                return query(1, currentIndex, l2, r2, -1, -1, 0, colSize - 1, false);
            }
            return tree[rowIndex][currentIndex];
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            return query(currentIndex << 1, rowIndex, l, r, l2, r2, currentl, mid, isRow);
        }
        if (mid < l) {
            return query(currentIndex << 1 | 1, rowIndex, l, r, l2, r2, mid + 1, currentr, isRow);
        }
        int leftChild = query(currentIndex << 1, rowIndex, l, r, l2, r2, currentl, mid, isRow);
        int rightChild = query(currentIndex << 1 | 1, rowIndex, l, r, l2, r2, mid + 1, currentr, isRow);
        return operation(leftChild, rightChild);
    }
};

int main() {
    vector<vector<int>> nums = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    segment_tree_2d st(nums);
    cout << st.tree << '\n';
    while (true) {
        int x1, y1, x2, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        cout << st.query(x1, x2, y1, y2) << '\n';
    }
}