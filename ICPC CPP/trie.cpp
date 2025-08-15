#include <bits/stdc++.h>
using namespace std;

struct node {
    vector<node*> letters;
    bool end;
    int count;

    node() : letters(26, nullptr), end(false), count(0) {}
};

class aho_corasick_automaton {
    node* root;

public:
    aho_corasick_automaton() : root(new node()) {}

public:
    void update(string s, bool insert) {
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                current->letters[idx] = new node();
            }
            current = current->letters[idx];
            current->count++;
        }
        current->end = insert;
    }

    void insert(string s) {
        update(s, true);
    }

    void erase(string s) {
        update(s, false);
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
};

int main() {
    aho_corasick_automaton t;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }
        string s;
        cin >> s;
        if (x == 0) {
            t.insert(s);
        } else if (x == 1) {
            cout << t.contains(s) << '\n';
        } else if (x == 2) {
            cout << t.checkPrefix(s) << '\n';
        } else {
            t.erase(s);
        }
    }
}