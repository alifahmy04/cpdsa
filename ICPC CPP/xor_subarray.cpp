#include <bits/stdc++.h>
using namespace std;
#define nl '\n'

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& t) { 
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

    int countGreaterOrLessEquals(node* current, int x, int l, int r, bool inclusive) {
        if (current == nullptr || current->high < x && inclusive || current->high <= x && !inclusive) {
            return 0;
        }
        if (current->low >= x && inclusive || current->low > x && !inclusive) {
            return r - l + 1;
        }
        int leftL = count(current, l - 1, true); int leftR = count(current, r, true) - 1;
        int rightL = count(current, l - 1, false); int rightR = count(current, r, false) - 1;
        int leftResult = countGreaterOrLessEquals(current->left, x, leftL, leftR, inclusive);
        int rightResult = countGreaterOrLessEquals(current->right, x, rightL, rightR, inclusive);
        return leftResult + rightResult;
    }

    int countGreaterEquals(int x, int l, int r) {
        return countGreaterOrLessEquals(root, x, l, r, true);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> xor_prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> xor_prefix[i];
    }
    for (int i = 1; i < n + 1; i++) {
        xor_prefix[i] ^= xor_prefix[i - 1];
    }
    unordered_map<int, int> last_occ;
    last_occ.reserve(n);

    for (int i = 0; i < n + 1; i++) {
        int x = xor_prefix[i];
        if (last_occ.find(x) == last_occ.end()) {
            xor_prefix[i] = -1;
        } else {
            xor_prefix[i] = last_occ[x];
        }
        last_occ[x] = i;
    } 

    wavelet_tree wt(xor_prefix);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << (wt.countGreaterEquals(l - 1, l - 1, r) ? "YES" : "NO") << nl;
    }
}
