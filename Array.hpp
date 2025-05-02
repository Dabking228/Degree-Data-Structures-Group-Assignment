#pragma once
#include "structure.hpp"
using namespace std;

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

template <typename T> class Array {
	string FILENAME;
	int arrayLength;
	T* typePointer {};

	void toggleClone() {
		if (!this->isClone) {
			this->isClone= !this->isClone;
		}
	}
	
	bool getClone() {
		return isClone;
	}

	bool compareByField(const T& a, const T& b, int field);

	void BubbleSort(int);

	Array<T>* MergeSort(int);

private:
	bool isClone = false;


public:
	Array(string FILENAME) {
		this->FILENAME = FILENAME;
	}

	~Array() { delete[] typePointer; }

	void createArray();

	T* getArray() {
		return typePointer;
	}

	int getArrayLength() {
		return arrayLength;
	}

	Array<T>* clone() const {
		if (isClone) {
			cout << "Please use the same variable that is assigned." << endl;
			return nullptr;
		} 

		if (FILENAME == "" || this->arrayLength == 0) { cout << "return nullptr, please initliaze before cloning! " << endl; return nullptr; }
		Array<T>* newArray = new Array<T>(this->FILENAME);
		newArray->arrayLength = this->arrayLength;
		newArray->typePointer = new T[this->arrayLength];

		for (int i = 0; i < this->arrayLength; i++) {
			newArray->typePointer[i] = this->typePointer[i];
		}

		newArray->toggleClone();
		return newArray;
	}

	void sortBy(int sortBy, int sortCol) {
		switch (sortBy) {
		case 1:
			 BubbleSort(sortCol);
			break;
		case 2:
			//MergeSort(sortCol);
			break;
		}
		
	}
};