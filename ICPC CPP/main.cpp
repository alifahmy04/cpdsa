#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define ll long long
#define int long long
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

int op(int a, int b) {
    return a ^ b;
}

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    int block_size = 400;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int block_idx = 0;
    int count = 0;
    vector<int> blocks((n + block_size - 1) / block_size, INT_MAX);
    for (int i = 0; i < n; i++, count++) {
        if (count == block_size) {
            count = 0;
            block_idx++;
        }
        blocks[block_idx] = min(blocks[block_idx], nums[i]);
    }
    for (int qu = 0; qu < q; qu++) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            idx--;
            int block = idx / block_size;
            nums[idx] = val;
            blocks[block] = min(blocks[block], val);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            int block_l = l / block_size;
            int block_r = r / block_size;
            int block_l_start = block_l * block_size;
            int block_r_start = block_r * block_size;
            int ans = INT_MAX;
            if (block_l >= block_r - 1) {
                for (int i = l; i <= r; i++) {
                    ans = min(ans, nums[i]);
                }
            } else {
                int block_l_end = block_l_start + block_size;
                for (int i = l; i < block_l_end; i++) {
                    ans = min(ans, nums[i]);
                }
                for (int i = block_r_start; i <= r; i++) {
                    ans = min(ans, nums[i]);
                }
                for (int i = block_l + 1; i < block_r; i++) {
                    ans = min(ans, blocks[i]);
                }
            }
            cout << ans << nl;
        }
    }
}
