#include <bits/stdc++.h>
using namespace std;
#define nl '\n'
int bs(vector<int>& nums, int x) {
    int l = 0;
    int r = nums.size() - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] <= x) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << l << ' ' << r << nl;
}
int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
}