#include <bits/stdc++.h>
using namespace std;

struct node {
    vector<node*> letters;
    bool end;
    int count;

    node() : letters(26, nullptr), end(false), count(0) {}

    ~node() {
        for (node* letter : letters) {
            delete letter;
        }
    }
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
            current->count = current->count + (insert ? 1 : -1);
        }
        current->end = insert;
    }

    void insert(string s) {
        if (contains(s)) return;
        update(s, true);
    }

    void erase(string s) {
        if (!contains(s)) return;
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
};
