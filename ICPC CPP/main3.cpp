#include <bits/stdc++.h>
using namespace std;

const int MAX_A = 1e6 + 5;
vector<int> pos[MAX_A];

bool is_missing(int y, int l, int r) {
    if (y < 0) return false;
    const auto& v = pos[y];
    if (v.empty()) return true;
    auto it = lower_bound(v.begin(), v.end(), l);
    return (it == v.end() || *it > r);
}

int compute_mex(int l, int r, int x) {
    int low = 0;
    int high = x + 1;
    int ans = x + 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (mid > MAX_A) break; // Prevent out of bounds
        if (is_missing(mid, l, r)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int find_max_missing(int l, int r, int start, int end) {
    int ans = -1;
    int low = start;
    int high = end;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (mid > MAX_A) break; // Prevent out of bounds
        if (is_missing(mid, l, r)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        pos[A[i]].push_back(i + 1); // Using 1-based index
    }

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        // Check if x is missing
        bool x_missing = is_missing(x, l, r);
        if (x_missing) {
            cout << x << '\n';
            continue;
        }

        // Compute MEX of the subarray
        int mex = compute_mex(l, r, x);

        if (mex > x) {
            cout << -1 << '\n';
        } else {
            // Find the maximum missing in [mex, x-1]
            int y = find_max_missing(l, r, mex, x - 1);
            if (y != -1) {
                cout << y << '\n';
            } else {
                // If no missing in [mex, x-1], return mex itself
                cout << mex << '\n';
            }
        }
    }

    return 0;
}