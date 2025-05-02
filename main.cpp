#include "Array.hpp"
#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TransactionFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

namespace {
	//LinkedList<transaction> _TransactionLinked(TransactionFILENAME);
	//LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TransactionFILENAME);
	Array<review> _ReviewArray(ReviewFILENAME);
}

void initializeData() {
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	//_TransactionLinked.createLinkedList();
	//_ReviewLinked.createLinkedList();

	_TransactionArray.createArray();
	_ReviewArray.createArray();

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "Time taken: " << taken.count() << endl;
}

void callSearch(string search) {
	string category, keyword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		cout << "Enter your Search Category: ";
		getline(cin, category);
		category = toLower(category);

		if (category.empty()) {
			cout << "Error! Category is empty!" << endl;
			continue;
		}

		if (category != "customerid" &&
			category != "product" &&
			category != "category" &&
			category != "price" &&
			category != "date" &&
			category != "payment method") {
			cout << "Invalid category! Please enter one of: customerId, product, category, price, date, payment method." << endl;
			continue;
		}

		break;
	}

	while (true) {
		cout << "Enter your Keyword: ";
		getline(cin, keyword);

		if (keyword.empty()) {
			cout << "Error! Keyword is empty!" << endl;
			continue;
		}

		break;
	}

	if (search == "linear")
		_TransactionArray.arrayLinearSearch(category, keyword);
	else if (search == "binary")
		_TransactionArray.arrayBinarySearch(category, keyword);
	else if (search == "reviews")
		_ReviewArray.arrayLinearSearch(category, keyword);
}

int main() {
	initializeData();

	while (true) {

		int option;
		cout << "Enter 2 to search array, 3 to search linked list, or -1 to exit: ";
		cin >> option;

		switch (option) {
		case 2: {

			callSearch("reviews"); // changed parameter to what you want to test

			break;
		}
		case 3: {
			//callSearch2();
		}
		case -1: {
			return 0;
		}
		}
	}

	//cout << _TransactionLinked.getListLength() << endl;
	//cout << _ReviewLinked.getListLength() << endl;

	//cout << _TransactionArray.getArrayLength() << endl;
	//cout << _ReviewArray.getArrayLength() << endl;
}



