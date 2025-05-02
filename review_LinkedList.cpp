#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
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
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string ratingStr,string reviewText) {
	Node<review>* newnode = new Node<review>();
	review* dataNode = new review(prodId, custId, ratingStr, reviewText);
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	newnode->_T = dataNode;

	return newnode;
}

/*
void LinkedList<review>::createLinkedList() {
	cout << "Creating Review Linked List.. \t";
	string prodId, custId, rating, reviewText;

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening review file for LinkedList Creation!" << endl;
	}

	while (file.good()) {
		getline(file, prodId, ',');
		getline(file, custId, ',');
		getline(file, rating, ',');
		getline(file, reviewText);
		if (prodId == "Product ID") {
			continue;
		}
		if (prodId == "" && custId == "" && rating == "" && reviewText == "") {
			break; // stops when no more records
		}
		if (prodId == "" || custId == "" || rating == "" || reviewText == "") { // data cleaning line
			continue; // skip missing values
		}
		// test if the rating can convert to interger
		try {
			stoi(rating);
		}
		catch (exception& err) {
			continue;
		}
		Node<review>* newnode = this->createNode(prodId, custId, rating, reviewText);
		this->addEndOfList(newnode);
		this->addLength();
	}
	cout << "Review Linked List Created!" << endl;
}


template<>
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string rating, string reviewText) {
	Node<review>* newnode = new Node<review>();
	review* dataNode = new review();
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	dataNode->prodId = prodId;
	dataNode->custId = custId;
	dataNode->rating = stoi(rating);
	dataNode->reviewText = reviewText;

	newnode->_T = dataNode;

	return newnode;
}
*/
//template class LinkedList<review>;