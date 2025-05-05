#ifndef UTILS
#define UTILS
#define NOMINMAX

#include <iostream>
#include <windows.h>
#include <psapi.h>
using namespace std;

inline string toLower(const string& input) {
    string result;
    for (char c : input) {
        if (isalnum(c)) {
            result += tolower(c);
        }
    }
    return result;
}

inline SIZE_T getCurrentMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize; // returns in bytes
    }
    return 0;
}

#endif