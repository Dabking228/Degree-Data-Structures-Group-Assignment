#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
using namespace std;

template<>
void LinkedList<transaction>::createLinkedList() {
	cout << "Creating Transaction Linked List... \t";
	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
		return;
	}

	string line;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;
		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			Node<transaction>* newnode = this->createNode(custId, product, category, priceStr, date, paymentMethod);
			this->addEndOfList(newnode);
			this->addLength();
		}
	}
	cout << "Successfully loaded " << getListLength() << " valid transactions!" << endl;

}

template<>
Node<transaction>* LinkedList<transaction>::createNode(string custId, string product, string category, string priceStr, string date, string paymentMethod)
{
	Node<transaction>* newnode = new Node<transaction>();
	transaction* dataNode = new transaction(custId, product, category, priceStr, date, paymentMethod);
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	newnode->_T = dataNode;

	return newnode;
}

void LinkedList<transaction>::printList() {
    const string separator = string(120, '=');

    cout << separator << endl;
    Node<transaction>* current = _NodeHEAD;
    if (current == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    while (current != nullptr) {
        transaction* data = current->_T;
        cout << "Customer ID: " << data->getCustId()
            << ", Product: " << data->getProduct()
            << ", Category: " << data->getCategory()
            << ", Price: " << data->getPrice()
            << ", Date: " << data->getDate()
            << ", Payment Method: " << data->getPaymentMethod() << endl;
        current = current->nextnode;
    }
    cout << separator << endl;
}

void LinkedList<transaction>::searchAgain(string search) {
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
					category != "payment method") {
					cout << "Invalid category! Please enter one of: customerId, product, category, price, date, payment method." << endl;
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
				linearSearch(category, keyword);
			}
			else if (search == "binary") {
				//BinarySearch(category, keyword);
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

template<>
void LinkedList<transaction>::linearSearch(string category, string keyword) {
    Node<transaction>* current = _NodeHEAD;
    bool found = false;

    // Create a new linked list to store results
    LinkedList<transaction> results("search_results");

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    while (current!=nullptr) {
        bool match = false;

        if (category == "customerid" && current->_T->getCustId() == keyword) match = true;
        else if (category == "product" && current->_T->getProduct() == keyword) match = true;
        else if (category == "category" && current->_T->getCategory() == keyword) match = true;
        else if (category == "date" && current->_T->getDate() == keyword) match = true;
        else if (category == "payment method" && current->_T->getPaymentMethod() == keyword) match = true;
        else if (category == "price") {
            try {
                double val = stod(keyword);
                if (current->_T->getPrice() == val) match = true;
            }
            catch (...) {
                cout << "Invalid price format.\n";
                return;
            }
        }

        if (match) {
            // Clone the data and add to results list
            Node<transaction>* matchedNode = results.createNode(current->_T);
            results.addEndOfList(matchedNode);
            results.addLength();
            found = true;
        }

        current = current->nextnode;
    }

    end = chrono::system_clock::now();
    chrono::duration<double> taken = end - start;

    results.printList();

    cout << "Number of results found: " << results.getListLength() << " out of 4128 entries." << endl;
    cout << "Time taken: " << fixed << setprecision(6) << taken.count() << endl << endl;

    if (!found) {
        cout << "No matching records found!" << endl;
    }

	results.searchAgain("linear");
} 

template class LinkedList<transaction>;