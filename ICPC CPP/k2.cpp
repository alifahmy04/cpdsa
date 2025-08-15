#include <iostream>
#include <vector>
using namespace std;

void solve(int n, int &x, int &y, int &z) {
    if (n % 3 == 0) {
        x = y = z = n / 3;
    } else if (n % 2 == 0) {
        int m = n / 2;
        int a, b, c;
        solve(m, a, b, c);
        x = a * 2;
        y = b * 2;
        z = c * 2;
    } else {
        x = 1;
        y = (n - 1) / 2;
        z = (n - 1) / 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int x, y, z;
        solve(n, x, y, z);
        cout << x << " " << y << " " << z << "\n";
    }
    return 0;
}