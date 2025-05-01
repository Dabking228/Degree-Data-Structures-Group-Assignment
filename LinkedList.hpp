#pragma once
#include "structure.hpp"
using namespace std;

template <typename T> struct Node {
	Node<T>* prevnode;
	T* _T;
	Node<T>* nextnode;
};

template <typename T> class LinkedList {
	string FILENAME;
	int ListLength;
	Node<T>* _NodeHEAD;
	Node<T>* _NodeCurr;
	Node<T>* _NodeTAIL;

public:
	LinkedList(string FILENAME) {
		this->FILENAME = FILENAME;
	}

	void createLinkedList();

	Node<T>* createNode(string, string, string, string, string, string);
	Node<T>* createNode(string , string , string , string );

	// create the list kekw
	void addEndOfList(Node<T>* node) {
		if (_NodeHEAD == NULL) {
			_NodeHEAD = _NodeCurr =  _NodeTAIL = node;
		}
		else if (_NodeHEAD != NULL) {
			_NodeCurr->nextnode = node;
			node->prevnode = _NodeCurr;
			_NodeTAIL = _NodeCurr = node;
		}
	}

	Node<T>* getHEAD() {
		return _NodeHEAD;
	};

	int getListLength() {
		return ListLength;
	}

	void addLength() {
		ListLength++;
	}
};
