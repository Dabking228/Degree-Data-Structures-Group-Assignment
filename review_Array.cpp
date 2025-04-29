#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<>
Array<review>::Array(string FILENAME) {
	this->FILENAME = FILENAME;
}

void Array<review>::createArray() {
	cout << "Creating Review Array.. " << endl;
	string prodId, custId, rating, reviewText;
	int index = 0;


	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with review file!" << endl;
		//return nullptr;
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
	//return reviewList;
}

template class Array<review>;