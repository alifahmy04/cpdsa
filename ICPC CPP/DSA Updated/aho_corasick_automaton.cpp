#include <bits/stdc++.h>
using namespace std;

struct node {
    vector<node*> letters;
    node* fail;
    vector<int> end;

    node() : letters(26, nullptr), fail(nullptr), end() {}

    ~node() {
        for (node* letter : letters) {
            delete letter;
        }
    }
};

class aho_corasick_automaton {
    int stringCount = 0;
    node* root;

public:
    aho_corasick_automaton() : root(new node()) {}

private:
    void insertHelper(string s) {
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            if (current->letters[idx] == nullptr) {
                current->letters[idx] = new node();
            }
            current = current->letters[idx];
        }
        current->end.push_back(stringCount++);
    }

public:
    void insert(string s) {
        if (contains(s)) return;
        insertHelper(s);
    }

    void buildLinks() {
        root->fail = root;
        queue<node*> q;
        node* parent;
        q.push(root);
        while (!q.empty()) {
            parent = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (parent->letters[i] != nullptr) {
                    node* child = parent->letters[i];
                    child->fail = findLink(parent, 'a' + i);
                    for (int x : child->fail->end) {
                        child->end.push_back(x);
                    }       
                    q.push(child);
                }
            }
        }    
    }

    node* findLink(node* current, char c) {
        if (current == root) {
            return root;
        }
        current = current->fail;
        while (current != root && current->letters[c - 'a'] == nullptr) {
            current = current->fail;
        }
        if (current->letters[c - 'a'] != nullptr) {
            return current->letters[c - 'a'];
        }
        return root;
    }

    vector<pair<int, int>> search(string s) {
        vector<pair<int, int>> result;
        node* current = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = tolower(s[i]) - 'a';
            while (current != root && current->letters[idx] == nullptr) {
                current = current->fail;
            }
            if (current->letters[idx] != nullptr) {
                current = current->letters[idx];
            }
            for (int x : current->end) {
                result.push_back({x, i});
            }
        }
        return result;
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
        return !current->end.empty();
    }
};

int main() {
    aho_corasick_automaton a;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }
        string s;
        if (x == 0) {
            cin >> s;
            a.insert(s);
        } else if (x == 1) {
            a.buildLinks();
        } else if (x == 2) {
            cin >> s;
            vector<pair<int, int>> result = a.search(s);
            for (auto& p : result) {
                cout << p.first << " " << p.second << '\n';
            }
        }
    }
}