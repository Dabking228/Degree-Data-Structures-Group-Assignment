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
	~LinkedList() {
		if (_NodeHEAD == nullptr) {
			return;
		}

		while (_NodeHEAD != nullptr) {
			_NodeCurr = _NodeHEAD->nextnode;
			delete _NodeHEAD;
			_NodeHEAD = _NodeCurr;
		}

		delete _NodeHEAD;
	}

	void createLinkedList();

	Node<T>* createNode(string, string, string, string, string, string);
	Node<T>* createNode(string , string , string , string );
	Node<T>* createNode(T* type) {
		Node<T>* newnode = new Node<T>();
		T* data = new T();
		data = type;

		newnode->_T = type;
		newnode->nextnode = nullptr;
		newnode->prevnode = nullptr;

	}

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

	LinkedList<T>* clone() const {
		if (this->FILENAME == 0 || this->arrayLength == 0) { cout << "return nullptr, please initliaze before cloning! " return nullptr };
		LinkedList<T>* newList;
		newList->FILENAME = this->FILENAME;
		Node<T> curr = this->_NodeHEAD;

		while (curr.nextnode != nullptr) {
			newList->addEndOfList(createNode(curr._T));
			newList->addLength();

			curr = curr.nextnode;
		}

		return newList;

	}
};
