#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<>
Array<transaction>::Array(string FILENAME) {
	this->FILENAME = FILENAME;
}

void Array<transaction>::createArray() {
	cout << "Creating Transaction Array." << endl;
	string custId, product, category, price, date, paymentMethod;
	int index = 0;


	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with transaction file!" << endl;
		//return nullptr;
	}


	//transaction* transactionList = new transaction[numberOfTransaction];
	//transaction* transactionList = new transaction[index + 1];
	this->typePointer = new transaction[index + 1];


	/*
	idea 1
	create new while, get number, crete array

	idea 2
	create array, if there is new data, create and copy old array + 1, add item


	4183??? shd be 4128
	price got NaN, date got "Invalid Date"
	neeed to filter those out

	*/

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

template class Array<transaction>;



