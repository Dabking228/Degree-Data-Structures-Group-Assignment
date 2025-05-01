#include "Array.hpp"
#include <iostream>
#include <string>
using namespace std;

string toLower(const string& input) {
    string result = input;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');
        }
    }
    return result;
}

template <typename T>

Array<T> Array<T>::arrayLinearSearch() {

    string category, keyword;
    cout << "Search in which category? ";
    cin.ignore();
    getline(cin, category);

    if (category.empty()) {
        cout << "Error! Category is empty!" << endl;
        return Array<T>(0);
    }

    cout << "Keyword: ";
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "Error! Keyword is empty!" << endl;
        return Array<T>(0); 
    }

    if (typePointer == nullptr || arrayLength == 0) {
        cout << "Error! Array is empty!" << endl;
        return Array<T>(0); 
    }

    int matchCount = 0;

    try {
        category = toLower(category);
    }
    catch (...) {
        cout << "Invalid category!" << endl;
        return Array<T>(0);
    }

    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && typePointer[i].custId == keyword) ||
            (category == "product" && typePointer[i].product == keyword) ||
            (category == "category" && typePointer[i].category == keyword) ||
            (category == "price" && to_string(typePointer[i].price) == keyword) ||
            (category == "date" && typePointer[i].date == keyword) ||
            (category == "payment method" && typePointer[i].paymentMethod == keyword)) {
            
            ++matchCount;
        }
    }

    // Create a new array to hold matches
    Array<T> resultArray("filtered_results");
    resultArray.arrayLength = matchCount;
    resultArray.typePointer = new T[matchCount];

    int j = 0;
    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && typePointer[i].custId == keyword) ||
            (category == "product" && typePointer[i].product == keyword) ||
            (category == "category" && typePointer[i].category == keyword) ||
            (category == "price" && to_string(typePointer[i].price) == keyword) ||
            (category == "date" && typePointer[i].date == keyword) ||
            (category == "payment method" && typePointer[i].paymentMethod == keyword)) {
            resultArray.typePointer[j++] = typePointer[i];
        }
    }

    const string separator = string(100, '=');

    cout << separator << endl;
    for (int i = 0; i < resultArray.arrayLength; ++i) {
        cout << "CustomerID: " << resultArray.typePointer[i].custId
            << ", Product: " << resultArray.typePointer[i].product 
            << ", Category: " << resultArray.typePointer[i].category 
            << ", Price: " << resultArray.typePointer[i].price 
            << ", Date: " << resultArray.typePointer[i].date 
            << ", Payment Method: " << resultArray.typePointer[i].paymentMethod << endl;
    }
    cout << separator << endl;

    cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl << endl;

    int option;
    cout << "Search again in filtered list? (1: Yes, -1: No): ";
    cin >> option;

    if (option == 1) {
        return resultArray.arrayLinearSearch();
    }
    else {
        return resultArray;
    }
}

template class Array<transaction>;

