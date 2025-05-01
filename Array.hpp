#pragma once
#include "structure.hpp"
using namespace std;

template <typename T> class Array {
	string FILENAME;
	int arrayLength;
	T* typePointer {};

	void toggleClone() {
		if (!isClone) {
			isClone = !isClone;
		}
	}

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

};