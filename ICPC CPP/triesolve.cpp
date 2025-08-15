#include <bits/stdc++.h>
using namespace std;

struct node {
    vector<node*> letters;
    string mostOccurring;
    int mostOccurringCount;
    int end;
    int count;

    node() : letters(26, nullptr), mostOccurring(), mostOccurringCount(0), end(0), count(0) {}
};

class aho_corasick_automaton {
    node* root;

public:
    aho_corasick_automaton() : root(new node()) {}

public:
    void insert(string s) {
        node* current = root;
        stack<node*> path;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                current->letters[idx] = new node();
            }
            current = current->letters[idx];
            path.push(current);
            current->count++;
        }
        current->end++;
        int count = current->end;
        while (!path.empty()) {
            node* top = path.top(); path.pop();
            if (top->mostOccurringCount < count || top->mostOccurringCount == count && top->mostOccurring > s) {
                top->mostOccurring = s;
                top->mostOccurringCount = count;
            }
        }
    }

    bool contains(string s) {
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                return false;
            }
            current = current->letters[idx];
        }
        return current->end;
    }

    string checkPrefix(string s) {
        stringstream result;
        queue<char> buffer;
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                break;
            }
            current = current->letters[idx];
            buffer.push((char) tolower(s[i]));
            if (current->end) {
                while (!buffer.empty()) {
                    result << buffer.front(); buffer.pop();
                }
            }
        }
        return result.str();
    }

    int count(string s) {
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                return 0;
            }
            current = current->letters[idx];
        }
        return current->count;
    }

    void longestString(string s) {
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                cout << -1 << '\n';
                return;
            }
            current = current->letters[idx];
        }
        cout << current->mostOccurring << ' ' << current->mostOccurringCount << '\n';
    }
};

int main() {
    cout.tie(nullptr);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n;
    aho_corasick_automaton t;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        t.insert(x);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        string x;
        cin >> x;
        t.longestString(x);
    }
}