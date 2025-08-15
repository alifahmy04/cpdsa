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
    int left;
    int right;
    vector<int> elements;
    vector<int> split;
    int low;
    int high;

    node(int low, int high) : left(-1), right(-1), low(low), high(high) {}
};

class wavelet_tree {
    vector<node> tree;
    vector<int> nums;

public:
    wavelet_tree(vector<int>& nums) : nums(nums) {
        int low = nums[0];
        int high = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            low = min(low, nums[i]);
            high = max(high, nums[i]);
        }
        build(-1, low, high);
    }
    
    int build(int parent, int l, int r) {
        int mid = l + r < 0 ? (l + r - 1) >> 1 : (l + r) >> 1;
        tree.emplace_back(node(l, r));
        int current = tree.size() - 1;
        int count = 0;
        int leftLow = INT_MAX; int rightLow = INT_MAX;
        int leftHigh = INT_MIN; int rightHigh = INT_MIN;
        int n = parent == -1 ? nums.size() : tree[parent].elements.size();
        for (int i = 0; i < n; i++) {
            int p = parent == -1 ? i : tree[parent].elements[i];
            if (nums[p] >= l && nums[p] <= r) {
                tree[current].elements.push_back(p);
                if (nums[p] <= mid) {
                    leftLow = min(leftLow, nums[p]);
                    leftHigh = max(leftHigh, nums[p]);
                    count++;
                } else {
                    rightLow = min(rightLow, nums[p]);
                    rightHigh = max(rightHigh, nums[p]);
                }
                tree[current].split.push_back(count);
            }
        }

        if (l == r) {
            tree[current].left = -1;
            tree[current].right = -1;
        } else {
            tree[current].left = build(current, leftLow, leftHigh);
            tree[current].right = build(current, rightLow, rightHigh);
        }
    
        return current;
    }

    int count(int current, int pos, bool ones) {
        if (pos < 0) {
            return 0;
        }
        return ones ? tree[current].split[pos] : (pos + 1) - tree[current].split[pos];
    }

    int countRange(int current, int l, int r, bool ones) {
        return count(current, r, ones) - count(current, l - 1, ones);
    }

    int minMaxQuery(int l, int r, int k, bool findingMin) {
        int current = 0;
        while (true) {
            bool countingOnes = findingMin;
            int range = countRange(current, l, r, countingOnes);
            if (k > range) {
                k -= range;
                countingOnes = !countingOnes;
            }
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;

            int next = countingOnes ? tree[current].left : tree[current].right;
            if (next == -1) {
                break;
            }
            current = next;
        }
        return nums[tree[current].elements[l]];  
    }

    int kthMinimum(int l, int r, int k) {
        return minMaxQuery(l, r, k, true);
    }

    int kthMaximum(int l, int r, int k) {
        return minMaxQuery(l, r, k, false);
    }

    int frequency(int l, int r, int k) {
        int current = 0;
        while (true) {
            int low = tree[current].low;
            int high = tree[current].high;
            int mid = low + high < 0 ? (low + high - 1) >> 1 : (low + high) >> 1;
            bool countingOnes = k <= mid;
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;
            int next = countingOnes ? tree[current].left : tree[current].right;
            if (next == -1) {
                break;
            }
            current = next;
        }
        if (tree[current].low != tree[current].high || tree[current].low != k) {
            return 0;
        }
        return r - l + 1;
    }

    int kthOccurrence(int l, int r, int k, int x) {
        int current = 0;
        while (true) {
            int low = tree[current].low;
            int high = tree[current].high;
            int mid = low + high < 0 ? (low + high - 1) >> 1 : (low + high) >> 1;
            bool countingOnes = x <= mid;
            l = count(current, l - 1, countingOnes);
            r = count(current, r, countingOnes) - 1;
            int next = countingOnes ? tree[current].left : tree[current].right;
            if (next == -1) {
                break;
            }
            current = next;
        }
        if (tree[current].low != x || l + k - 1 < l || l + k - 1 > r) {
            return -1;
        }
        return tree[current].elements[l + k - 1];
    }

    int countGreaterOrLessEquals(int current, int l, int r, int x, bool inclusive) {
        if (current == -1 || tree[current].high < x && inclusive || tree[current].high <= x && !inclusive) {
            return 0;
        }
        if (tree[current].low >= x && inclusive || tree[current].low > x && !inclusive) {
            return r - l + 1;
        }
        int leftL = count(current, l - 1, true); int leftR = count(current, r, true) - 1;
        int rightL = count(current, l - 1, false); int rightR = count(current, r, false) - 1;
        int leftResult = countGreaterOrLessEquals(tree[current].left, leftL, leftR, x, inclusive);
        int rightResult = countGreaterOrLessEquals(tree[current].right, rightL, rightR, x, inclusive);
        return leftResult + rightResult;
    }

    int countGreater(int l, int r, int x) {
        return countGreaterOrLessEquals(0, l, r, x, false);
    }

    int countGreaterEquals(int l, int r, int x) {
        return countGreaterOrLessEquals(0, l, r, x, true);
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