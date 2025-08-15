#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Generate a periodic string by repeating a given base
string generate_periodic_string(const string& base, int repeat_count) {
    string result;
    for (int i = 0; i < repeat_count; i++) {
        result += base;
    }
    return result;
}

// Generate a non-periodic string (e.g. no repeated pattern)
string generate_non_periodic_string(int length) {
    string s;
    for (int i = 0; i < length; i++) {
        s += 'a' + (i % 26); // rotates through 'a' to 'z'
    }
    random_shuffle(s.begin(), s.end());
    return s.substr(0, length);
}

int main() {
    srand(time(0));

    int num_cases = 200;
    cout << num_cases << "\n";

    for (int i = 0; i < num_cases; i++) {
        if (i % 2 == 0) {
            // Generate periodic string
            int base_len = 1 + rand() % 10;
            int repeat = 2 + rand() % 10;
            string base;
            for (int j = 0; j < base_len; j++) {
                base += 'a' + rand() % 3; // only 'a', 'b', 'c' to keep it readable
            }
            string periodic = generate_periodic_string(base, repeat);
            cout << periodic << "\n";
        } else {
            // Generate non-periodic string
            int len = 5 + rand() % 30;
            string non_periodic = generate_non_periodic_string(len);
            cout << non_periodic << "\n";
        }
    }

    return 0;
}
