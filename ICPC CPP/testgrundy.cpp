#include <bits/stdc++.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#define nl '\n'
#define sp ' '
#define int long long
#define ld long double
#define cd complex<double>
#define vi vector<int>

// FFFFFFF    A       M     M
// F         A A      MM   MM
// FFFFF    A   A     M M M M
// F       AAAAAAA    M  M  M
// F       A     A    M     M
// F       A     A    M     M

int compute(int x)
{
    while (x >= 2)
    {
        int k = 0;
        int temp = x;
        while (temp > 1)
        {
            temp >>= 1;
            k++;
        }
        int p = 1 << k;
        int q = p >> 1;
        int r = x - p;
        if (r < q)
        {
            return r + q;
        }
        x = r;
    }
    return 0;
}

void solve(int t)
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans ^= compute(nums[i]);
    }
    cout << (ans ? "First" : "Second") << nl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int testcases = 1;
    cin >> testcases;
    while (testcases-- > 0)
    {
        solve(testcases);
    }
    return 0;
}
