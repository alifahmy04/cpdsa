#include <bits/stdc++.h>
#define nl '\n'
using namespace std;

class sparse_table {
public:
    int n;
    int layers;
    vector<vector<int>> table;

    sparse_table(vector<int>& elements) : n(elements.size()) {
        layers = log2(elements.size()) + 1;
        table.resize(layers);
        table[0].resize(n);
        for (int i = 0; i < n; i++) {
            table[0][i] = elements[i];
        }
        for (int i = 1; i < layers; i++) {
            int size = n - (1 << i) + 1;
            table[i].resize(size);
            for (int j = 0; j < size; j++) {
                table[i][j] = operation(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int operation(int a, int b) {
        return max(a, b);
    }

    int query(int l, int r) {
        int layer = log2(r - l + 1);
        return operation(table[layer][l], table[layer][r - (1 << layer) + 1]);
    }
};

int main() {
    vector<int> v({1, 2, 3, 4, 5, 6, 7, 8});
    sparse_table st(v);
    for (vector<int>& v : st.table) {
        for (int i : v) {
            cout << i << ' ';
        }
        cout << nl;
    }
    cout << st.query(0, 7);
}