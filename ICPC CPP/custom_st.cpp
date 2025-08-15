#include <bits/stdc++.h>
using namespace std;

struct sortedArray {
    vector<int> array;
    int n;

    sortedArray() {
        array = vector<int>();
        n = 0;
    }

    void insert(int x) {
        array.push_back(x);
        n++;
    }

    int size() {
        return n;
    }

    void merge(sortedArray& b, sortedArray& res) {
        int ptr1 = 0;
        int ptr2 = 0;
        while (ptr1 < array.size() && ptr2 < b.size()) {
            if (array[ptr1] <= b.array[ptr2]) {
                res.insert(array[ptr1++]);
            } else {
                res.insert(b.array[ptr2++]);
            }
        }
        while (ptr1 < array.size())
            res.insert(array[ptr1++]);
        while (ptr2 < b.size())
            res.insert(b.array[ptr2++]);
    }
};

class segment_tree {
public: 
    int size = 1;
    vector<sortedArray> tree;

public:
    segment_tree(const vector<int>& elements) {
        size = 1 << (int) ceil(log2(elements.size()));
        tree.resize(size << 1);
        for (int i = 0; i < elements.size(); i++) {
            sortedArray s;
            s.insert(elements[i]);
            tree[i + size] = s;
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    sortedArray operation(sortedArray& a, sortedArray& b) {
        sortedArray res;
        a.merge(b, res);
        return res;
    }

    sortedArray query(int l, int r) {
        return query(1, l, r, 0, size - 1);
    }

    sortedArray query(int currentIndex, int l, int r, int currentl, int currentr) {
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
        sortedArray leftChild = query(currentIndex << 1, l, r, currentl, mid);
        sortedArray rightChild = query(currentIndex << 1 | 1, l, r, mid + 1, currentr);
        return operation(leftChild, rightChild);
    }
};