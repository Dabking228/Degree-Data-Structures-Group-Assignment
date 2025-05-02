#include "LinkedList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

template<>
void LinkedList<transaction>::createLinkedList() {
	cout << "Creating Trans Linked List.. \t";
	string custId, product, category, price, date, paymentMethod;

	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with transation file under LinkedList!" << endl;
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

bool LinkedList<transaction>::compareByField(const transaction* nodeA, const transaction* nodeB, int field) {
	switch (field) {
	case 1: return nodeA->custId < nodeB->custId;
	case 2: return nodeA->product < nodeB->product;
	case 3: return nodeA->category < nodeB->category;
	case 4: return nodeA->price < nodeB->price;
	case 5: 
	{
		stringstream ssA(nodeA->date), ssB(nodeB->date);
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
	case 6: return nodeA->paymentMethod < nodeB->paymentMethod;
	default: return false;
	}
}

template class LinkedList<transaction>;