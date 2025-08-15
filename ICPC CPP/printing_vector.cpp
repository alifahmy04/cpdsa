#include <iostream>
#include <vector>

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