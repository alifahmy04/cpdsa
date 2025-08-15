#include <iostream>
#include <unordered_map>
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <chrono>

#ifdef __GNUC__
    #include <ext/pb_ds/assoc_container.hpp>
    using namespace __gnu_pbds;
    typedef gp_hash_table<int, int> gp_map;
#endif

using namespace std;

void printMemoryUsage(const string& label) {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));

    SIZE_T physMemUsed = memInfo.WorkingSetSize;
    SIZE_T peakMemUsed = memInfo.PeakWorkingSetSize;

    cout << label << ":\n";
    cout << "  Current memory: " << physMemUsed / (1024.0 * 1024) << " MB\n";
    cout << "  Peak memory:    " << peakMemUsed / (1024.0 * 1024) << " MB\n";
    cout << endl;
}

int main() {
    const int N = 10'000'000;

    // unordered_map
    {
        unordered_map<int, int> umap;
        for (int i = 0; i < N; ++i) {
            umap[i] = i;
        }
        printMemoryUsage("unordered_map");
    }

#ifdef __GNUC__
    // gp_hash_table
    {
        gp_map gpmap;
        for (int i = 0; i < N; ++i) {
            gpmap[i] = i;
        }
        printMemoryUsage("gp_hash_table");
    }
#endif

    // raw array
    {
        int* arr = new int[N];
        for (int i = 0; i < N; ++i) {
            arr[i] = i;
        }
        printMemoryUsage("raw array");
        delete[] arr;
    }

    return 0;
}
