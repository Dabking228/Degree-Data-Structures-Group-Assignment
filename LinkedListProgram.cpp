#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.h"
#include "createList.h"
string TransFILENAME = "transactions_cleaned.csv";
string reviewFILENAME = "reviews_cleaned.csv";

void deleteAllNode(transactionNode* HEAD) {
	transactionNode* curr = HEAD->nextnode;
	while (curr != HEAD) {
		transactionNode* next = curr->nextnode;
		delete curr;
		curr = next;
	}
	delete HEAD;
	HEAD = NULL;
}

void deleteAllNode(reviewNode* HEAD) {
	reviewNode* curr = HEAD->nextnode;
	while (curr != HEAD) {
		reviewNode* next = curr->nextnode;
		delete curr;
		curr = next;
	}
	delete HEAD;
	HEAD = NULL;
}

void showLinkedList() {
	// Curr = curr node
	// Pointer = curr's next node
	transactionNode* TransHEAD = nullptr;
	reviewNode* ReviewHEAD = nullptr;

	TransHEAD = transactionCreateLinked(TransFILENAME);
	ReviewHEAD = reviewCreateLinked(reviewFILENAME);

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

	//loop transaction
	while (true) {
		cout << " prev cust id " << TransCurr->prevnode->_transaction->getCustId() << " | next cust id: " << TransCurr->nextnode->_transaction->getCustId()
			<< "\n customer id: " << TransCurr->_transaction->getCustId()
			<< " | Cata: " << TransCurr->_transaction->getCategory()
			<< " | Product: " << TransCurr->_transaction->getProduct()
			<< " | Price: " << TransCurr->_transaction->getPrice() << endl;
		TransCurr = TransPointer;
		TransPointer = TransPointer->nextnode;
		if (TransCurr->_transaction->getCustId() == TransHEAD->_transaction->getCustId()) {
			break;
		}
	}

	deleteAllNode(TransHEAD);
	deleteAllNode(ReviewHEAD);
}

int main() {

}