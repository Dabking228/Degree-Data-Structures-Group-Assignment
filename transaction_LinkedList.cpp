#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
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

//dataNode->custId = custId;
//dataNode->product = product;
//dataNode->category = category;
//dataNode->price = stod(price);
//dataNode->date = date;
//dataNode->paymentMethod = paymentMethod;
//
//newnode->_T = dataNode;
//
//return newnode;
//
//template class LinkedList<transaction>;