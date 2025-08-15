#include <bits/stdc++.h>
#define nl '\n'
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> t) { 
    s << "[";
    for (int i = 0; i < t.size(); i++) {
        s << t[i];
        if (i != t.size() - 1) {
            s << ", ";
        }
    }
    return s << "]";
}

struct node {
    node* left;
    node* right;
    vector<int> elements;
    vector<int> split;
    int low;
    int high;

    node(int low, int high) : left(nullptr), right(nullptr), low(low), high(high) {}
};

class wavelet_tree {
    node* root;
    vector<int> nums;

public:
    wavelet_tree(vector<int>& nums) : nums(nums) {
        int low = nums[0];
        int high = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            low = min(low, nums[i]);
            high = max(high, nums[i]);
        }
        vector<int> dummy(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            dummy[i] = i;
        }
        root = build(dummy, low, high);
    }
    
    node* build(vector<int>& parent, int l, int r) {
        int mid = l + r < 0 ? (l + r - 1) >> 1 : (l + r) >> 1;
        node* current = new node(l, r);
        int count = 0;
        int leftLow = INT_MAX; int rightLow = INT_MAX;
        int leftHigh = INT_MIN; int rightHigh = INT_MIN;
        for (int i = 0; i < parent.size(); i++) {
            if (nums[parent[i]] >= l && nums[parent[i]] <= r) {
                current->elements.push_back(parent[i]);
                if (nums[parent[i]] <= mid) {
                    leftLow = min(leftLow, nums[parent[i]]);
                    leftHigh = max(leftHigh, nums[parent[i]]);
                    count++;
                } else {
                    rightLow = min(rightLow, nums[parent[i]]);
                    rightHigh = max(rightHigh, nums[parent[i]]);
                }
                current->split.push_back(count);
            }
        }

        if (l == r) {
            current->left = nullptr;
            current->right = nullptr;
        } else {
            current->left = build(current->elements, leftLow, leftHigh);
            current->right = build(current->elements, rightLow, rightHigh);
        }
    
        return current;
    }

    int count(node* current, int pos, bool ones) {
        if (pos < 0) {
            return 0;
        }
        return ones ? current->split[pos] : (pos + 1) - current->split[pos];
    }

    int countRange(node* current, int l, int r, bool ones) {
        return count(current, r, ones) - count(current, l - 1, ones);
    }

    int minMaxQuery(int l, int r, int k, bool findingMin) {
        node* current = root;
        while (true) {
            bool countingOnes = findingMin;
            int range = countRange(current, l, r, countingOnes);
            if (k > range) {
                k -= range;
                countingOnes = !countingOnes;
            }
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;

            node* next = countingOnes ? current->left : current->right;
            if (next == nullptr) {
                break;
            }
            current = next;
        }
        return nums[current->elements[l]];  
    }

    int kthMinimum(int l, int r, int k) {
        return minMaxQuery(l, r, k, true);
    }

    int kthMaximum(int l, int r, int k) {
        return minMaxQuery(l, r, k, false);
    }

    int frequency(int l, int r, int k) {
        node* current = root;
        while (true) {
            int low = current->low;
            int high = current->high;
            int mid = low + high < 0 ? (low + high - 1) >> 1 : (low + high) >> 1;
            bool countingOnes = k <= mid;
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;
            node* next = countingOnes ? current->left : current->right;
            if (next == nullptr) {
                break;
            }
            current = next;
        }
        return r - l + 1;
    }

    int kthOccurrence(int l, int r, int k, int x) {
        node* current = root;
        while (true) {
            int low = current->low;
            int high = current->high;
            int mid = low + high < 0 ? (low + high - 1) >> 1 : (low + high) >> 1;
            bool countingOnes = x <= mid;
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;
            node* next = countingOnes ? current->left : current->right;
            if (next == nullptr) {
                break;
            }
            current = next;
        }
        if (current->low != x || l + k - 1 < l || l + k - 1 > r) {
            return -1;
        }
        return current->elements[l + k - 1];
    }

    int countGreaterOrLessEquals(node* current, int l, int r, int x, bool inclusive) {
        if (current == nullptr || current->high < x && inclusive || current->high <= x && !inclusive) {
            return 0;
        }
        if (current->low >= x && inclusive || current->low > x && !inclusive) {
            return r - l + 1;
        }
        int leftL = count(current, l - 1, true); int leftR = count(current, r, true) - 1;
        int rightL = count(current, l - 1, false); int rightR = count(current, r, false) - 1;
        int leftResult = countGreaterOrLessEquals(current->left, leftL, leftR, x, inclusive);
        int rightResult = countGreaterOrLessEquals(current->right, rightL, rightR, x, inclusive);
        return leftResult + rightResult;
    }

    int countGreater(int l, int r, int x) {
        return countGreaterOrLessEquals(root, l, r, x, false);
    }

    int countGreaterEquals(int l, int r, int x) {
        return countGreaterOrLessEquals(root, l, r, x, true);
    }

    int countLess(int l, int r, int x) {
        return r - l + 1 - countGreaterEquals(l, r, x);
    }

    int countLessEquals(int l, int r, int x) {
        return r - l + 1 - countGreater(l, r, x);
    }
};

int main() {
    vector<int> nums = {15, 2, 3, 4};
    wavelet_tree wt(nums);
    while (true) {
        int x;
        cin >> x;
        int k, l, r;
        cin >> k >> l >> r;
        if (x == 0) {
            cout << wt.kthMaximum(k, l, r) << '\n';
        } else if (x == 1) {
            cout << wt.kthMinimum(k, l, r) << '\n';
        } else if (x == 2) {
            cout << wt.frequency(k, l, r) << '\n';
        } else if (x == 3) {
            int y;
            cin >> y;
            cout << wt.kthOccurrence(k, l, r, y) << '\n';
        } else if (x == 4) {
            cout << wt.countGreaterEquals(k, l, r) << '\n';
        } else if (x == 5) {
            cout << wt.countGreater(k, l, r) << '\n';
        } else if (x == 6) {
            cout << wt.countLessEquals(k, l, r) << '\n';
        } else if (x == 7) {
            cout << wt.countLess(k, l, r) << '\n';
        }
    }
}