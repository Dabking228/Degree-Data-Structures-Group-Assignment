#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
using namespace std;

/*void LL_LinearSearch(const string& field, const string& target) const {
    Node* current = head;
    bool found = false;

    while (current) {
        bool match = false;

        if (field == "custId" && current->custId == target) match = true;
        else if (field == "product" && current->product == target) match = true;
        else if (field == "category" && current->category == target) match = true;
        else if (field == "date" && current->date == target) match = true;
        else if (field == "paymentMethod" && current->paymentMethod == target) match = true;
        else if (field == "price") {
            try {
                double value = stod(target);
                if (current->price == value) match = true;
            }
            catch (...) {
                cerr << "Invalid price format.\n";
                return;
            }
        }

        if (match) {
            cout << "CustomerID: " << node->getCustId()
                << ", Product: " << node->getProduct()
                << ", Category: " << node->getCategory()
                << ", Price: " << node->getPrice()
                << ", Date: " << node->getDate()
                << ", Payment Method: " << node->getPaymentMethod() << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No matching records found for field '" << field << "' with value '" << target << "'.\n";
    }
}*/