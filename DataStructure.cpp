#include <iostream>
#include <fstream>
#include <sstream>
#include "strucuture.h"
#include "createList.h"


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

	//linked list need +1
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
	/*for (int i = 0; i < reviewNumOfLines+1; i++) {
		cout << "prev cust id: " << curr->prevnode->_review->getCustId() << " | next cust id: " << curr->nextnode->_review->getCustId()
			<< "\ncustomer id: " << curr->_review->getCustId()
			<< " | prod id: " << curr->_review->getProdId() << " | rating: " << curr->_review->getRating()
			<< " | text " << curr->_review->getReviewText() << endl;
		curr = pointer;
		pointer = pointer->nextnode;
	}*/
	cout << "finish list i think " << endl;

	/*for (int i = 0; i < transNumOfLines; i++) {
		cout << transPointer[i].custId << ", " << transPointer[i].product << ", " << transPointer[i].catagory << endl;
	}

	for (int i = 0; i < reviewNumOfLines; i++) {
		cout << reviewPointer[i].custId << ", " << reviewPointer[i].prodId << ", " << reviewPointer[i].rating << ", "<<  reviewPointer[i].reviewText << endl;
	}*/

}