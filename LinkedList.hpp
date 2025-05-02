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

	void toggleClone() {
		if (!isClone) {
			isClone = !isClone;
		}
	}

private:
	bool isClone = false;

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

		return newnode;
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
		if (isClone) {
			cout << "Please use the same variable that is assigned." << endl;
			return nullptr;
		}

		if (FILENAME == "" || this->ListLength == 0) {
			cout << "Return nullptr, please initialize before cloning!" << endl; 
			return nullptr; 
		}
		LinkedList<T>* newList = new LinkedList<T>(this->FILENAME);
		Node<T>* curr = this->_NodeHEAD;

		while (curr->nextnode != nullptr) {
			newList->addEndOfList(newList->createNode(curr->_T));
			newList->addLength();

			curr = curr->nextnode;
		}

		newList->toggleClone();
		return newList;

	}
};
