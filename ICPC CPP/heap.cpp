#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <ctime>

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

void buildHeap(vector<int>& nums) {
    int n = nums.size() - 1;
    int next;
    for (int i = n / 2; i >= 0; i--) {
        next = i << 1;
        if (nums[next] < nums[next | 1]) {
            next |= 1;
        }
        if (nums[i] < nums[next]) {
            int temp = nums[i];
            nums[i] = nums[next];
            nums[next] = nums[i];
        }
    }
}

void heapify(vector<int>& nums, int i) {
    int x = nums[i];
    int nextChild = i << 1 | 1;
    int n = nums.size();
    while (nextChild < n && (nums[nextChild] > x || nums[nextChild + 1] > x)) {
        if (nextChild + 1 < n && nums[nextChild + 1] > nums[nextChild]) {
            nextChild++;
        }
        nums[i] = nums[nextChild];
        i = nextChild;
        nextChild = i << 1 | 1;
    }
}

void heapSort(vector<int>& nums) {
    heap h;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        h.insert(nums[i]);
    }   
    for (int i = 0; i < n; i++) {
        nums[i] = h.pop();
    }
}
