#include "Array.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

template<>
int Array<review>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening review file for Array Creation!" << endl;
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

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
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
		cerr << "Error in opening review file for Array Creation!" << endl;
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

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
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

template class Array<review>;