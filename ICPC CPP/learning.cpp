#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <cstring>
#include <random>

#define nl '\n'
#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"

using namespace std;

class heap {
public:
    int* nums;
    int n;
    int capacity;

public:
    heap() : nums(new int[16]),  n(0), capacity(16) {}

    int size() {
        return n;
    }
    
    int compare(int& a, int& b) {
        return a < b ? 1 : a == b ? 0 : -1;
    }

    void resize(double factor) {
        int newCapacity = capacity * factor;
        int* newHeap = new int[newCapacity];
        for (int i = 0; i <= n; i++) {
            newHeap[i] = nums[i];
        }

        delete[] nums;
        capacity = newCapacity;
        nums = newHeap;
    }

    void insert(int x) {
        if (n + 1 == capacity) {
            resize(2);
        }

        int i = n + 1;
        while (i > 1 && compare(x, nums[i >> 1]) > 0) {
            nums[i] = nums[i >> 1];
            i >>= 1;
        }

        nums[i] = x;
        n++;
    }

    int pop() {
        if (n == 0) {
            cout << "Empty.\n";
            return INT_MIN;
        }

        if (n * 4 <= capacity && capacity > 16) {
            resize(0.5);
        }   

        int res = nums[1];
        int x = nums[n];
        int i = 1;
        int nextChild = 2;
        while (nextChild <= n && (compare(nums[nextChild], x) > 0 || compare(nums[nextChild | 1], x) > 0)) {
            if ((nextChild | 1) <= n && compare(nums[nextChild | 1], nums[nextChild]) > 0) {
                nextChild |= 1;
            }
            nums[i] = nums[nextChild];
            i = nextChild;
            nextChild = i << 1;
        }
        nums[i] = x;
        n--;
        return res;
    }

    int top() {
        if (n == 0) {
            cout << "Empty.\n";
            return INT_MIN;
        }
        return nums[1];
    }
};

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

void reverse(int* arr, int n) {
    int mid = n >> 1;
    for (int i = 0; i < mid; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

void merge(int l, int r, int end, vector<int>& result) {
    int leftPtr = l, rightPtr = r, resultPtr = 0;
    int size = end - l + 1;
    vector<int> temp(size);
    while (resultPtr < size) {
        if (leftPtr == r || rightPtr < end + 1 && result[rightPtr] < result[leftPtr]) {
            temp[resultPtr++] = result[rightPtr++];
        } else {
            temp[resultPtr++] = result[leftPtr++];
        }
    }
    for (int i = 0; i < size; i++) {
        result[l + i] = temp[i];
    }
}

void insertionSort(vector<int>& arr, int l, int r) {
    for (int i = l; i <= r; i++) {
        int pivot = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > pivot) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = pivot;
    }
}


void heapSort2(vector<int>& nums, int l, int r) {
    heap h;
    int n = nums.size();
    for (int i = l; i <= r; i++) {
        h.insert(nums[i]);
    }   
    for (int i = l; i <= r; i++) {
        nums[i] = h.pop();
    }
}

void mergeSort(int l, int r, vector<int>& arr) {
    int size = r - l + 1;
    if (size < 2) {
        return;
    }

    if (size < 100) {
        heapSort2(arr, l, r);
        return;
    }
    
    int half = (size - 1) >> 1;
    mergeSort(l, l + half, arr);
    mergeSort(l + half + 1, r, arr);
    merge(l, l + half + 1, r, arr);
}

void mergeSort(vector<int>& arr) {
    mergeSort(0, arr.size() - 1, arr);
}

void generateDropConstraint() {
    vector<string> tables;
    vector<string> foreignKeys;
    while (true) {
        string x;
        cin >> x;
        if (x == ".") {
            break;
        }
        tables.push_back(x);
    }
    for (int i = 0; i < tables.size(); i++) {
        string x;
        cin >> x;
        foreignKeys.push_back(x);
    }
    cout << tables.size() << nl;
    for (int i = 0; i < tables.size(); i++) {
        cout << "ALTER TABLE " << tables[i] << " DROP CONSTRAINT " << foreignKeys[i] << nl;
    }
}

void generateDropTable() {
    vector<string> tables;
    while (true) {
        string x;
        cin >> x;
        if (x == ".") {
            break;
        }
        tables.push_back(x);
    }
    for (int i = 0; i < tables.size(); i++) {
        cout << "DELETE FROM TABLE " << tables[i] << nl;
    }
    for (int i = 0; i < tables.size(); i++) {
        cout << "TRUNCATE TABLE " << tables[i] << nl;
    }
}

void quicksort2(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    int pivot = arr[0];
    int count = 0;
    vector<int> smaller;
    vector<int> larger;
    vector<int> equal;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < pivot) {
            smaller.push_back(arr[i]);
        } else if (arr[i] == pivot) {
            equal.push_back(arr[i]);
        } else {
            larger.push_back(arr[i]);
        }
    }
    for (int i = 0; i < equal.size(); i++) {
        arr[i + smaller.size()] = equal[i];
    }
    quicksort2(smaller);
    quicksort2(larger);
    for (int i = 0; i < smaller.size(); i++) {
        arr[i] = smaller[i];
    }
    int offset = smaller.size() + equal.size();
    for (int i = 0; i < larger.size(); i++) {
        arr[i + offset] = larger[i];
    }
}

