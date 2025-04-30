#include "Array.hpp"
#include "LinkedList.hpp"
#include <iostream>
using namespace std;
string TrnasFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";


int main() {
	LinkedList<transaction> _TransactionLinked(TrnasFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	_TransactionLinked.createLinkedList();
	_ReviewLinked.createLinkedList();


	cout << _TransactionLinked.getListLength() << endl;
	cout << _ReviewLinked.getListLength() << endl;
	 
	 
	Array<transaction> _Transaction(TrnasFILENAME);
	Array<review> _Review(ReviewFILENAME);

	// initialize this
	_Transaction.createArray();
	_Review.createArray();
	//transaction* arrayTransaction = _Transaction.getArray();
	//review* arrayReview = _Review.getArray();

	cout << _Transaction.getArrayLength() << endl;
	cout << _Review.getArrayLength() << endl;
}

