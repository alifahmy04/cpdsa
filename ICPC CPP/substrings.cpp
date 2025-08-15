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

struct triple {
    int x;
    int y;
    int z;

    triple() {};
    triple(int x, int y, int z) : x(x), y(y), z(z) {};
};

std::ostream& operator<<(std::ostream& s, const pair<int, int>& t) { 
    s << "(" << t.first << ", " << t.second << ")";
    return s;
}

std::ostream& operator<<(std::ostream& s, const triple& t) { 
    s << "(" << t.x << ", " << t.y << ", " << t.z << ")";
    return s;
}


template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& t) { 
    int last = t.size() - 1;
    s << "[";
    for (int i = 0; i < t.size(); i++) {
        s << t[i];
        if (i != last) {
            s << ", ";
        }
    }
    return s << "]";
}

string arrToString(int* arr, int size) {
    std::ostringstream result;  
    result << "[";              
    for (int i = 0; i < size; ++i) {
        result << arr[i];       
        if (i != size - 1) {
            result << ", ";   
        }
    }
    result << "]";              
    return result.str(); 
}

bool cmp(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

signed main() {
    int hash[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
    while (true) {
        unordered_map<string, int> substrings;
        string s;
        cin >> s;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < s.size() - i + 1; j++) {
                string x = s.substr(j, i);
                if (substrings.find(x) == substrings.end()) {
                    substrings[x] = 1;
                }
                substrings[x] *= hash[j + i - 1];
                substrings[x] %= (int) 1e9 + 7;
            }
        }
        unordered_map<int, int> unhash;
        vector<vector<string>> equivalence;
        int idx = 0;
        for (auto& x : substrings) {
            if (unhash.find(x.second) == unhash.end()) {
                unhash[x.second] = idx++;
                equivalence.emplace_back(vector<string>());
            }
            equivalence[unhash[x.second]].push_back(x.first);
        }
        for (vector<string>& v : equivalence) {
            sort(v.begin(), v.end(), [](string& a, string& b) {
                return a.size() != b.size() ? a.size() < b.size() : a < b;
            });
            cout << v << nl;
        }
        cout << "--------------" << nl;
    }
}