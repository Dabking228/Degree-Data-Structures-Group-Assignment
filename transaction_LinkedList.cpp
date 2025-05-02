#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
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
	default: return false;
	}
}

template class LinkedList<transaction>;