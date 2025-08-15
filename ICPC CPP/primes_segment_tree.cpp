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
    int left;
    int right;
    node(int val, int left = -1, int right = -1) : val(val), left(left), right(right) {}
};

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

vector<bool> sieve;
vector<int> sieve_map;

void tour() {

}

void initSieve(int N) {
    sieve.resize(N + 1, true);
    sieve_map.resize(N + 1, -1);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i < N; i++) {
        if (sieve[i]) {
            for (int j = 2*i; j < N; j += i) {
                sieve[j] = false;
            }
        }
    }
    int idx = 0;
    for (int i = 1; i <= N; i++) {
        if (sieve[i]) {
            sieve_map[i] = idx++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    initSieve(n + 10);
    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int parent, child;
        cin >> parent >> child;
        parent--; child--;
        adj[parent].push_back(child);
    }    
    
    vector<int> tour;
} 
