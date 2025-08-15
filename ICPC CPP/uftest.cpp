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

class union_find {
public:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    unordered_map<int, int> size;
    int maxSize;
    union_find(const vector<int>& nums) : parent(), size(), maxSize(1) {
        for (int i = 0; i < nums.size(); i++) {
            parent[nums[i]] = nums[i];
            parent[nums[i] + 1] = nums[i] + 1;
            size[nums[i]] = 1;
            size[nums[i] + 1] = 1;
            rank[nums[i]] = 0;
            rank[nums[i] + 1] = 0;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }
    
    int getSize(int x) {
        return size[find(x)];
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return;
        }
        if (rank[px] >= rank[py]) {
            size[px] += size[py];
            parent[py] = px;
            maxSize = max(maxSize, size[px]);
        } else {
            size[py] += size[px];
            parent[px] = py;
            maxSize = max(maxSize, size[py]);
        }
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    union_find uf(nums);
    for (int i : nums) {
        uf.join(i, i + 1);
    }
    cout << uf.maxSize - 1 << '\n';
    for (auto& x : uf.parent) {
        cout << x.first << ' ' << x.second << '\n';
    }
}