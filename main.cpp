#include "Array.hpp"
#include "LinkedList.hpp"
#include "Utils.hpp"
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

/*
* Before sorting, clone from the orignal using .clone()
* then sort the cloned version, during the searching will do the same
* do deconstruct when the user return back to the main menu
* 
* Cloning will create a pointer to the cloned type
* cloning will be:
* Type* Varabile = _AnyOfTheOriginal.clone()
* 
* sorting will be:
* Varaible->sortBy(sorting method, sorting column)
*/

void callSearchTransactions(string search) {
	string category, keyword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		cout << "Enter your Search Category: ";
		//cin >> category;

		if (!(cin >> category)) {
			cout << "Invalid category! Please enter one of: customerId, product, category, price, date, paymentmethod." << endl;
			cin.clear(); // clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
			continue;
		}

		//cin >> category;

		if (category.empty()) {
			cout << "Error! Category is empty!" << endl;
			continue;
		}

		category = toLower(category);

		if (category != "customerid" &&
			category != "product" &&
			category != "category" &&
			category != "price" &&
			category != "date" &&
			category != "paymentmethod") {
			cout << "Invalid category! Please enter one of: customerId, product, category, price, date, paymentmethod." << endl;
			continue;
		}

		break;
	}

	while (true) {
		cout << "Enter your Keyword: ";
		//getline(cin, keyword);

		if (!(cin >> keyword)) {
			cout << "Invalid input! Please enter a string." << endl;
			cin.clear(); // clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
			continue;
		}

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
	else if (search == "binary")
		//_transSortCustID->arrayBinarySearch(category, keyword);
		cout << "Array needs to be sorted first! Try passing the array from sorting";
	else
		cout << "Invalid!" << endl;

}

int main() {
	initializeData();

	// i want to dupe the _XY, use that XY for sorting purpose

	//Array<transaction>* _transSortCustID = _TransactionArray.clone();
	//Array<review>* _reviewSortCustID = _ReviewArray.clone();


	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	//_transSortCustID->sortBy(BubbleSort, sortColTransaction::trans_custId); //sample for doing sorting for all
	//_reviewSortCustID->sortBy(BubbleSort, sortColReview::rv_prodId);

	
	LinkedList<review>* _reviewSort = _ReviewLinked.clone();
	_reviewSort->sortBy(BubbleSort, sortColReview::rv_rating);
	_reviewSort->binarySearch("rating","2");

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "time take: " << taken.count() << endl; 


	while (true) {

		cout << "1. Linear Search Transaction Array" << "\n"
			<< "2. Linear Search Reviews Array" << "\n"
			<< "3. Linear Search Transaction Linked List" << "\n"
			<< "4. Linear Search Reviews Linked List" << "\n"
			<< "5. Binary Search Transaction Array" << "\n" << endl;

		int option;
		cout << "Enter your option (-1 to exit): ";
		cin >> option;

		switch (option) {
		case 1: {
			callSearchTransactions("linear");
			break;
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
		case 5: {
			callSearchTransactions("binary");
			break;
		}
		case -1: {
			return 0;
		}
		}
	}
	

	//for (int i = 0; i < _transSortCustID->getArrayLength(); i++) {
	//	cout << i << " : " << _transSortCustID->getArray()[i].getCustId() << endl;
	//}

	//for (int i = 0; i < _reviewSortCustID->getArrayLength(); i++) {
	//	cout << i << " : " << _reviewSortCustID->getArray()[i].getProdId() << endl;
	//}
}



