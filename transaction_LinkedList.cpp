#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<>
void LinkedList<transaction>::createLinkedList() {
	cout << "Creating Trans Linked List.." << endl;
	string custId, product, category, price, date, paymentMethod;

	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with transation file under LinkedList!" << endl;
		//return nullptr;
	}

	while (file.good()) {
		getline(file, custId, ',');
		getline(file, product, ',');
		getline(file, category, ',');
		getline(file, price, ',');
		getline(file, date, ',');
		getline(file, paymentMethod);
		if (custId == "Customer ID") {
			continue;
		}
		if (custId == "" && product == "" && category == "" && price == "" && date == "" && paymentMethod == "") {
			break; // stops when no more records
		}
		if (custId == "" || product == "" || category == "" || price == "" || date == "" || paymentMethod == "") { // data cleaning line
			continue; // skip missing values
		}
		if (isnan(stod(price))) { // check for NaN price value
			continue;
		}
		if (date == "Invalid Date") { // check if the text is invalid date, need to create another checker for invalid date that is NOT written in "Invalid Date"
			continue;
		}
		
		Node<transaction>* newnode = this->createNode(custId, product, category, price, date, paymentMethod);
		this->addEndOfList(newnode);
		this->addLength();
	}
		cout << "Transaction Array Created!" << endl;

}

template<>
Node<transaction>* LinkedList<transaction>::createNode(string custId, string product, string category, string price, string date, string paymentMethod) 
{
	Node<transaction>* newnode = new Node<transaction>();
	transaction* dataNode = new transaction();
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	dataNode->custId= custId;
	dataNode->product = product;
	dataNode->category = category;
	dataNode->price = stod(price);
	dataNode->date = date;
	dataNode->paymentMethod = paymentMethod;

	newnode->_T = dataNode;
	
	return newnode;
}

template class LinkedList<transaction>;