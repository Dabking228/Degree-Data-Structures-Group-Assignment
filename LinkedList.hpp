#pragma once
#include "structure.hpp"
#include <chrono>
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

	bool getClone() {
		return isClone;
	}

	bool compareByField(const T* a, const T* b, int field);


	// Bubble Sort
	// Time Complexity: O(N^2)
	// Space Complexity: O(1)
	void BubbleSort(int field) {
		if (!this->getClone()) {
			cout << "Please Clone before sorting!" << endl;
			return;
		}

		if (_NodeHEAD == nullptr) { cout << "Head is nullptr!" << endl; return; }

		bool swapped;
		Node<T>* end = nullptr;
		do {
			swapped = false;
			Node<T>* curr = _NodeHEAD;

			while (curr->nextnode != end) {
				if (!compareByField(curr->_T, curr->nextnode->_T, field)) {
					std::swap(curr->_T, curr->nextnode->_T);
					swapped = true;
				}
				curr = curr->nextnode;
			}

			end = curr;
		} while (swapped);
	}


	// Merge Sort
	// Time Complexity: O(N log N)
	// Space Complexity: O(N)
	void MergeSort(int field, Node<T>* HEAD) {
		if (!this->getClone()) {
			cout << "Please Clone before sorting!" << endl;
			return;
		}

		Node<T>* head = mergeSort(field, HEAD, 0 , 1000);

		_NodeHEAD = head;
		_NodeTAIL = head;

		while (_NodeTAIL->nextnode != nullptr ) {
			_NodeTAIL = _NodeTAIL->nextnode;
		}
	}
private:
	bool isClone = false;

	/*
	Depth is added to prevent stackoverflow
	due to this, using the typical recursive doesnt work as it reaches overflow for 3300+ times on comparing
	hence, replace the merge() from recersive into iterative. This doesnt change the time complexity of O(n log n)
	but the space complexity will change from o(n log n) to o(n) as the merge() iterative only changes the data
	*/

	Node<T>* mergeSort(int field, Node<T>* HEAD, int depth = 0, int maxDepth = 1000 ) {
		if (HEAD == nullptr || HEAD->nextnode == nullptr) {
			return HEAD;
		}

		if (depth > maxDepth) {
			std::cerr << "Max recursion depth reached. MergeSort aborted to prevent stack overflow.\n";
			return HEAD;
		}

		Node<T>* middle = getMiddle(HEAD); // cut nodes in half
		
		Node<T>* nodeLeft = HEAD; 
		Node<T>* nodeRight = middle->nextnode;

		middle->nextnode->prevnode = nullptr; // remove the middle's nextnode's prevnode pointer
		middle->nextnode = nullptr; // remove the middle's nextnode pointer

		nodeLeft = mergeSort(field, nodeLeft, depth + 1, maxDepth);
		nodeRight= mergeSort(field, nodeRight, depth + 1, maxDepth);


		return merge(nodeLeft, nodeRight, field);
	}

	Node<T>* merge(Node<T>* left, Node<T>* right, int field) {
		Node<T>* dummyHead = new Node<T>();
		Node<T>* current = dummyHead;

		while (left && right) {
			if (compareByField(left->_T, right->_T, field)) {
				current->nextnode = left;
				left->prevnode = current;
				left = left->nextnode;
			}
			else {
				current->nextnode = right;
				right->prevnode = current;
				right = right->nextnode;
			}
			current = current->nextnode;
		}

		if (left) {
			current->nextnode = left;
			left->prevnode = current;
		}
		else if (right) {
			current->nextnode = right;
			right->prevnode = current;
		}

		Node<T>* newHead = dummyHead->nextnode;
		if (newHead) newHead->prevnode = nullptr;

		delete dummyHead;
		return newHead;
	}


	Node<T>* getMiddle(Node<T>* HEAD) {
		if (!HEAD) return HEAD;

		Node<T>* slow = HEAD;
		Node<T>* fast = HEAD->nextnode;

		while (fast != nullptr && fast->nextnode != nullptr) {
			slow = slow->nextnode;
			fast = fast->nextnode->nextnode;
		}

		return slow;
	}

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
	Node<T>* createNode(string, string, string, string);
	Node<T>* createNode(T* type) {
		Node<T>* newnode = new Node<T>();
		T* data = new T(*type);

		newnode->_T = type;
		newnode->nextnode = nullptr;
		newnode->prevnode = nullptr;

		return newnode;
	}

	// create the list kekw
	void addEndOfList(Node<T>* node) {
		if (_NodeHEAD == NULL) {
			_NodeHEAD = _NodeCurr = _NodeTAIL = node;
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

		while (curr != nullptr) {
			newList->addEndOfList(newList->createNode(curr->_T));
			newList->addLength();

			curr = curr->nextnode;
		}

		newList->toggleClone();
		return newList;

	}

	void sortBy(int sortBy, int sortCol, bool asce) {
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();

		if (!asce) {
			sortCol += 10;
		}

		switch (sortBy) {
		case 1:
			BubbleSort(sortCol);
			break;
		case 2:
			MergeSort(sortCol,_NodeHEAD);
			break;
		}

		end = chrono::system_clock::now();
		chrono::duration<double> taken = end - start;
		//cout << "Time taken for sorting: " << taken.count() << " seconds" << endl;

	}

	void printList();

	void linearSearch(string category, string keyword);

	void searchAgain(string search);

	void binarySearch(string category, string keyword);

	bool isSortedByCategory(string category, bool& isAscending);

	// For assignment question no.3
	void appendWordInFront(WordNode*& head, const string& word);
	WordNode* extractAllWordsByRating(Node<review>* reviewHead, int ratingInput);
	WordNode* mergeWordNodes(WordNode* left, WordNode* right);
	void splitWordNodes(WordNode* head, WordNode** front, WordNode** back);
	WordNode* mergeSortWordNodes(WordNode* head);
	WordFrequencyNode* countWordFrequency(WordNode* sortedWordHead);
	WordFrequencyNode* mergeWordFrequencyNodes(WordFrequencyNode* left, WordFrequencyNode* right);
	void splitWordFrequencyNodes(WordFrequencyNode* head, WordFrequencyNode** front, WordFrequencyNode** back);
	WordFrequencyNode* mergeSortWordFrequencyNodes(WordFrequencyNode* head);
	void printTop5MostFrequentlyUsedWords(WordFrequencyNode* head);
	void runLinkedListFindingMostFrequentWordInReview(int ratingInput);
};
