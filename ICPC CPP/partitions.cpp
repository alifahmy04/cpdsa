#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <sstream>
#define nl '\n'
#define ll long long
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

signed main() {
    ios_base::sync_with_stdio(false);
    // freopen("rmq.in", "r", stdin);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<int> left(n);
    vector<int> right(n);
    left[0] = 0;
    right[n - 1] = n - 1;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[left[i - 1]]) {
            left[i] = i;
        } else {
            left[i] = left[i - 1];
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > nums[right[i + 1]]) {
            right[i] = i;
        } else {
            right[i] = right[i + 1];
        }
    }
    int score = INT_MAX;
    for (int i = 1; i < n - 1; i++) {
        score = min(nums[left[i - 1]] + nums[i] + nums[right[i + 1]], score);
    }
    cout << score << nl;
} 
