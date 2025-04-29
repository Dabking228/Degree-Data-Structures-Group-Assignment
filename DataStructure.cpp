#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "structure.h"
#include "createList.h"
string TransFILENAME = "transactions.csv";
string reviewFILENAME = "reviews.csv";

transactionNode* createTransNode(string custId, string product, string catagory, string price, string date, string paymentMethod) {
	transactionNode* newnode = new transactionNode;
	transaction _transaction;

	_transaction.custId = custId;
	_transaction.product = product;
	_transaction.catagory = catagory;
	_transaction.price = stod(price);
	_transaction.date = date;
	_transaction.paymentMethod = paymentMethod;

	newnode->prevnode = NULL;
	newnode->_transaction = _transaction;
	newnode->nextnode = NULL;

	return newnode;
}


/*
Array List is complete
Linked List need to create

	transaction* transArray = transactionCreate(TransFILENAME);
	review* reviewArray = reviewCreate(reviewFILENAME);

	for (int i = 0; i < transNumOfLines; i++) {
		cout << transArray[i].getCustId() << ", " << transArray[i].getProduct() << ", " << transArray[i].getCategory()<< endl;
	}

	for (int i = 0; i < reviewNumOfLines; i++) {
		cout << reviewArray[i].getCustId() << ", " << reviewArray[i].getProdId() << ", " << reviewArray[i].getRating() << ", "<< reviewArray[i].getReviewText() << endl;
	}

	delete[] transArray;
	delete[] reviewArray;
}

void showLinkedList() {
	// Curr = curr node
	// Pointer = curr's next node
	transactionNode* TransHEAD = nullptr;
	reviewNode* ReviewHEAD = nullptr;

	// codes goes here
	transPointer = transactionCreate(transFileName, TransHEAD);
	reviewPointer = reviewCreate(reviewFileName);
	// trans
	ReviewHEAD = reviewCreateLinked(reviewFileName);


	cout << transPointer << endl;
	cout << reviewPointer << endl;
	//cout << TransHEAD << endl;
	cout << &ReviewHEAD << endl;

	transactionNode* TransCurr = TransHEAD;
	transactionNode* TransPointer = TransHEAD->nextnode;
	reviewNode* curr = ReviewHEAD;
	reviewNode* pointer = ReviewHEAD->nextnode;

	//loop review
	while (true) {
		cout << "prev cust id: " << curr->prevnode->_review->getCustId() << " | next cust id: " << curr->nextnode->_review->getCustId()
			<< "\ncustomer id: " << curr->_review->getCustId()
			<< " | prod id: " << curr->_review->getProdId() << " | rating: " << curr->_review->getRating()
			<< " | text " << curr->_review->getReviewText() << endl;
		curr = pointer;
		pointer = pointer->nextnode;

		if (curr->_review->getCustId() == ReviewHEAD->_review->getCustId()) {		
			break;
		}
	}

	while (true) {
		if (&pointer == &ReviewHEAD) {
			break;
		}

		cout << "Customer ID: " << curr->_review->custId
			<< " | Prod ID: " << curr->_review->prodId
			<< " | Rating: " << curr->_review->rating
			<< " | Text " << curr->_review->reviewText << endl;
		&curr = &pointer;
		pointer = pointer->nextnode;
	}
	cout << "finish list i think " << endl;


	cout << "finish list i think " << endl;

}