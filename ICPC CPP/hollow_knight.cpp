#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define ll long long
using namespace __gnu_pbds;
using namespace std;

using Ht = gp_hash_table<int, int>;

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

vector<bool> sieve;

void tour(vector<vector<int>>& adj, vector<int>& result, vector<int>& size, vector<int>& index, int parent, int node) {
    result.push_back(node);
    index[node] = result.size() - 1;
    for (int i : adj[node]) {
        if (i == parent) {
            continue;
        }
        tour(adj, result, size, index, node, i);
        size[node] += size[i];
    }
}

class segment_tree {
public: 
    int size = 1;
    vector<Ht> tree;

public:
    segment_tree(const vector<int>& elements) {
        size = 1 << (int) ceil(log2(elements.size()));
        tree.resize(size << 1);
        for (int i = 0; i < elements.size(); i++) {
            if (sieve[elements[i]]) {
                tree[i + size][elements[i]] = 1;
            }
        }
        for (int i = size - 1; i > 0; i--) {
            tree[i] = operation(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    Ht operation(Ht& a, Ht& b) {
        Ht res;
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

    void get_nodes(int l, int r, vector<int>& res) {
        get_nodes(1, l, r, 0, size - 1, res);
    }

    void get_nodes(int currentIndex, int l, int r, int currentl, int currentr, vector<int>& res) {
        if (currentl >= l && currentr <= r) {
            res.push_back(currentIndex);
            return;
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            get_nodes(currentIndex << 1, l, r, currentl, mid, res);
            return;
        }
        if (mid < l) {
            get_nodes(currentIndex << 1 | 1, l, r, mid + 1, currentr, res);
            return;
        }
        get_nodes(currentIndex << 1, l, r, currentl, mid, res);
        get_nodes(currentIndex << 1 | 1, l, r, mid + 1, currentr, res);
    }

    void set(int index, int val) {
        int old_val = INT_MAX;
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

void initSieve(int N) {
    sieve.resize(N + 1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i <= N; i++) {
        if (sieve[i]) {
            for (int j = 2*i; j <= N; j += i) {
                sieve[j] = false;
            }
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
    initSieve(1e5);
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
        adj[child].push_back(parent);
    }
    vector<int> primes;
    for (int i = 1; i <= 1e5; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    vector<int> tour_array;
    vector<int> size(n, 1);
    vector<int> index(n);
    tour(adj, tour_array, size, index, 0, 0);
    vector<int> tour_values(n);
    for (int i = 0; i < n; i++) {
        tour_values[i] = values[tour_array[i]];
    }
    segment_tree st(tour_values);
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int v;
            cin >> v;
            v--;
            int l = index[v];
            int r = index[v] + size[v] - 1;
            vector<int> nodes;
            st.get_nodes(l, r, nodes);
            unordered_set<int> prime_values;
            for (int i : nodes) {
                for (auto& x : st.tree[i]) {
                    prime_values.insert(x.first);
                }
            }
            cout << prime_values.size() << nl;
        } else if (type == 2) {
            int v, x;
            cin >> v >> x;
            v--;
            int l = index[v];
            int r = index[v] + size[v] - 1;
            cout << st.find(l, r, x) << nl;
        } else {
            int v, x;
            cin >> v >> x;
            v--;
            int idx = index[v];
            st.set(idx, x);
        }
    }
} 
