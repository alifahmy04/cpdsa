#include <bits/stdc++.h>
#define nl '\n'
#define ll long long
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
using namespace std;

int periodic_string(string s) {
    int period = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != s[i % period]) {
            period = i + 1;
            while (s.size() % period != 0) {
                period++;
            }
            i = period - 1;
        }
    }
    return period;
}

int periodic_string2(const std::string& s) {
    int n = s.size();
    std::vector<int> pi(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }

    int period = n - pi[n - 1];
    if (n % period == 0) {
        return period;
    }
    return n; 
}

int main() {
    while (true) {
        string s;
        cin >> s;
        if (s == ".") {
            break;
        }
        cout << periodic_string(s) << nl;
    }
}