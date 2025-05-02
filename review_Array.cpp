#include "Array.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

bool isValidTransaction(string prodId, string custId, string ratingStr, string reviewText) {
	if (prodId.empty() || custId.empty() || ratingStr.empty() || reviewText.empty()) {
		return false;
	}

	try {
		int rating = stoi(ratingStr);
		return true;
	}
	catch (...) {
		return false;
	}
	return false;
}

template<>
int Array<review>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening review file!" << endl;
		return 0;
	}

	string line;
	int numOfValidLines = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText); // So that review text with comma ',' will not be wrongly cut

		if (isValidTransaction(prodId, custId, ratingStr, reviewText)) {
			numOfValidLines++;
		}
		else {
			continue;
		}
	}
	return numOfValidLines;
}

void Array<review>::createArray() {
	cout << "Creating Review Array... \t";
	string prodId, custId, ratingStr, reviewText;
	int numOfValidLines = getNumOfValidLines();

	if (numOfValidLines == 0) {
		cout << "No valid reviews found!" << endl;
		return;
	}

	this->typePointer = new review[numOfValidLines];

	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening review file!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line) && index < numOfValidLines) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText); // So that review text with comma ',' will not be wrongly cut

		if (isValidTransaction(prodId, custId, ratingStr, reviewText)) {
			this->typePointer[index] = review(prodId, custId, ratingStr, reviewText);
			index++;
		}
		else {
			continue;
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << index << " valid reviews!" << endl;
}

template<>
void Array<review>::searchAgain(string search) {
	int option;

	while (true) {
		cout << "Search again in filtered list? (1: Yes, -1: No): ";
		cin >> option;

		if (option == 1) {

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
					cout << "Invalid category! Please enter one of: productId, customerId, rating, review." << endl;
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

			if (search == "linear") {
				arrayLinearSearch(category, keyword);
			}
			else if (search == "binary") {
				arrayBinarySearch(category, keyword);
			}

			return;

		}
		else if (option == -1) {
			return;
		}
		else {
			cout << "Invalid Input!" << endl;
		}
	}
}


/*	int index = 0;


	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with review file!" << endl;
	}

	this->typePointer = new review[index + 1];

	while (file.good()) {
		getline(file, prodId, ',');
		getline(file, custId, ',');
		getline(file, rating, ',');
		getline(file, reviewText);
		if (prodId == "Product ID") {
			continue;
		}
		if (prodId == "" && custId == "" && rating == "" && reviewText == "") {
			break; // stops when no more records
		}
		if (prodId == "" || custId == "" || rating == "" || reviewText == "") { // data cleaning line
			continue; // skip missing values
		}
		// test if the rating can convert to interger
		try {
			stoi(rating);
		}
		catch (exception& err) {
			continue;
		}

		//TODO: same as the on for transaction, need to optimize
		review* oldReivewList = this->typePointer;
		this->typePointer = new review[index + 1];
		for (int i = 0; i < index; i++) {
			this->typePointer[i] = oldReivewList[i];
		}
		//cout << index + 1 << endl;
		delete[] oldReivewList;

		// array creation
		this->typePointer[index].prodId = prodId;
		this->typePointer[index].custId = custId;
		this->typePointer[index].rating = stoi(rating);
		this->typePointer[index].reviewText = reviewText;

		index++;
	}

	cout << "Review Array Created!" << endl;
	this->arrayLength = index;
}

template class Array<review>;
*/