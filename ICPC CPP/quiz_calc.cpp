#include <bits/stdc++.h>
using namespace std;
int main() {
    long long num = ((1LL << 42) - 5) >> 1;
    printf("Page number: %X\n", num >> 20);
    printf("Page offset: %X\n", num & 0xFFFFF);

    long long M = (1LL << 42) - 5;
    long long offset1 = num & 0xFFFFF;
    printf("%X\n", offset1 + (8LL << 20));
    cout << num << endl;
}