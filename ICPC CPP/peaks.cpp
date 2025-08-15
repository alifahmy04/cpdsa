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

class segment_tree {
public: 
    int size = 1;
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
        return max(a, b);
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
            tree[index] = operation(tree[index << 1], tree[index << 1 | 1]);
            index >>= 1;
        }
    }

    void add(int index, int val) {
        set(index, tree[index + size] + val);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        unordered_map<int, int> occ_map;
        segment_tree max_tree(nums);
        vector<int> prev(n, -1);
        vector<triple> peaks;
        for (int i = 0; i < n; i++) {
            if (occ_map.find(nums[i]) != occ_map.end()) {
                prev[i] = occ_map[nums[i]];
                int peak_val = max_tree.query(prev[i], i);
                if (peak_val > nums[i]) {
                    peaks.emplace_back(prev[i], i, peak_val);
                }
            }
            occ_map[nums[i]] = i;
        }
        int q;
        cin >> q;
        vector<triple> queries(q);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            queries[i] = triple(l, r, i);
        }
        sort(peaks.begin(), peaks.end(), [](triple& a, triple& b) {
            return a.y < b.y;
        });
        sort(queries.begin(), queries.end(), [](triple& a, triple& b) {
            return a.y < b.y;
        });
        segment_tree segments((vector<int>(n)));
        vector<int> ans(q);
        int idx = 0;
        for (int i = 0; i < q; i++) {
            while (idx < peaks.size() && peaks[idx].y <= queries[i].y) {
                segments.add(peaks[idx].x, peaks[idx].z);
                idx++;
            }
            ans[queries[i].z] = segments.query(queries[i].x, queries[i].y);
        }
        for (int i : ans) {
            cout << i << nl;
        }
    }
    
} 
