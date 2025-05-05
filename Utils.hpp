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
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*) & pmc, sizeof(pmc))) {
        return pmc.PrivateUsage; // Or pmc.PrivateUsage for more accuracy // returns in bytes
    }
    return 0;
}

#endif