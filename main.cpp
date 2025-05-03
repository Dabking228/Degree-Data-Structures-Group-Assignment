#include "Array.hpp"
#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TransactionFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

namespace {
	LinkedList<transaction> _TransactionLinked(TransactionFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TransactionFILENAME);
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
	cout << "Time taken: " << taken.count() << endl;
}

void callSearchTransactions(string search) {
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
		else if (search == "linearll")
			_TransactionLinked.linearSearch(category, keyword);
		else
			cout << "Invalid!" << endl;
		
}

void callReviewsSearch(string search) {

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
			category != "productid" &&
			category != "rating" &&
			category != "review") {
			cout << "Invalid category! Please enter one of: customerId, productid, rating, review." << endl;
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
		_ReviewArray.arrayLinearSearch(category, keyword);
	else if (search == "linearll")
		_ReviewLinked.linearSearch(category, keyword);
	else
		cout << "Invalid!" << endl;
}


int main() {
	initializeData();

	while (true) {

		cout << "1. Linear Search Transaction Array" << "\n"
			<< "2. Linear Search Reviews Array" << "\n"
			<< "3. Linear Search Transaction Linked List" << "\n"
			<< "4. Linear Search Reviews Linked List" << "\n" << endl;

		int option;
		cout << "Enter your option (-1 to exit): ";
		cin >> option;

		switch (option) {
		case 1: {
			callSearchTransactions("linear");
		}
		case 2: {
			callReviewsSearch("linear");
			break;
		}
		case 3: {
			callSearchTransactions("linearll");
			break;
		}
		case 4: {
			callReviewsSearch("linearll");
			break;
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



