#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
#define nl '\n'
using namespace std;
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"

std::ostream& operator<<(std::ostream& s, pair<string, string> p) { 
    s << '(' << p.first << ", " << p.second << ')';
    return s;
}

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> t) { 
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

template<typename T>
void shuffle_vector(vector<T>& arr) {
    if (arr.size() <= 1) {
        return;
    }
    int n = arr.size();
    std::mt19937 generator(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < n - 1; i++) {
        std::uniform_int_distribution<> dis(i, n - 1); 
        int random = dis(generator);
        swap(arr[i], arr[random]);
    }
}

void printRandomLines() {
    std::mt19937 generator(static_cast<unsigned>(std::time(nullptr)));
    char letters[3] = {'0', 'O', 'o'};
    std::uniform_int_distribution<> dis(0, 2);
    for (int j = 0; j < 10; j++) {
        stringstream ss;
        for (int i = 0; i < 40; i++) {
            ss << letters[dis(generator)];
        }
        cout << ss.str() << nl;
    }
}

string removeNumber(string s) {
    int i = 0;
    while (i < s.length() && s[i] != ')') {
        i++;
    }
    if (i == s.length()) {
        return s;
    }
    return s.substr(i + 2);
}

string decNumber(string s) {
    string temp = "";
    string temp2 = "";
    int i;
    bool found = false;
    for (i = 0; i < s.length(); i++) {
        if (s[i] == ')') {
            found = true;
        }
        if (found) {
            temp2 += s[i];
        } else {
            temp += s[i];
        }
    }
    int num = stoi(temp) - 1;
    return to_string(num) + temp2;
}

string replaceNumber(string s, int i) {
    string temp = "";
    bool found = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ')') {
            found = true;
        }
        if (found) {
            temp += s[i];
        }
    }
    return to_string(i) + temp;
}

void extractNames(vector<string> s) {
    cout << s << '\n';
    int count = 1;
    for (const string& name : s) {
        string temp1 = "";
        string extractedName = "";
        string temp2 = "";
        int i = 0;
        while (i < name.length() && name[i] != ']') {
            temp1 += name[i];
            i++;
        }
        temp1 += ']';
        i++;
        while (i < name.length() && name[i] != '[') {
            extractedName += name[i];
            i++;
        }
        for (; i < name.length(); i++) {
            temp2 += name[i];
        }
        cout << temp1 + replaceNumber(extractedName, count++) + temp2 << '\n';
    }
}

vector<pair<string, string>> assign(vector<string>& names) {
    vector<string> recipients = names;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<> dis(0.0, 0.99999); 
    unordered_map<string, string> map;
    vector<pair<string, string>> assignments;
    for (int i = 0; i < names.size(); i++) {
        int index;
        while (true) {
            index = (int)(dis(gen) * recipients.size());   
            if (!(map.find(recipients[index]) != map.end() && map[recipients[index]] == names[i] || recipients[index] == names[i])) {
                break;
            }
            if (map.find(recipients[index]) != map.end() && map[recipients[index]] == names[i]) {
                cout << "Chosen recipient is their own santa!\n";
            } else {
                cout << "Chosen recipient is the participant themselves!\n";
            }
            cout << "Reset.\n";
            map.clear();
            recipients = names;
            assignments.clear();
            i = 0;
        }
        assignments.push_back(pair<string, string>(names[i], recipients[index]));
        map[names[i]] = recipients[index];
        recipients.erase(recipients.begin() + index);
    }
    return assignments;
}

vector<int> generateAssignment(int n) {
    vector<int> assignments(n, -1);
    vector<int> permutation(n);
    for (int i = 0; i < n; i++) {
        permutation[i] = i;
    }
    bool success;
    while (true) {
        success = true;
        shuffle_vector(permutation);
        for (int i = 0; i < n; i++) {
            if (permutation[i] == i || assignments[permutation[i]] == i) {
                // if (assignments[permutation[i]] == i) {
                //     cout << "Chosen recipient is their own santa!\n";
                // } else {
                //     cout << "Chosen recipient is the participant themselves!\n";
                // }
                success = false;
                fill(assignments.begin(), assignments.begin() + i, -1);
                // cout << "Reset.\n";
                break;
            }
            assignments[i] = permutation[i];
        }
        if (success) {
            break;
        }
    }
    cout << permutation << '\n';
    return permutation;
}

int dfs(vector<int>& permutation, vector<bool>& visited, int i, int size) {
    if (visited[i]) {
        return size;
    }
    visited[i] = true;
    return dfs(permutation, visited, permutation[i], size + 1);
}

int countComponents(vector<int>& permutation) {
    int n = permutation.size();
    int count = 0;
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            cout << dfs(permutation, visited, i, 0) << '\n';
        }
    }
    return count;
}

vector<pair<string, string>> assign3(vector<string>& names) {
    int n = names.size();
    shuffle_vector(names);
    vector<int> assignment = generateAssignment(n);
    cout << countComponents(assignment) << " components.\n";
    vector<pair<string, string>> pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i] = pair<string, string>(names[i], names[assignment[i]]);
    }
    return pairs;
}

vector<pair<string, string>> assign2(vector<string>& names) {
    vector<pair<string, string>> pairs;
    shuffle_vector(names);
    int n = names.size();
    for (int i = 0; i < n; i++) {
        int next = i == n - 1 ? 0 : i + 1;
        pairs.emplace_back(pair<string, string>(names[i], names[next]));
    }
    return pairs;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    printRandomLines();
}
