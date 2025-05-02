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
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string ratingStr, string reviewText) {
	Node<review>* newnode = new Node<review>();
	review* dataNode = new review(prodId, custId, ratingStr, reviewText);
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	newnode->_T = dataNode;

	return newnode;
}


bool LinkedList<review>::compareByField(const review* nodeA, const review* nodeB, int field) {
	switch (field) {
	case 1: return nodeA->getCustId() < nodeB->getCustId();
	case 2: return nodeA->getProdId() < nodeB->getProdId();
	case 3: return nodeA->getRating() < nodeB->getRating();
	case 4: return nodeA->getReviewText() < nodeB->getReviewText();
	default: return false;
	}
}

template class LinkedList<review>;