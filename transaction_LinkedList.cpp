#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

// Please do not move or reorder the functions

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
				linearSearch(category, keyword);
			}
			else if (search == "binary") {

				int sortField = -1;
				if (category == "customerid") sortField = 1;
				else if (category == "product") sortField = 2;
				else if (category == "category") sortField = 3;
				else if (category == "price") sortField = 4;
				else if (category == "date") sortField = 5;
				else if (category == "paymentmethod") sortField = 6;

				//LinkedList<transaction>* cloned_results = clone();

				//// Check if cloning was successful
				//if (cloned_results == nullptr) {
				//	cout << "Cloning failed! Unable to proceed with binary search." << endl;
				//	return;
				//}

				//cloned_results->sortBy(1, sortField);
				//cloned_results->binarySearch(category, keyword);
				//TELEPORT

				//sortBy(1, sortField);
				binarySearch(category, keyword);

				return;
			}

			return;

		}
		else if (option == -1) {
			cout << "Search cancelled. Returning to menu...";
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
        else if (category == "paymentmethod" && current->_T->getPaymentMethod() == keyword) match = true;
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
			Node<transaction>* matchedNode = new Node<transaction>();
			matchedNode->_T = new transaction(*current->_T);  // deep copy
			matchedNode->nextnode = nullptr;
			matchedNode->prevnode = nullptr;
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

bool LinkedList<transaction>::compareByField(const transaction* nodeA, const transaction* nodeB, int field) {
	switch (field) {
	case 1: return nodeA->getCustId() < nodeB->getCustId();
	case 2: return nodeA->getProduct() < nodeB->getProduct();
	case 3: return nodeA->getCategory() < nodeB->getCategory();
	case 4: return nodeA->getPrice() < nodeB->getPrice();
	case 5: 
	{
		stringstream ssA(nodeA->getDate()), ssB(nodeB->getDate());
		tm tmA = {};
		tm tmB = {};

		ssA >> get_time(&tmA, "%d/%m/%Y");
		ssB >> get_time(&tmB, "%d/%m/%Y");
		if (ssA.fail() || ssB.fail()) {
			return false;

			cout << "Failed to parse date" << endl;
		}

		//cout << mktime(&tmA) << " | " << mktime(&tmB) << endl;

		return mktime(&tmA) < mktime(&tmB);
	}
	case 6: return nodeA->getPaymentMethod() < nodeB->getPaymentMethod();
	// descending
	case 11: return nodeA->getCustId() > nodeB->getCustId();
	case 12: return nodeA->getProduct() > nodeB->getProduct();
	case 13: return nodeA->getCategory() > nodeB->getCategory();
	case 14: return nodeA->getPrice() > nodeB->getPrice();
	case 15:
	{
		stringstream ssA(nodeA->getDate()), ssB(nodeB->getDate());
		tm tmA = {};
		tm tmB = {};

		ssA >> get_time(&tmA, "%d/%m/%Y");
		ssB >> get_time(&tmB, "%d/%m/%Y");
		if (ssA.fail() || ssB.fail()) {
			return false;

			cout << "Failed to parse date" << endl;
		}

		//cout << mktime(&tmA) << " | " << mktime(&tmB) << endl;

		return mktime(&tmA) > mktime(&tmB);
	}
	case 16: return nodeA->getPaymentMethod() > nodeB->getPaymentMethod();
	default: return false;
	}
}

template<>
bool LinkedList<transaction>::isSortedByCategory(string category, bool& isAscending) {
	isAscending = true;
	bool isDescending = true;

	Node<transaction>* curr = _NodeHEAD;
	if (curr == nullptr || curr->nextnode == nullptr) return true;

	while (curr->nextnode != nullptr) {
		string prev, next;

		if (category == "customerid") {
			prev = curr->_T->getCustId();
			next = curr->nextnode->_T->getCustId();
		}
		else if (category == "product") {
			prev = curr->_T->getProduct();
			next = curr->nextnode->_T->getProduct();
		}
		else if (category == "category") {
			prev = curr->_T->getCategory();
			next = curr->nextnode->_T->getCategory();
		}
		else if (category == "price") {
			prev = to_string(curr->_T->getPrice());
			next = to_string(curr->nextnode->_T->getPrice());
		}
		else if (category == "date") {
			prev = curr->_T->getDate();
			next = curr->nextnode->_T->getDate();
		}
		else if (category == "paymentmethod") {
			prev = curr->_T->getPaymentMethod();
			next = curr->nextnode->_T->getPaymentMethod();
		}
		else {
			cout << "Invalid category!" << endl;
			return false;
		}

		if (prev > next) isAscending = false;
		if (prev < next) isDescending = false;

		curr = curr->nextnode;
	}

	return isAscending || isDescending;
}

template<>
void LinkedList<transaction>::binarySearch(string category, string keyword) {
	if (_NodeHEAD == nullptr) {
		cout << "Error! Linked list is empty!" << endl;
		return;
	}

	bool isAscending;
	if (!isSortedByCategory(category, isAscending)) {
		cout << "Error! The list is not sorted by category '" << category << "'." << endl;
		return;
	}

	Node<transaction>* left = _NodeHEAD;
	Node<transaction>* right = _NodeTAIL;
	Node<transaction>* mid = nullptr;
	int matchCount = 0;

	chrono::time_point<chrono::system_clock> begin, finish;
	begin = chrono::system_clock::now();

	while (left != right) {
		// Find the middle node using slow and fast pointer technique
		mid = left;
		Node<transaction>* fast = left;
		while (fast != right && fast->nextnode != right) {
			mid = mid->nextnode;
			fast = fast->nextnode;
			if (fast != right) fast = fast->nextnode;
		}

		string value;
		if (category == "customerid") value = mid->_T->getCustId();
		else if (category == "product") value = mid->_T->getProduct();
		else if (category == "category") value = mid->_T->getCategory();
		else if (category == "price") value = to_string(mid->_T->getPrice());
		else if (category == "date") value = mid->_T->getDate();
		else if (category == "paymentmethod") value = mid->_T->getPaymentMethod();

		if (value == keyword) {
			matchCount = 1;
			break;
		}
		else if ((isAscending && value < keyword) || (!isAscending && value > keyword)) {
			left = mid->nextnode;  // Move left pointer to the right of mid
		}
		else {
			right = mid->prevnode;  // Move right pointer to the left of mid
		}
	}

	if (matchCount == 0) {
		cout << "No results found for '" << keyword << "' in " << category << "." << endl;
		return;
	}

	// Expand left and right from the found mid to get all matching results
	int resultsCount = 1;
	Node<transaction>* start = mid;
	while (start->prevnode != nullptr) {
		string value;
		if (category == "customerid") value = start->prevnode->_T->getCustId();
		else if (category == "product") value = start->prevnode->_T->getProduct();
		else if (category == "category") value = start->prevnode->_T->getCategory();
		else if (category == "price") value = to_string(start->prevnode->_T->getPrice());
		else if (category == "date") value = start->prevnode->_T->getDate();
		else if (category == "paymentmethod") value = start->prevnode->_T->getPaymentMethod();

		if (value == keyword) {
			resultsCount++;
			start = start->prevnode;
		}
		else {
			break;
		}
	}

	Node<transaction>* end = mid;
	while (end->nextnode != nullptr) {
		string value;
		if (category == "customerid") value = end->nextnode->_T->getCustId();
		else if (category == "product") value = end->nextnode->_T->getProduct();
		else if (category == "category") value = end->nextnode->_T->getCategory();
		else if (category == "price") value = to_string(end->nextnode->_T->getPrice());
		else if (category == "date") value = end->nextnode->_T->getDate();
		else if (category == "paymentmethod") value = end->nextnode->_T->getPaymentMethod();

		if (value == keyword) {
			resultsCount++;
			end = end->nextnode;
		}
		else {
			break;
		}
	}

	end = end->nextnode; // Move to the last matching node

	// Print the results
	LinkedList<transaction> resultList("linked_binary_results");
	Node<transaction>* current = start;
	while (current != end) {
		resultList.addEndOfList(resultList.createNode(current->_T));
		resultList.addLength();
		current = current->nextnode;
	}

	// Print the final results and time taken
	resultList.printList();
	cout << "Number of results found: " << resultsCount << " entries " << resultList.getListLength() << endl;

	finish = chrono::system_clock::now();
	chrono::duration<double> taken = finish - begin;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << " seconds" << endl << endl;

	resultList.toggleClone();

	resultList.searchAgain("binary");

}

template class LinkedList<transaction>;