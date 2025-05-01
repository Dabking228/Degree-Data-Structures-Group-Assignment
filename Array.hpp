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

	void createArray();

	T* getArray() {
		return typePointer;
	}

	int getArrayLength() {
		return arrayLength;
	}

	Array<T> arrayLinearSearch();
};