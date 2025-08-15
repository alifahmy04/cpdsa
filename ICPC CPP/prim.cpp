#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <cstdint>
#include <unordered_map>
#define nl '\n'
#define ll long long
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
using namespace std;

struct triple {
    int first;
    int second;
    int third;

    triple() {};
    triple(int x, int y, int z) : first(x), second(y), third(z) {};
};

class weighted_edge_cmp {
public:
    bool operator()(const triple& a, const triple& b) {
        return a.third > b.third;
    }
};

std::ostream& operator<<(std::ostream& s, const pair<int, int>& t) { 
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

std::ostream& operator<<(std::ostream& s, const triple& t) { 
    s << "(" << t.first << ", " << t.second << ", " << t.third << ")";
    return s;
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

void prim(vector<vector<pair<int, int>>>& adj, vector<vector<pair<int, int>>>& result) {
    priority_queue<triple, vector<triple>, weighted_edge_cmp> edges;
    vector<bool> visited(adj.size());

    visited[1] = true;
    for (int i = 0; i < adj[1].size(); i++) {
        edges.push(triple(1, adj[1][i].first, adj[1][i].second));
    }
    
    while (!edges.empty()) {
        triple edge = edges.top(); edges.pop();
        if (visited[edge.second]) {
            continue;
        }
        result[edge.first].emplace_back(pair(edge.second, edge.third));
        result[edge.second].emplace_back(pair(edge.first, edge.third));
        visited[edge.second] = true;
        for (int i = 0; i < adj[edge.second].size(); i++) {
            if (visited[adj[edge.second][i].first]) {
                continue;
            }
            edges.push(triple(edge.second, adj[edge.second][i].first, adj[edge.second][i].second));
        }
    }
}

class union_find {
public:
    vector<int> parent;
    vector<int> rank;
    union_find(int n) : parent(n), rank(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (rank[px] >= rank[py]) {
            parent[py] = px;
        } else {
            parent[px] = py;
        }
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }

    void flatten() {
        for (int i = 0; i < parent.size(); i++) {
            find(i);
        }
    }
};

void kruskal(vector<vector<pair<int, int>>>& adj, vector<vector<pair<int, int>>>& result) {
    priority_queue<triple, vector<triple>, weighted_edge_cmp> edges;
    int count = 0;
    union_find uf(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            if (adj[i][j].first > i) {
                edges.push(triple(i, adj[i][j].first, adj[i][j].second));
            }
        }
    }
    while (!edges.empty()) {
        triple edge = edges.top(); edges.pop();
        if (uf.find(edge.first) == uf.find(edge.second)) {
            continue;
        }
        result[edge.first].emplace_back(pair(edge.second, edge.third));
        result[edge.second].emplace_back(pair(edge.first, edge.third));
        uf.join(edge.first, edge.second);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);
    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }
        int y, cost;
        cin >> y >> cost;
        adj[x].emplace_back(pair(y, cost));
        adj[y].emplace_back(pair(x, cost));
    }    
    vector<vector<pair<int, int>>> mst(n);
    kruskal(adj, mst);
    cout << mst << nl;
}
