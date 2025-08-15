#include <bits/stdc++.h>
using namespace std;

class merge_sort_tree {
public: 
    int size = 1;
    vector<vector<int>> tree;
    vector<vector<pair<int, int>>> gaps;

public:
    merge_sort_tree(const vector<int>& elements) {
        size = 1 << (int) ceil(log2(elements.size()));
        tree.resize(size << 1, vector<int>({0}));
        gaps.resize(size << 1);
        for (int i = 0; i < elements.size(); i++) {
            tree[i + size] = vector<int>({elements[i]});
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1], i);
        }
    }

    vector<int> operation(vector<int> a, vector<int> b, int i) {
        int l = 0, r = 0, idx = 0;
        vector<int> output = vector<int>(a.size() + b.size());
        while (idx < output.size()) {
            if (r == b.size() || l < a.size() && a[l] <= b[r]) {
                output[idx] = a[l];
                l++;
            } else {
                output[idx] = b[r];
                r++;
            }
            if (idx > 1 && output[idx] - output[idx - 1] > 1) {
                gaps[i].emplace_back(make_pair(output[idx - 1], output[idx]));
            }
            idx++;
        }
        return output;
    }

    int query(int node, int currentl, int currentr, int l, int r, int x) {
        if (currentl >= l && currentr <= r) {
            if (gaps.size() > 0 && gaps[node][0].first < x) {
                if (x > tree[node])
                return findMaximumExcluded(gaps[node], x);
            };
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            return query(node << 1, l, r, currentl, mid);
        }
        if (mid < l) {
            return query(node << 1 | 1, l, r, mid + 1, currentr);
        }
        int leftChild = query(node << 1, l, r, currentl, mid);
        int rightChild = query(node << 1 | 1, l, r, mid + 1, currentr);
        
    }

    int findMaximumExcluded(vector<pair<int, int>>, int x) {
        if (x > gaps)
    }
};