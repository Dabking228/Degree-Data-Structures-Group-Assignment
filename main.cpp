#include "Array.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TransactionFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

enum sortBy {
	BubbleSort = 1,
	MergeSort = 2
};

enum sortColTransaction {
	trans_custId = 1,
	trans_product = 2,
	trans_category = 3,
	trans_price = 4,
	trans_date = 5,
	trans_paymentMethod = 6
};

enum sortColReview {
	rv_custId = 1,
	rv_prodId = 2,
	rv_rating = 3,
	rv_reviewText = 4
};


namespace {
	LinkedList<transaction> _TransactionLinked(TransactionFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TransactionFILENAME);
	Array<review> _ReviewArray(ReviewFILENAME);
}

void initializeData() {
	chrono::time_point<chrono::system_clock> start,end;
	start = chrono::system_clock::now();

	_TransactionLinked.createLinkedList();
	_ReviewLinked.createLinkedList();

	_TransactionArray.createArray();
	_ReviewArray.createArray();

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "time take: " << taken.count() << endl;
}

/*
* Before sorting, clone from the orignal using .clone()
* then sort the cloned version, during the searching will do the same
* do deconstruct when the user return back to the main menu
*/

int main() {
	initializeData();

	// i want to dupe the _XY, use that XY for sorting purpose

	Array<transaction>* _transSortCustID = _TransactionArray.clone();
	Array<review>* _reviewSortCustID = _ReviewArray.clone();


	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	_transSortCustID->sortBy(BubbleSort, sortColTransaction::trans_custId); //sample for doing sorting for all
	_reviewSortCustID->sortBy(BubbleSort, sortColReview::rv_prodId);

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "time take: " << taken.count() << endl;

	for (int i = 0; i < _transSortCustID->getArrayLength(); i++) {
		cout << i << " : " << _transSortCustID->getArray()[i].getCustId() << endl;
	}

	for (int i = 0; i < _reviewSortCustID->getArrayLength(); i++) {
		cout << i << " : " << _reviewSortCustID->getArray()[i].getProdId() << endl;
	}


	//Array<transaction>* _newArray = _TransactionArray.clone();
	//Array<transaction>* _newnewArray = _newArray->clone();

}

