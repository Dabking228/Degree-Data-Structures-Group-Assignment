#include "Array.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TrnasFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

enum sortBy {
	BubbleSort = 1,
	MergeSort = 2
};




namespace {
	LinkedList<transaction> _TransactionLinked(TrnasFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TrnasFILENAME);
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

int main() {
	initializeData();

	// i want to dupe the _XY, use that XY for sorting purpose

	Array<transaction>* _transSortCustID = _TransactionArray.clone();
	Array<review>* _reviewSortCustID = _ReviewArray.clone();


	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	/*
	Option 1: keep using the normal enums
	Option 2: convert he enums to class enums, then atleast got type safety
	*/

	_transSortCustID->sortBy(MergeSort, sortColTransaction::trans_custId); //sample for doing sorting for all
	_reviewSortCustID->sortBy(MergeSort, sortColReview::rv_prodId);

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "time take: " << taken.count() << endl;

	for (int i = 0; i < _transSortCustID->getArrayLength(); i++) {
		cout << i << " : " << _transSortCustID->getArray()[i].custId << endl;
	}

	for (int i = 0; i < _reviewSortCustID->getArrayLength(); i++) {
		cout << i << " : " << _reviewSortCustID->getArray()[i].prodId << endl;
	}

	//Array<transaction>* _newArray = _TransactionArray.clone();
	//Array<transaction>* _newnewArray = _newArray->clone();

	//cout << _TransactionLinked.getListLength() << endl;
	//cout << _ReviewLinked.getListLength() << endl;

	//cout << _TransactionArray.getArrayLength() << endl;
	//cout << _ReviewArray.getArrayLength() << endl;
}