void quicksort1(vector<int>& arr, int l, int r) {
    if (r <= l) {
        return;
    }

    int pivot = arr[r];
    int count = l;
    for (int i = l; i < r; i++) {
        if (arr[i] < pivot) {
            int temp = arr[i];
            arr[i] = arr[count];
            arr[count] = temp;
            count++;
        }
    }
    arr[r] = arr[count];
    arr[count] = pivot;
    quicksort1(arr, l, count - 1);
    quicksort1(arr, count + 1, r);
}

void quicksort3(vector<int>& arr, int l, int r) {
    if (r <= l) {
        return;
    }

    int pivot = arr[r];
    int count = l;
    for (int i = l; i < r; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[count]);
            count++;
        }
    }
    swap(arr[r], arr[count]);
    quicksort3(arr, l, count - 1);
    quicksort3(arr, count + 1, r);
}

void bubbleDown(int i, int x, int n, vector<int>& nums) {
    int nextChild = i << 1 | 1;
    while (nextChild < n) {
        if (nextChild + 1 < n && nums[nextChild + 1] > nums[nextChild]) {
            nextChild++;
        }
        if (nums[nextChild] <= x) {
            break;
        }
        nums[i] = nums[nextChild];
        i = nextChild;
        nextChild = i << 1 | 1;
    }
    nums[i] = x;
}

void heapify(int i, vector<int>& nums) {
    bubbleDown(i, nums[i], nums.size(), nums);
}

void buildHeap(vector<int>& nums) {
    int n = nums.size() - 1;
    int next;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        heapify(i, nums);
    }
}

int pop(int n, vector<int>& nums) {
    int res = nums[0];
    bubbleDown(0, nums[n - 1], n, nums);
    return res;
}

void heapSort(vector<int>& nums) {
    int n = nums.size();
    buildHeap(nums);
    for (int i = 0; i < n - 1; i++) {
        int temp = nums[0];
        bubbleDown(0, nums[n - 1 - i], n - i, nums);
        nums[n - 1 - i] = temp;
    }
}

void heapSort2(vector<int>& nums) {
    heapSort2(nums, 0, nums.size() - 1);
}

void countSort(vector<int>& nums, int maxVal) {
    int n = nums.size();
    int* count = new int[maxVal + 1];
    memset(count, 0, sizeof(int) * (maxVal + 1));
    for (int i = 0; i < n; i++) {
        count[nums[i]]++;
    }
    int idx = 0;
    for (int i = 0; i < maxVal + 1; i++) {
        for (int j = 0; j < count[i]; j++) {
            nums[idx++] = i;
        }
    }
    delete[] count;
}

void countSort(vector<int>& nums) {
    int n = nums.size();
    int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        maxVal = max(nums[i], maxVal);
    }
    countSort(nums, maxVal);
}

void timSort(vector<int>& arr) {
    int n = arr.size();
    const int RUN_SIZE = 5;

    for (int i = 0; i < arr.size(); i += RUN_SIZE) {
        int end = min(i + RUN_SIZE - 1, n - 1);
        heapSort2(arr);
    }

    for (int runSize = RUN_SIZE; runSize < n; runSize <<= 1) {
        for (int l = 0; l < n; l += (runSize << 1)) {
            int end = min(l + (runSize << 1) - 1, n - 1);
            if (l + runSize < end) {
                merge(l, l + runSize, end, arr);
            }
        }
    }
}

int main() {
    const int N = 1e7; // Size of the vector
    const int MIN_VALUE = 1;
    const int MAX_VALUE = 1e7;

    // Generate random numbers
    std::vector<int> data(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN_VALUE, MAX_VALUE);

    for (int& num : data) {
        num = dis(gen);
    }

    auto start = chrono::high_resolution_clock::now();
    // sort(data.begin(), data.end());
    mergeSort(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "mergeSort execution time: " << duration.count() << " seconds" << endl;

    // auto start = chrono::high_resolution_clock::now();
    // heapSort(data);
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << "heapSort2 execution time: " << duration.count() << " seconds" << endl;
    
    // auto start = chrono::high_resolution_clock::now();
    // heapSort2(data);
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << "heapSort2 execution time: " << duration.count() << " seconds" << endl;

    // start = chrono::high_resolution_clock::now();
    // quicksort3(data, 0, data.size() - 1);
    // end = chrono::high_resolution_clock::now();
    // duration = end - start;
    // cout << "quicksort1 execution time: " << duration.count() << " seconds" << endl;

    // auto start = chrono::high_resolution_clock::now();
    // mergeSort(data);
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << "mergeSort execution time: " << duration.count() << " seconds" << endl;

    
    // auto start = chrono::high_resolution_clock::now();
    // countSort(data, MAX_VALUE);
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << "countSort execution time: " << duration.count() << " seconds" << endl;
}


