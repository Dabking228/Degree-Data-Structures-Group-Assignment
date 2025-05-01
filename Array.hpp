#pragma once
#include "structure.hpp"
using namespace std;

template <typename T> class Array {
	string FILENAME;
	int arrayLength;
	T* typePointer {};

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
		if (this->FILENAME == 0 || this->arrayLength == 0) { cout<< "return nullptr, please initliaze before cloning! " return nullptr };
		Array<T>* newArray;
		newArray->FILENAME = this->FILENAME;
		newArray->arrayLength = this->arrayLength;
		newArray->typePointer = new T[this->arrayLength];

		for (int i = 0; i < this->arrayLength; i++) {
			newArray->typePointer[i] = this->typePointer[i];
		}

		return newArray;
	}

};