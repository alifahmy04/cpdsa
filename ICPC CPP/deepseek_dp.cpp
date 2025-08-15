#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Weapon {
    int A, B, C;
};

bool compare(const Weapon& x, const Weapon& y) {
    // Determine the order that allows more remaining power when used first
    return (x.B + x.A * y.B) < (y.B + y.A * x.B);
}

int main() {
    int N, P;
    cin >> N >> P;
    vector<Weapon> weapons(N);
    for (int i = 0; i < N; ++i) {
        int A, B, C;
        cin >> A >> B >> C;
        weapons[i] = {A, B, C};
    }

    // Sort weapons based on the derived comparator
    sort(weapons.begin(), weapons.end(), compare);

    const int INF = -1e9;
    vector<int> dp(P + 1, INF);
    dp[P] = 0; // Initial state with full power

    for (const auto& w : weapons) {
        vector<int> tmp = dp; // Copy current states to avoid overwriting

        for (int p = P; p >= 0; --p) {
            if (dp[p] == INF) continue;

            if (p >= w.B) {
                int new_p = (p - w.B) / w.A;
                if (new_p >= 0) {
                    tmp[new_p] = max(tmp[new_p], dp[p] + w.C);
                }
            }
        }

        dp = move(tmp); // Update DP with new states
    }

    int max_damage = *max_element(dp.begin(), dp.end());
    cout << (max_damage > 0 ? max_damage : 0) << endl;

    return 0;
}