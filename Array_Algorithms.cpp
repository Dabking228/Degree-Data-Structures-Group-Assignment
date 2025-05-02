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

void Array<T>::arrayLinearSearch() {

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
            category != "payment method") {
            cout << "Invalid category! Please enter one of: customerid, product, category, price, date, payment method." << endl;
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
    

    if (typePointer == nullptr || arrayLength == 0) {
        cout << "Error! Array is empty!" << endl;
        return; 
    }

    int matchCount = 0;

    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && (*typePointer[i]).getCustId() == keyword) ||
            (category == "product" && (*typePointer[i]).getProduct() == keyword) ||
            (category == "category" && (*typePointer[i]).getCategory() == keyword) ||
            (category == "price" && to_string((*typePointer[i]).getPrice()) == keyword) ||
            (category == "date" && (*typePointer[i]).getDate() == keyword) ||
            (category == "payment method" && (*typePointer[i]).getPaymentMethod() == keyword)) {
            
            ++matchCount;
        }
    }

    //Using old type pointer
    //for (int i = 0; i < arrayLength; ++i) {
    //    if ((category == "customerid" && typePointer[i].custId == keyword) ||
    //        (category == "product" && typePointer[i].product == keyword) ||
    //        (category == "category" && typePointer[i].category == keyword) ||
    //        (category == "price" && to_string(typePointer[i].price) == keyword) ||
    //        (category == "date" && typePointer[i].date == keyword) ||
    //        (category == "payment method" && typePointer[i].paymentMethod == keyword)) {

    //        ++matchCount;
    //    }
    //}

    // Create a new array to hold matches
    Array<T> resultArray("filtered_results");
    resultArray.arrayLength = matchCount;
    resultArray.typePointer = new T*[matchCount]; // change this also

    int j = 0;

    for (int i = 0; i < arrayLength; ++i) {
        if ((category == "customerid" && (*typePointer[i]).getCustId() == keyword) ||
            (category == "product" && (*typePointer[i]).getProduct() == keyword) ||
            (category == "category" && (*typePointer[i]).getCategory() == keyword) ||
            (category == "price" && to_string((*typePointer[i]).getPrice()) == keyword) ||
            (category == "date" && (*typePointer[i]).getDate() == keyword) ||
            (category == "payment method" && (*typePointer[i]).getPaymentMethod() == keyword)) {

            *resultArray.typePointer[j++] = *typePointer[i];
        }
    }

    //Using old type pointer
    //for (int i = 0; i < arrayLength; ++i) {
    //    if ((category == "customerid" && typePointer[i].custId == keyword) ||
    //        (category == "product" && typePointer[i].product == keyword) ||
    //        (category == "category" && typePointer[i].category == keyword) ||
    //        (category == "price" && to_string(typePointer[i].price) == keyword) ||
    //        (category == "date" && typePointer[i].date == keyword) ||
    //        (category == "payment method" && typePointer[i].paymentMethod == keyword)) {

    //        resultArray.typePointer[j++] = typePointer[i];
    //    }
    //}

    const string separator = string(100, '=');

    cout << separator << endl;
    for (int i = 0; i < resultArray.arrayLength; ++i) {
        cout << "CustomerID: " << resultArray.typePointer[i]->getCustId()
            << ", Product: " << resultArray.typePointer[i]->getProduct()
            << ", Category: " << resultArray.typePointer[i]->getCategory()
            << ", Price: " << resultArray.typePointer[i]->getPrice()
            << ", Date: " << resultArray.typePointer[i]->getDate()
            << ", Payment Method: " << resultArray.typePointer[i]->getPaymentMethod() << endl;
    }
    cout << separator << endl;


    //cout << separator << endl;
    //for (int i = 0; i < resultArray.arrayLength; ++i) {
    //    cout << "CustomerID: " << resultArray.typePointer[i].custId
    //        << ", Product: " << resultArray.typePointer[i].product 
    //        << ", Category: " << resultArray.typePointer[i].category 
    //        << ", Price: " << resultArray.typePointer[i].price 
    //        << ", Date: " << resultArray.typePointer[i].date 
    //        << ", Payment Method: " << resultArray.typePointer[i].paymentMethod << endl;
    //}
    //cout << separator << endl;

    cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl << endl;

    int option;

    cout << "Search again in filtered list? (1: Yes, -1: No): ";
    cin >> option;

    while (true) {
        if (option == 1) {
            resultArray.arrayLinearSearch();
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

