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

class compare {
public:
    bool operator()(const triple& a, const triple& b) {
        return a.first > b.first;
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
    priority_queue<triple, vector<triple>, compare> edges;
    union_find uf(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            edges.push(triple(adj[i][j].first, i, adj[i][j].second));
        }
    }
    while (!edges.empty()) {
        triple edge = edges.top(); edges.pop();
        if (uf.find(edge.second) == uf.find(edge.third)) {
            continue;
        }
        result[edge.second].push_back(pair(edge.first, edge.third));
        result[edge.third].push_back(pair(edge.first, edge.second));
        uf.join(edge.second, edge.third);
    }
}

signed main() {
    union_find uf(10);

    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }

        int y;
        cin >> y;
        cout << "x: " << uf.find(x) << ", y: " << uf.find(y) << ".\n";
        if (uf.find(x) == uf.find(y)) {
            cout << "Same group!\n";
        }
        uf.join(x, y);
    }
    cout << uf.parent << nl;
    uf.find(0);
    cout << uf.parent << nl;
}