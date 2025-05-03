#include "Array.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <type_traits>
using namespace std;

// Reviews
template<>
void Array<review>::arrayLinearSearch(string category, string keyword) {

    if (typePointer == nullptr || arrayLength == 0) {
        cout << "Error! Array is empty!" << endl;
        return;
    }

    // Count number of results
    int matchCount = countMatches(category, keyword);

    // Create a new array to hold results
    Array<review> resultArray("filtered_results");
    resultArray.arrayLength = matchCount;
    resultArray.typePointer = new review[matchCount];

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    int j = 0;
    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
            (category == "customerid" && typePointer[i].getCustId() == keyword) ||
            (category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
            (category == "review" && typePointer[i].getReviewText() == keyword)) {
            resultArray.typePointer[j++] = typePointer[i];
        }
    }

    end = chrono::system_clock::now();
    chrono::duration<double> taken = end - start;

    resultArray.printList();

    cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl;
    cout << "Time taken: " << taken.count() << endl << endl;

    resultArray.searchAgain("linear");

    return;

}

int Array<review>::countMatches(const string& category, const string& keyword) const {
    int matchCount = 0;

    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
            (category == "customerid" && typePointer[i].getCustId() == keyword) ||
            (category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
            (category == "review" && typePointer[i].getReviewText() == keyword)) {
            ++matchCount;
        }
    }

    return matchCount;
}

void Array<review>::printList() const {
    const string separator = string(100, '=');

    cout << separator << endl;
    for (int i = 0; i < arrayLength; ++i) {
        cout << "ProductID: " << typePointer[i].getProdId()
            << ", CustomerID: " << typePointer[i].getCustId()
            << ", Rating: " << to_string(typePointer[i].getRating())
            << ", Review: " << typePointer[i].getReviewText() << endl;
    }
    cout << separator << endl;
}

void Array<review>::searchAgain(string search) {
    int option;

    while (true) {
        cout << "Search again in filtered list? (1: Yes, -1: No): ";
        cin >> option;

        if (option == 1) {

            string category, keyword;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter your Search Category: ";
                getline(cin, category);
                category = toLower(category);


                if (category.empty()) {
                    cout << "Error! Category is empty!" << endl;
                    continue;
                }

                if (category != "customerid" &&
                    category != "productid" &&
                    category != "rating" &&
                    category != "review") {
                    cout << "Invalid category! Please enter one of: productId, customerId, rating, review." << endl;
                    continue;
                }

                break;
            }

            while (true) {
                cout << "Enter your Keyword: ";
                getline(cin, keyword);

                if (keyword.empty()) {
                    cout << "Error! Keyword is empty!" << endl;
                    continue;
                }

                break;
            }

            if (search == "linear") {
                arrayLinearSearch(category, keyword);
            }
            else if (search == "binary") {
                arrayBinarySearch(category, keyword);
            }

            return;

        }
        else if (option == -1) {
            return;
        }
        else {
            cout << "Invalid Input!" << endl;
        }
    }
}

template class Array<review>;