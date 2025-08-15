#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const string& text, const string& pattern) {
    vector<int> pi(pattern.size());
    for (int i = 1; i < pattern.size(); i++) {
        int parent = pi[i - 1];
        while (parent > 0 && pattern[parent] != pattern[i]) {
            parent = pi[parent - 1];
        }
        if (pattern[parent] == pattern[i]) {
            pi[i] = parent + 1;
        } else {
            pi[i] = 0;
        }
        for (int i : pi) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    
    vector<int> result;
    int current = 0;
    for (int i = 0; i < text.size(); i++) {
        while (current > 0 && text[i] != pattern[current]) {
            current = pi[current - 1];
        }
        if (text[i] == pattern[current]) {
            current++;
        }
        if (current == pattern.size()) {
            result.push_back(i - pattern.size() + 1);
            current = pi[current - 1];
        }
    }
    return result;
}

int main() {
    string pattern;
    cin >> pattern;    
    string text;
    cin >> text;
    vector<int> result = kmp(text, pattern);
    for (int i : result) {
        cout << i << " ";
    }
}