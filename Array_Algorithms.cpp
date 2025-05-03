#include "Array.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <type_traits>
using namespace std;

// Transactions
/*
template<typename T>
int Array<T>::countMatches(const string& category, const string& keyword) const {
    int matchCount = 0;

    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && typePointer[i].getCustId() == keyword) ||
            (category == "product" && typePointer[i].getProduct() == keyword) ||
            (category == "category" && typePointer[i].getCategory() == keyword) ||
            (category == "price" && to_string(typePointer[i].getPrice()) == keyword) ||
            (category == "date" && typePointer[i].getDate() == keyword) ||
            (category == "paymentmethod" && typePointer[i].getPaymentMethod() == keyword)) {
            ++matchCount;
        }
    }

    return matchCount;
} 

template<typename T>
void Array<T>::printList() const {
    const string separator = string(120, '=');

    cout << separator << endl;
    for (int i = 0; i < arrayLength; ++i) {
        cout << "CustomerID: " << typePointer[i].getCustId()
            << ", Product: " << typePointer[i].getProduct()
            << ", Category: " << typePointer[i].getCategory()
            << ", Price: " << typePointer[i].getPrice()
            << ", Date: " << typePointer[i].getDate()
            << ", Payment Method: " << typePointer[i].getPaymentMethod() << endl;
    }
    cout << separator << endl;
}

template<typename T>
void Array<T>::searchAgain(string search) {
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
                    category != "product" &&
                    category != "category" &&
                    category != "price" &&
                    category != "date" &&
                    category != "paymentmethod") {
                    cout << "Invalid category! Please enter one of: customerId, product, category, price, date, paymentmethod." << endl;
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

template <typename T>
void Array<T>::arrayLinearSearch(string category, string keyword) {

    if (typePointer == nullptr || arrayLength == 0) {
        cout << "Error! Array is empty!" << endl;
        return;
    }

    // Count number of results
    int matchCount = countMatches(category, keyword);

    // Create a new array to hold results
    Array<T> resultArray("filtered_results");
    resultArray.arrayLength = matchCount;
    resultArray.typePointer = new T[matchCount];

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    int j = 0;
    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && typePointer[i].getCustId() == keyword) ||
            (category == "product" && typePointer[i].getProduct() == keyword) ||
            (category == "category" && typePointer[i].getCategory() == keyword) ||
            (category == "price" && to_string(typePointer[i].getPrice()) == keyword) ||
            (category == "date" && typePointer[i].getDate() == keyword) ||
            (category == "paymentmethod" && typePointer[i].getPaymentMethod() == keyword)) {
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


template<typename T>
void Array<T>::arrayBinarySearch(string category, string keyword) {

    if (typePointer == nullptr || arrayLength == 0) {
        cout << "Error! Array is empty!" << endl;
        return;
    }

    int left = 0, right = arrayLength - 1;

    // Count number of results
    int matchCount = countMatches(category, keyword);

    // Create a new array to hold results
    Array<T> resultArray("filtered_results");
    resultArray.arrayLength = matchCount;
    resultArray.typePointer = new T[matchCount];

    int j = 0;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    while (left <= right) {
        int mid = left + (right - left) / 2;

        string midValue;
        if (category == "customerid") midValue = typePointer[mid].getCustId();
        else if (category == "product") midValue = typePointer[mid].getProduct();
        else if (category == "category") midValue = typePointer[mid].getCategory();
        else if (category == "price") midValue = to_string(typePointer[mid].getPrice());
        else if (category == "date") midValue = typePointer[mid].getDate();
        else if (category == "paymentmethod") midValue = typePointer[mid].getPaymentMethod();
        else {
            cout << "Invalid category." << endl;
            return;
        }

        if (midValue == keyword) {
            // Scan to the left
            int i = mid;
            while (i >= 0) {
                string val = (category == "customerid") ? typePointer[i].getCustId() :
                    (category == "product") ? typePointer[i].getProduct() :
                    (category == "category") ? typePointer[i].getCategory() :
                    (category == "price") ? to_string(typePointer[i].getPrice()) :
                    (category == "date") ? typePointer[i].getDate() :
                    typePointer[i].getPaymentMethod();
                if (val == keyword) resultArray.typePointer[j++] = typePointer[i--];
                else break;
            }

            // Scan to the right
            i = mid + 1;
            while (i < arrayLength) {
                string val = (category == "customerid") ? typePointer[i].getCustId() :
                    (category == "product") ? typePointer[i].getProduct() :
                    (category == "category") ? typePointer[i].getCategory() :
                    (category == "price") ? to_string(typePointer[i].getPrice()) :
                    (category == "date") ? typePointer[i].getDate() :
                    typePointer[i].getPaymentMethod();
                if (val == keyword) resultArray.typePointer[j++] = typePointer[i++];
                else break;
            }

            // Continue search left and right of original match to ensure no duplicates missed
            int midLeft = mid - 1, midRight = mid + 1;
            right = midLeft;
            left = midRight;
        }
        else if (midValue < keyword) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    end = chrono::system_clock::now();
    chrono::duration<double> taken = end - start;

    resultArray.printList();

    cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl;
    cout << "Time taken: " << taken.count() << endl << endl;

    resultArray.searchAgain("binary");
}

// Reviews

//template <>
//void Array<review>::arrayLinearSearch(string category, string keyword) {
//
//    if (typePointer == nullptr || arrayLength == 0) {
//        cout << "Error! Array is empty!" << endl;
//        return;
//    }
//
//    // Count number of results
//    //int matchCount = countMatches(category, keyword);
//
//    int matchCount = 0;
//
//    for (int i = 0; i < arrayLength; ++i) {
//        if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
//            (category == "customerid" && typePointer[i].getCustId() == keyword) ||
//            (category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
//            (category == "review" && typePointer[i].getReviewText() == keyword)) {
//            ++matchCount;
//        }
//    }
//
//    // Create a new array to hold results
//    Array<review> resultArray("filtered_results");
//    resultArray.arrayLength = matchCount;
//    resultArray.typePointer = new review[matchCount];
//
//    chrono::time_point<chrono::system_clock> start, end;
//    start = chrono::system_clock::now();
//
//    int j = 0;
//    for (int i = 0; i < arrayLength; ++i) {
//        if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
//            (category == "customerid" && typePointer[i].getCustId() == keyword) ||
//            (category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
//            (category == "review" && typePointer[i].getReviewText() == keyword))  {
//            resultArray.typePointer[j++] = typePointer[i];
//        }
//    }
//
//    end = chrono::system_clock::now();
//    chrono::duration<double> taken = end - start;
//
//    //resultArray.printList();
//
//    const string separator = string(100, '=');
//
//    cout << separator << endl;
//    for (int i = 0; i < arrayLength; ++i) {
//        cout << "ProductID: " << typePointer[i].getProdId()
//            << ", CustomerID: " << typePointer[i].getCustId()
//            << ", Rating: " << to_string(typePointer[i].getRating())
//            << ", Review: " << typePointer[i].getReviewText() << endl;
//    }
//    cout << separator << endl;
//
//    cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl;
//    cout << "Time taken: " << taken.count() << endl << endl;
//
//    //resultArray.searchAgain("linear");
//
//    int option;
//
//    while (true) {
//        cout << "Search again in filtered list? (1: Yes, -1: No): ";
//        cin >> option;
//
//        if (option == 1) {
//
//            string category, keyword;
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//            while (true) {
//                cout << "Enter your Search Category: ";
//                getline(cin, category);
//                category = toLower(category);
//
//
//                if (category.empty()) {
//                    cout << "Error! Category is empty!" << endl;
//                    continue;
//                }
//
//                if (category != "customerid" &&
//                    category != "productid" &&
//                    category != "rating" &&
//                    category != "review") {
//                    cout << "Invalid category! Please enter one of: productId, customerId, rating, review." << endl;
//                    continue;
//                }
//
//                break;
//            }
//
//            while (true) {
//                cout << "Enter your Keyword: ";
//                getline(cin, keyword);
//
//                if (keyword.empty()) {
//                    cout << "Error! Keyword is empty!" << endl;
//                    continue;
//                }
//
//                break;
//            }
//
//            arrayLinearSearch(category, keyword);
//
//            return;
//
//        }
//        else if (option == -1) {
//            return;
//        }
//        else {
//            cout << "Invalid Input!" << endl;
//        }
//    }
//
//    return;
//
//}

template<>
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

template<>
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

template<>
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

template class Array<transaction>;
// template class Array<review>; */
