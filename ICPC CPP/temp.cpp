// #include <iostream>
// #include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <sstream>
// #define nl '\n'
// #define ll long long
// #define int long long
// using namespace std;
//
// //  u, 4, 7, idx
// int memo[2][2][2][14];
//
// int ithDigit(int n, int i, int m) {
//     i = m - i - 1;
//     while (i > 0) {
//         n /= 10;
//         i--;
//     }
//     return n % 10;
// }
//
// int digits(int n) {
//     int ans = 0;
//     while (n > 0) {
//         ans++;
//         n /= 10;
//     }
//     return ans;
// }
//
// int power(int base, int expo) {
//     int res = 1;
//     while (expo > 0) {
//         if (expo & 1)
//             res = res * base;
//         base = base * base;
//         expo >>= 1;
//     }
//     return res;
// }
//
// int dp(int idx, bool up, int s, bool four, bool seven){
//     int length = digits(s);
//     if (idx >= length)
//         return four && seven;
//     if (four && seven)
//         return power(10, length - idx - 1);
//     if (~memo[up][four][seven][idx])
//         return memo[up][four][seven][idx];
//
//     int ub = up ? ithDigit(s, idx, length) : 9;
//     int ans = 0;
//     for(int i = 0; i <= ub; i++){
//         ans += dp(idx + 1, up && i == ub, s, four || i == 4, seven || i == 7);
//     }
//     return memo[up][four][seven][idx] = ans;
// }
//
// void solve() {
//     int K;
//     cin >> K;
//
//     int l = 1, r = 4e12 + 10;
//     int fin_ans = 0;
//     while (l <= r) {
//         int m = (l + r) / 2;
//         memset(memo, -1, sizeof(memo));
//         int check = dp(0, 1, m, 0, 0);
//         if (m - check > K) {
//             r = m - 1;
//             fin_ans = m;
//         } else if (m - check < K) {
//             l = m + 1;
//         } else {
//             fin_ans = m;
//             break;
//         }
//     }
//     int n1 = fin_ans;
//     bool four = false;
//     bool seven = false;
//     while (n1 != 0) {
//         if (n1%10 == 4)
//             four = true;
//         if (n1%10 == 7)
//             seven = true;
//         n1 /= 10;
//     }
//     if (four && seven)
//         fin_ans++;
//     cout << fin_ans << nl;
// }
//
// signed main() {
//     ios_base::sync_with_stdio(false);
//     // freopen("rmq.in", "r", stdin);
//     cout.tie(nullptr);
//     cin.tie(nullptr);
//     int t;
//     cin >> t;
//     while(t-- > 0){
//         solve();
//     }
// }