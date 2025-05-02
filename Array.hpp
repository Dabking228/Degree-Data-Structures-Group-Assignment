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


	// Bubble Sort
	// Time Complexity: O(N^2)
	// Space Complexity: O(1)
	void BubbleSort(int field) {
		if (!this->getClone()) {
			cout << "Please Clone before sorting!" << endl;
			return;
		}

		for (int i = 0; i < this->arrayLength - 1; i++) {
			bool swapped = false;
			for (int j = 0; j < this->arrayLength - i - 1; j++) {
				if (!this->compareByField(this->typePointer[j], this->typePointer[j + 1], field)) {
					swap(this->typePointer[j], this->typePointer[j + 1]);
					swapped = true;
				}
			}
			if (!swapped) {
				break;
			}
		}
	}

	// Merge Sort
	// Time Complexity: O(n log n)
	// Space Complexity: O(n)
	void MergeSort(int field, int left, int right) {
		if (!this->getClone()) {
			cout << "Please Clone before sorting!" << endl;
			return;
		}

		if (left < right) {
			int middle = left + (right - left) / 2;

			MergeSort(field, left, middle);
			MergeSort(field, middle + 1, right);

			sort(field, left, middle, right);
		}
		
	}



private:
	bool isClone = false;

	void sort(int field, int left, int middle, int right) {
		int leftNumber = middle - left + 1;
		int rightNumber = right - middle;

		T* typeLeft = new T[leftNumber];
		T* typeRight = new T[rightNumber];

		for (int i = 0; i < leftNumber; ++i) {
			typeLeft[i] = this->typePointer[left + i];
		}
		for (int j = 0; j < rightNumber; ++j) {
			typeRight[j] = this->typePointer[middle + 1 + j];
		}

		int i = 0, j = 0;
		int k = left;

		while (i < leftNumber && j < rightNumber) {
			if (this->compareByField(typeLeft[i], typeRight[j], field)) {
				this->typePointer[k] = typeLeft[i];
				i++;
			}
			else {
				this->typePointer[k] = typeRight[j];
				j++;
			}
			k++;
		}

		while (i < leftNumber) {
			this->typePointer[k] = typeLeft[i];
			i++;
			k++;
		}

		while (j < rightNumber) {
			this->typePointer[k] = typeRight[j];
			j++;
			k++;
		}

	}


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
			MergeSort(sortCol, 0 , this->arrayLength - 1);
			break;	
		}
		
	}
};