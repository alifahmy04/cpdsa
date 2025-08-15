#include <bits/stdc++.h>
using namespace std;

class union_tree {
public:
    vector<unordered_set<int>*> tree;
    vector<unordered_set<int>*> lazy;
    vector<int> leaves;
    int n;

    union_tree(int size) {
        n = size;
        int treeSize = (1 << (int)(log2(n) + 1));
        if (treeSize / 2 == n) treeSize = n;
        tree.resize(treeSize * 2, new unordered_set<int>());
        lazy.resize(treeSize, new unordered_set<int>());
        leaves.resize(n);
    }

    unordered_set<int>* operation(const unordered_set<int>* a, const unordered_set<int>* b) {
        unordered_set<int>* res = new unordered_set<int>();
        for (int i : *a) {
            res->insert(i);
        }
        for (int i : *b) {
            res->insert(i);
        } 
        return res;
    }

    unordered_set<int>* query(int p) {
        unordered_set<int>* ans = new unordered_set<int>();
        point_query(1, 0, n - 1, p, ans);
        return ans;
    }

    void point_query(int node, int currentl, int currentr, int p, unordered_set<int>* ans) {
        if (currentl == currentr) {
            for (int i : *tree[node]) {
                ans->insert(i);
            }
            return;
        }
        int mid = (currentl + currentr) / 2;
        for (int i : *lazy[node]) {
            ans->insert(i);
        }

        if (mid >= p) {
            point_query(node * 2, currentl, mid, p, ans);
        } else {
            point_query(node * 2 + 1, mid + 1, currentr, p, ans);
        }
    }

    void addRange(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

private:
    void update(int node, int currentl, int currentr, int l, int r, int val) {
        if (currentr < l || currentl > r) {
            return;
        }
        int mid = (currentl + currentr) / 2;
        if (currentl >= l && currentr <= r) {
            tree[node]->insert(val);
            if (currentl != currentr) {
                lazy[node]->insert(val);
            }
            return;
        }
        update(node * 2, currentl, mid, l, r, val);
        update(node * 2 + 1, mid + 1, currentr, l, r, val);
        unordered_set<int>* tempptr = tree[node];
        tree[node] = operation(tree[node * 2], tree[node * 2 + 1]);
        delete tempptr;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    union_tree ut(1e6 + 10);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ut.addRange(l, r, i);
    }
    for (int i = 0; i < m; i++) {
        int c;
        cin >> c;
        unordered_set<int> visited;
        for (int j = 0; j < c; j++) {
            int p;
            cin >> p;
            unordered_set<int>* res = ut.query(p);
            for (int i : *res) {
                visited.insert(i);
            }
            delete res;
        }
        cout << visited.size() << '\n';
    }
}

