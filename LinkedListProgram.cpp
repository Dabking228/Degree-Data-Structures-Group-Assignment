#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "structure.h"
#include "CreateLinkedList.h"
#include "array"
string TransFILENAME = "transactions.csv";
string reviewFILENAME = "reviews.csv";

//void deleteAllNode(transactionNode*& HEAD) {
//	transactionNode* curr = HEAD->nextnode;
//	while (curr != HEAD) {
//		transactionNode* next = curr->nextnode;
//		delete curr;
//		curr = next;
//	}
//	delete HEAD;
//	HEAD = NULL;
//}
//
//void deleteAllNode(reviewNode*& HEAD) {
//	reviewNode* curr = HEAD->nextnode;
//	while (curr != HEAD) {
//		reviewNode* next = curr->nextnode;
//		delete curr;
//		curr = next;
//	}
//	delete HEAD;
//	HEAD = NULL;
//}

//void showAllLinkedList() {
//	// Curr = curr node
//	// Pointer = curr's next node
//	transactionNode* TransHEAD = nullptr;
//	reviewNode* ReviewHEAD = nullptr;
//
//	TransHEAD = transactionCreateLinked(TransFILENAME);
//	ReviewHEAD = reviewCreateLinked(reviewFILENAME);
//
//	transactionNode* TransCurr = TransHEAD;
//	transactionNode* TransPointer = TransHEAD->nextnode;
//	reviewNode* curr = ReviewHEAD;
//	reviewNode* pointer = ReviewHEAD->nextnode;
//
//	//loop review
//	while (true) {
//		cout << "prev cust id: " << curr->prevnode->_review->getCustId() << " | next cust id: " << curr->nextnode->_review->getCustId()
//			<< "\ncustomer id: " << curr->_review->getCustId()
//			<< " | prod id: " << curr->_review->getProdId() << " | rating: " << curr->_review->getRating()
//			<< " | text " << curr->_review->getReviewText() << endl;
//		curr = pointer;
//		pointer = pointer->nextnode;
//
//		if (curr->_review->getCustId() == ReviewHEAD->_review->getCustId()) {
//			break;
//		}
//	}
//
//	//loop transaction
//	while (true) {
//		cout << " prev cust id " << TransCurr->prevnode->_transaction->getCustId() << " | next cust id: " << TransCurr->nextnode->_transaction->getCustId()
//			<< "\n customer id: " << TransCurr->_transaction->getCustId()
//			<< " | Cata: " << TransCurr->_transaction->getCategory()
//			<< " | Product: " << TransCurr->_transaction->getProduct()
//			<< " | Price: " << TransCurr->_transaction->getPrice() << endl;
//		TransCurr = TransPointer;
//		TransPointer = TransPointer->nextnode;
//		if (TransCurr->_transaction->getCustId() == TransHEAD->_transaction->getCustId()) {
//			break;
//		}
//	}
//
//	deleteAllNode(TransHEAD);
//	deleteAllNode(ReviewHEAD);
//}

int LListLength(transactionNode* node) {
	int totalNodes = 0;
	transactionNode* curr = node;

	while (curr != nullptr) {
		totalNodes++;
		if (curr->nextnode == nullptr) {
			break;
		}
		curr = curr->nextnode;
	}
	return totalNodes;
}

int LListLength(reviewNode* node) {
	int totalNodes = 0;
	reviewNode* curr = node;

	while (curr != nullptr) {
		totalNodes++;
		if (curr->nextnode == nullptr) {
			break;
		}
		
		curr = curr->nextnode;
		cout << totalNodes << endl;
	}

	return totalNodes;
}

int main() {
	chrono::time_point<chrono::system_clock> Tstart, Tend, Rstart, Rend;

	Tstart = chrono::system_clock::now();
	transactionNode* temp = transactionCreateLinked(TransFILENAME);
	Tend = chrono::system_clock::now();

	chrono::duration<double> Ttaken = Tend - Tstart;
	cout << "time take: " << Ttaken.count() << endl;

	Rstart = chrono::system_clock::now();
	reviewNode* temp2 = reviewCreateLinked(reviewFILENAME);
	Rend = chrono::system_clock::now();

	cout << LListLength(temp2) << endl;

	chrono::duration<double> Rtaken = Rend - Rstart;
	cout << "time take: " << Rtaken.count() << endl;

}