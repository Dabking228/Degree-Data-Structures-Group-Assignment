#ifndef UTILS
#define UTILS

#include <iostream>
using namespace std;

inline string toLower(const string& input) {
    string result;
    for (char c : input) {
        result += tolower(c);
    }
    return result;
}

#endif