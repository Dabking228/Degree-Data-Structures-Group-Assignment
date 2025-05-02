#ifndef UTILS
#define UTILS

#include <iostream>
using namespace std;

inline std::string toLower(const std::string& input) {
    std::string result;
    for (char c : input) {
        result += std::tolower(c);
    }
    return result;
}

#endif