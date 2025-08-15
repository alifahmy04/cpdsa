#include <bits/stdc++.h>
using namespace std;
#define nl '\n'
#define int long long

class segment_tree {
public:
    int size = 1;
    vector<int> tree;

public:
    segment_tree() {}

    segment_tree(int n) {
        size = 1 << (int) ceil(log2(n));
        tree.resize(size << 1);
    }

    int operation(int a, int b) {
        return a + b;
    }

    int query(int l, int r) {
        return query(1, l, r, 0, size - 1);
    }

    int query(int currentIndex, int l, int r, int currentl, int currentr) {
        if (currentl >= l && currentr <= r) {
            return tree[currentIndex];
        }
        int mid = (currentl + currentr) >> 1;
        if (mid >= r) {
            return query(currentIndex << 1, l, r, currentl, mid);
        }
        if (mid < l) {
            return query(currentIndex << 1 | 1, l, r, mid + 1, currentr);
        }
        int leftChild = query(currentIndex << 1, l, r, currentl, mid);
        int rightChild = query(currentIndex << 1 | 1, l, r, mid + 1, currentr);
        return operation(leftChild, rightChild);
    }

    void set(int index, int val) {
        tree[index + size] = val;
        index = (index + size) >> 1;
        while (index > 0) {
            tree[index] = operation(tree[index << 1], tree[index << 1 | 1]);
            index >>= 1;
        }
    }

    void add(int index, int val) {
        set(index, tree[index + size] + val);
    }
};

struct node {
    int left;
    int right;
    vector<int> elements;
    segment_tree sums;
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
        tree[current].sums = segment_tree(tree[current].elements.size() + 1);
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

    void addRange(int current, int l, int r, int x, int val) {
        if (current == -1 || tree[current].high < x) {
            return;
        }
        if (tree[current].low >= x) {
            tree[current].sums.add(l, val);
            tree[current].sums.add(r + 1, -val);
        }
        int leftL = count(current, l - 1, true); int leftR = count(current, r, true) - 1;
        int rightL = count(current, l - 1, false); int rightR = count(current, r, false) - 1;
        addRange(tree[current].left, leftL, leftR, x, val);
        addRange(tree[current].right, rightL, rightR, x, val);
    }

    void addRange(int l, int r, int x, int val) {
        addRange(0, l, r, x, val);
    }

    int query(int idx, int k) {
        int l = idx;
        int r = idx;
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
        return tree[current].sums.query(0, l);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    wavelet_tree wt(b);
    for (int qu = 0; qu < q; qu++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, x, val;
            cin >> l >> r >> x >> val;
            l--; r--;
            wt.addRange(l, r, x, val);
        } else {
            int idx;
            cin >> idx;
            idx--;
            int addition = wt.query(idx, b[idx]);
            cout << a[idx] + addition << nl;
        }
    }
}