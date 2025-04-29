#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "structure.h"
#include "createList.h"
string TransFILENAME = "transactions.csv";
string reviewFILENAME = "reviews.csv";

/*
transaction* Array
transactionNode* LinkedList's Head

getNumberofLines(FILENAME) // return the amount of lines in the file, when skiping header

transactionCreate(TransFILENAME); // reutrn the array of transaction
reviewCreate(reviewFILENAME); // return the array of review

transactionCreateLinked(TransFILENAME); //reutrn the HEAD of the linked list from transaction
reviewCreateLinked(reviewFILENAME); // return the HEAD of linked list from review

deleteAllNode(); // delete all the node based on which HEAD you provided with
*/

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

void showArray() {
	int transNumOfLines = getNumberofLines(TransFILENAME);
	int reviewNumOfLines = getNumberofLines(reviewFILENAME);

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

	int transNumOfLines = getNumberofLines(TransFILENAME);
	int reviewNumOfLines = getNumberofLines(reviewFILENAME);

	//showArray();
	//showLinkedList();


	cout << "finish list i think " << endl;

}