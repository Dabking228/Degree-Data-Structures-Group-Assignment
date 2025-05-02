/*#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <>
void LinkedList<review>::createLinkedList() {
	cout << "Creating Review Linked List.. \t";
	string prodId, custId, rating, reviewText;

	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with review file under LinkedList!" << endl;
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
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string rating,string reviewText) {
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