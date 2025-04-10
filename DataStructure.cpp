#include <iostream>
#include <fstream>
#include <sstream>
#include "strucuture.h"
#include "createList.h"

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

provide code block for them to use for thier purpose
*/


int main() {
	string transFileName = "transactions_cleaned.csv";
	string reviewFileName = "reviews_cleaned.csv";

	// num of line - 1: to use this number for looping index purpose
	int transNumOfLines = getNumberofLines(transFileName) - 1;
	int reviewNumOfLines = getNumberofLines(reviewFileName) - 1;

	// array pointers
	transaction* transPointer = nullptr;
	review* reviewPointer = nullptr;

	// linked list pointer
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

	reviewNode* curr = ReviewHEAD;
	reviewNode* pointer = ReviewHEAD->nextnode;

	cout << &pointer << endl;

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

	/*for (int i = 0; i < transNumOfLines; i++) {
		cout << transPointer[i].custId << ", " << transPointer[i].product << ", " << transPointer[i].catagory << endl;
	}

	for (int i = 0; i < reviewNumOfLines; i++) {
		cout << reviewPointer[i].custId << ", " << reviewPointer[i].prodId << ", " << reviewPointer[i].rating << ", "<<  reviewPointer[i].reviewText << endl;
	}*/

}