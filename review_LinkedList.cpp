#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

template <>
void LinkedList<review>::createLinkedList() {
	cout << "Creating Review Linked List... \t";

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening review file for LinkedList Creation!" << endl;
		return;
	}

	string line;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText);

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
			Node<review>* newnode = this->createNode(prodId, custId, ratingStr, reviewText);
			this->addEndOfList(newnode);
			this->addLength();
		}
		else {
			continue;
		}

	}
	cout << "Successfully loaded " << getListLength() << " valid reviews!" << endl;
}

template<>
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string ratingStr, string reviewText) {
	Node<review>* newnode = new Node<review>();
	review* dataNode = new review(prodId, custId, ratingStr, reviewText);
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	newnode->_T = dataNode;

	return newnode;
}

void LinkedList<review>::printList() {
	const string separator = string(120, '=');

	cout << separator << endl;
	Node<review>* current = _NodeHEAD;
	if (current == nullptr) {
		cout << "List is empty.\n";
		return;
	}

	while (current != nullptr) {
		review* data = current->_T;
		cout << "Product ID: " << data->getProdId()
			<< ", Customer ID: " << data->getCustId()
			<< ", Rating: " << data->getRating()
			<< ", Review: " << data->getReviewText() << endl;
		current = current->nextnode;
	}
	cout << separator << endl;
}

void LinkedList<review>::searchAgain(string search) {
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
void LinkedList<review>::linearSearch(string category, string keyword) {
	Node<review>* current = _NodeHEAD;
	bool found = false;

	// Create a new linked list to store results
	LinkedList<review> results("search_results");

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	while (current != nullptr) {
		bool match = false;

		if (category == "productid" && current->_T->getProdId() == keyword) match = true;
		else if (category == "customerid" && current->_T->getCustId() == keyword) match = true;
		else if (category == "rating" && to_string(current->_T->getRating()) == keyword) match = true;
		else if (category == "review" && current->_T->getReviewText() == keyword) match = true;

		if (match) {
			// Clone the data and add to results list
			Node<review>* matchedNode = results.createNode(current->_T);
			results.addEndOfList(matchedNode);
			results.addLength();
			found = true;
		}

		current = current->nextnode;
	}

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	results.printList();

	cout << "Number of results found: " << results.getListLength() << " out of 3372 entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << endl << endl;

	if (!found) {
		cout << "No matching records found!" << endl;
	}

	results.searchAgain("linear");
}

template class LinkedList<review>;