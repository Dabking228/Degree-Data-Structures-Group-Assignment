#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;



template<>
void Array<transaction>::createArray() {
	cout << "Creating Transaction Array. \t";
	string custId, product, category, price, date, paymentMethod;
	int index = 0;


	ifstream file(this->FILENAME);

	if (!file.good()) {
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
}



// Bubble Sorting

bool Array<transaction>::compareByField(const transaction& a, const transaction& b, int field) {
	switch (field) {
	case 1: return a.custId < b.custId; //good
	case 2: return a.product < b.product; //good
	case 3: return a.category < b.category; // good
	case 4: return a.price < b.price; // good
	case 5: //good
	{
		stringstream ssA(a.date), ssB(b.date);
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
	case 6: return a.paymentMethod < b.paymentMethod;
	default: return false;
	}
}

void Array<transaction>::BubbleSort(int field) {
	if (!this->getClone()) {
		cout << "Please Clone before sorting!" << endl;
	}

	for (int i = 0; i < this->arrayLength - 1; i++) {
		for (int j = 0; j < this->arrayLength - i - 1; j++) {
			if (!this->compareByField(this->typePointer[j], this->typePointer[j + 1], field)) {
				swap(this->typePointer[j], this->typePointer[j + 1]);
			}
		}
	}
}


template class Array<transaction>;



