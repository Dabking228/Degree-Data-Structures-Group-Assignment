#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;


bool isValidTransaction(string custId, string product, string category, string priceStr, string date, string paymentMethod) {
	if (custId.empty() || product.empty() || category.empty() || priceStr.empty() || date.empty() || paymentMethod.empty()) {
		return false;
	}

	try {
		double price = stod(priceStr);

		if (date == "Invalid Date") {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

template<>
int Array<transaction>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error opening transaction file!" << endl;
		return 0;
	}

	string line;
	int numOfValidLines = 0;

	// Skip header
	getline(file, line);

	// Time Complexity: O(N)
	while (getline(file, line)) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;

		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod, ',');

		if (isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			numOfValidLines++;
		}
	}
	return numOfValidLines;
}


void Array<transaction>::createArray() {
	cout << "Creating Transaction Array. \t";
	string custId, product, category, price, date, paymentMethod;
	int numOfValidLines = getNumOfValidLines(); // Time Complexity = O(N)

	if (numOfValidLines == 0) {
		cout << "No valid transactions found!";
		return;
	}

	this->typePointer = new transaction*[numOfValidLines];

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error opening transaction file!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	// Time Complexity: O(N)
	while (getline(file, line) && index < numOfValidLines) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;

		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod, ',');

		if (isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			this->typePointer[index++] = new transaction(custId, product, category, priceStr, date, paymentMethod);
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << index << " valid transactions!" << endl;
}

/*	if (!file.good()) {
		cout << "Something wrong with transaction file!" << endl;
	}

	this->typePointer = new transaction[index + 1];

	while (file.good()) {
		getline(file, custId, ',');
		getline(file, product, ',');
		getline(file, category, ',');
		getline(file, price, ',');
		getline(file, date, ',');
		getline(file, paymentMethod);
		if (custId == "Customer ID") {
			continue;
		}
		if (custId == "" && product == "" && category == "" && price == "" && date == "" && paymentMethod == "") {
			break; // stops when no more records
		}
		if (custId == "" || product == "" || category == "" || price == "" || date == "" || paymentMethod == "") { // data cleaning line
			continue; // skip missing values
		}
		if (isnan(stod(price))) { // check for NaN price value
			continue;
		}
		if (date == "Invalid Date") { // check if the text is invalid date, need to create another checker for invalid date that is NOT written in "Invalid Date"
			continue;
		}

		// TODO: optimize this part of the code, maybe use back idea 1
		transaction* oldtransactionList = this->typePointer;
		this->typePointer = new transaction[index + 1];
		for (int i = 0; i < index; i++) {
			this->typePointer[i] = oldtransactionList[i];
		}
		//cout << index+1 << endl;
		delete[] oldtransactionList;


		//// add item into array
		this->typePointer[index].custId = custId;
		this->typePointer[index].product = product;
		this->typePointer[index].category = category;
		this->typePointer[index].price = stod(price);
		this->typePointer[index].date = date;
		this->typePointer[index].paymentMethod = paymentMethod;

		index++;

	}

	cout << "Transaction Array Created!" << endl;
	this->arrayLength = index;
	//return this->typePointer;

template class Array<transaction>;
*/




