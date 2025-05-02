#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdexcept>
using namespace std;



template<>
int Array<transaction>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
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
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			numOfValidLines++;
		}
		else {
			continue;
		}
	}
	return numOfValidLines;
}


void Array<transaction>::createArray() {
	cout << "Creating Transaction Array... \t";
	string custId, product, category, price, date, paymentMethod;
	int numOfValidLines = getNumOfValidLines(); // Time Complexity = O(N)

	if (numOfValidLines == 0) {
		cout << "No valid transactions found!" << endl;
		return;
	}

	this->typePointer = new transaction[numOfValidLines];

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
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
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			this->typePointer[index] = transaction(custId, product, category, priceStr, date, paymentMethod);
			index++;
		}
		else {
			continue;
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << arrayLength << " valid transactions!" << endl;
}



// Bubble Sorting

bool Array<transaction>::compareByField(const transaction& a, const transaction& b, int field) {
	switch (field) {
	case 1: return a.getCustId() < b.getCustId();
	case 2: return a.getProduct() < b.getProduct();
	case 3: return a.getCategory() < b.getCategory(); 
	case 4: return a.getPrice() < b.getPrice(); 
	case 5: //good
	{
		stringstream ssA(a.getDate()), ssB(b.getDate());
		tm tmA = {};
		tm tmB = {};

		ssA >> get_time(&tmA, "%d/%m/%Y");
		ssB >> get_time(&tmB, "%d/%m/%Y");
		if (ssA.fail() || ssB.fail()) {
			return false;

			cout << "Failed to parse date" << endl;
		}

		//cout << mktime(&tmA) << " | " << mktime(&tmB) << endl;

		return mktime(&tmA) < mktime(&tmB);
	}
	case 6: return a.getPaymentMethod() < b.getPaymentMethod();
	default: return false;
	}
}



template class Array<transaction>;



