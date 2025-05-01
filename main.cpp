#include "Array.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TrnasFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

namespace {
	LinkedList<transaction> _TransactionLinked(TrnasFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TrnasFILENAME);
	Array<review> _ReviewArray(ReviewFILENAME);
}

void initializeData() {
	chrono::time_point<chrono::system_clock> start, end;
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



	//cout << _TransactionLinked.getListLength() << endl;
	//cout << _ReviewLinked.getListLength() << endl;

	//cout << _TransactionArray.getArrayLength() << endl;
	//cout << _ReviewArray.getArrayLength() << endl;
}



