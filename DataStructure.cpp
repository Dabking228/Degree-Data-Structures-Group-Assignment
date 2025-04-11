#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.h"
#include "createList.h"


/*
Array List is complete
Linked List is complete

provide code block for them to use for thier purpose
*/


int main() {
	string transFileName = "transactions_cleaned.csv";
	string reviewFileName = "reviews_cleaned.csv";

	int transNumOfLines = getNumberofLines(transFileName);
	int reviewNumOfLines = getNumberofLines(reviewFileName);

	// array pointers
	transaction* transPointer = nullptr;
	review* reviewPointer = nullptr;

	// linked list pointer
	transactionNode* TransHEAD = nullptr;
	reviewNode* ReviewHEAD = nullptr;

	// codes goes here
	transPointer = transactionCreate(transFileName, TransHEAD);
	reviewPointer = reviewCreate(reviewFileName);

	TransHEAD = transactionCreateLinked(transFileName);
	ReviewHEAD = reviewCreateLinked(reviewFileName);

	transactionNode* TransCurr = TransHEAD;
	transactionNode* TransPointer = TransHEAD->nextnode;
	reviewNode* curr = ReviewHEAD;
	reviewNode* pointer = ReviewHEAD->nextnode;


	//loop review
	//while (true) {
	//	cout << "prev cust id: " << curr->prevnode->_review->getCustId() << " | next cust id: " << curr->nextnode->_review->getCustId()
	//		<< "\ncustomer id: " << curr->_review->getCustId()
	//		<< " | prod id: " << curr->_review->getProdId() << " | rating: " << curr->_review->getRating()
	//		<< " | text " << curr->_review->getReviewText() << endl;
	//	curr = pointer;
	//	pointer = pointer->nextnode;

	//	if (curr->_review->getCustId() == ReviewHEAD->_review->getCustId()) {		
	//		break;
	//	}
	//}
	
	// loop transaction
	//while (true) {
	//	cout << " prev cust id " << TransCurr->_transaction->getCustId() << " | next cust id: " << TransCurr->nextnode->_transaction->getCustId()
	//		<< "\n customer id: " << TransCurr->_transaction->getCustId()
	//		<< " | Cata: " << TransCurr->_transaction->getCategory()
	//		<< " | Product: " << TransCurr->_transaction->getProduct()
	//		<< " | Price: " << TransCurr->_transaction->getPrice() << endl;
	//	TransCurr = TransPointer;
	//	TransPointer = TransPointer->nextnode;
	//	if (TransCurr->_transaction->getCustId() == TransHEAD->_transaction->getCustId()) {
	//		break;
	//	}
	//}

	cout << "finish list i think " << endl;

	//for (int i = 0; i < transNumOfLines; i++) {
	//	cout << transPointer[i].getCustId() << ", " << transPointer[i].getProduct() << ", " << transPointer[i].getCategory()<< endl;
	//}

	//for (int i = 0; i < reviewNumOfLines; i++) {
	//	cout << reviewPointer[i].getCustId() << ", " << reviewPointer[i].getProdId() << ", " << reviewPointer[i].getRating() << ", "<<  reviewPointer[i].getReviewText() << endl;
	//}

}