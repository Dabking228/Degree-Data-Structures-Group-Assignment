#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

template <>
void LinkedList<review>::createLinkedList() {
	cout << "Creating Review Linked List... \t";

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening review file for LinkedList Creation!" << endl;
		return;
	}

	string line;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText);

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
			Node<review>* newnode = this->createNode(prodId, custId, ratingStr, reviewText);
			this->addEndOfList(newnode);
			this->addLength();
		}
		else {
			continue;
		}

	}
	cout << "Successfully loaded " << getListLength() << " valid reviews!" << endl;
}

template<>
Node<review>* LinkedList<review>::createNode(string prodId, string custId, string ratingStr, string reviewText) {
	Node<review>* newnode = new Node<review>();
	review* dataNode = new review(prodId, custId, ratingStr, reviewText);
	newnode->nextnode = nullptr;
	newnode->prevnode = nullptr;

	newnode->_T = dataNode;

	return newnode;
}

void LinkedList<review>::printList() {
	const string separator = string(120, '=');

	cout << separator << endl;
	Node<review>* current = _NodeHEAD;
	if (current == nullptr) {
		cout << "List is empty.\n";
		return;
	}

	while (current != nullptr) {
		review* data = current->_T;
		cout << "Product ID: " << data->getProdId()
			<< ", Customer ID: " << data->getCustId()
			<< ", Rating: " << data->getRating()
			<< ", Review: " << data->getReviewText() << endl;
		current = current->nextnode;
	}
	cout << separator << endl;
}

void LinkedList<review>::searchAgain(string search) {
	int option;

	while (true) {
		cout << "Search again in filtered list? (1: Yes, -1: No): ";
		cin >> option;

		if (option == 1) {

			string category, keyword;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			while (true) {
				cout << "Enter your Search Category: ";
				getline(cin, category);
				category = toLower(category);

				if (category.empty()) {
					cout << "Error! Category is empty!" << endl;
					continue;
				}

				if (category != "customerid" &&
					category != "productid" &&
					category != "rating" &&
					category != "review") {
					cout << "Invalid category! Please enter one of: productId, customerId, rating, review." << endl;
					continue;
				}

				break;
			}

			while (true) {
				cout << "Enter your Keyword: ";
				getline(cin, keyword);

				if (keyword.empty()) {
					cout << "Error! Keyword is empty!" << endl;
					continue;
				}

				break;
			}

			if (search == "linear") {
				linearSearch(category, keyword);
			}
			else if (search == "binary") {
				//BinarySearch(category, keyword);
			}

			return;

		}
		else if (option == -1) {
			return;
		}
		else {
			cout << "Invalid Input!" << endl;
		}
	}
}

template<>
void LinkedList<review>::linearSearch(string category, string keyword) {
	Node<review>* current = _NodeHEAD;
	bool found = false;

	// Create a new linked list to store results
	LinkedList<review> results("search_results");

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	while (current != nullptr) {
		bool match = false;

		if (category == "productid" && current->_T->getProdId() == keyword) match = true;
		else if (category == "customerid" && current->_T->getCustId() == keyword) match = true;
		else if (category == "rating" && to_string(current->_T->getRating()) == keyword) match = true;
		else if (category == "review" && current->_T->getReviewText() == keyword) match = true;

		if (match) {
			// Clone the data and add to results list
			Node<review>* matchedNode = results.createNode(current->_T);
			results.addEndOfList(matchedNode);
			results.addLength();
			found = true;
		}

		current = current->nextnode;
	}

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	results.printList();

	cout << "Number of results found: " << results.getListLength() << " out of 3372 entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << endl << endl;

	if (!found) {
		cout << "No matching records found!" << endl;
	}

	results.searchAgain("linear");
}


// For assignment question 3

void LinkedList<review>::appendWordInFront(WordNode*& head, const string& word) {
	WordNode* newnode = new WordNode{ word, nullptr, head };
	if (head) {
		head->prev = newnode;
	}
	head = newnode;
}

// Time Complexity: O(1) for insert because of tail
//		O(W) overall where W is the number of words from all reviews with the target rating
// Space Complexity: O(N) for N words
WordNode* LinkedList<review>::extractAllWordsByRating(Node<review>* reviewHead, int ratingInput) {
	if (ratingInput < 1 || ratingInput > 5) {
		cout << "Invalid rating!" << endl;
		return nullptr;
	}
	WordNode* wordHead = nullptr;
	WordNode* wordTail = nullptr;

	while (reviewHead) {
		if (reviewHead->_T->getRating() == ratingInput) {
			istringstream iss(reviewHead->_T->getReviewText());
			string word;
			while (iss >> word) {
				word = toLower(word);
				WordNode* newWord = new WordNode{ word, nullptr, nullptr };
				if (!wordHead) { // Can use appendWordInFront() to become O(1) unless using tail?
					wordHead = wordTail = newWord;
				}
				else {
					wordTail->next = newWord;
					newWord->prev = wordTail;
					wordTail = newWord;
				}
			}
		}
		reviewHead = reviewHead->nextnode;
	}
	return wordHead;
}

WordNode* LinkedList<review>::mergeWordNodes(WordNode* left, WordNode* right) {
	if (!left) {
		return right;
	}
	if (!right) {
		return left;
	}

	if (left->word <= right->word) {
		left->next = mergeWordNodes(left->next, right);
		if (left->next) {
			left->next->prev = left;
		}
		left->prev = nullptr;
		return left;
	}
	else {
		right->next = mergeWordNodes(left, right->next);
		if (right->next) {
			right->next->prev = right;
		}
		right->prev = nullptr;
		return right;
	}
}

void LinkedList<review>::splitWordNodes(WordNode* head, WordNode** front, WordNode** back) {
	WordNode* slow = head;
	WordNode* fast = head->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	*front = head;
	*back = slow->next;
	slow->next = nullptr;
	if (*back) {
		(*back)->prev = nullptr;
	}
}

WordNode* LinkedList<review>::mergeSortWordNodes(WordNode* head) {
	if (!head || !head->next) {
		return head;
	}
	WordNode *front, *back;
	splitWordNodes(head, &front, &back);

	front = mergeSortWordNodes(front);
	back = mergeSortWordNodes(back);

	return mergeWordNodes(front, back);
}

WordFrequencyNode* LinkedList<review>::countWordFrequency(WordNode* sortedWordHead) {
	WordFrequencyNode* frequencyHead = nullptr;
	WordFrequencyNode* frequencyTail = nullptr;

	while (sortedWordHead) {
		string currentWord = sortedWordHead->word;
		int frequency = 1;

		WordNode* temp = sortedWordHead->next;
		while (temp && temp->word == currentWord) {
			frequency++;
			temp = temp->next;
		}

		WordFrequencyNode* newWordFrequencyNode = new WordFrequencyNode{ currentWord, frequency, nullptr, nullptr };
		if (!frequencyHead) {
			frequencyHead = frequencyTail = newWordFrequencyNode;
		}
		else {
			frequencyTail->next = newWordFrequencyNode;
			newWordFrequencyNode->prev = frequencyTail;
			frequencyTail = newWordFrequencyNode;
		}
		sortedWordHead = temp;
	}
	return frequencyHead;
}

WordFrequencyNode* LinkedList<review>::mergeWordFrequencyNodes(WordFrequencyNode* left, WordFrequencyNode* right) {
	if (!left) {
		return right;
	}
	if (!right) {
		return left;
	}

	if (left->frequency >= right->frequency) {
		left->next = mergeWordFrequencyNodes(left->next, right);
		if (left->next) {
			left->next->prev = left;
		}
		left->prev = nullptr;
		return left;
	}
	else {
		right->next = mergeWordFrequencyNodes(left, right->next);
		if (right->next) {
			right->next->prev = right;
		}
		right->prev = nullptr;
		return right;
	}
}

void LinkedList<review>::splitWordFrequencyNodes(WordFrequencyNode* head, WordFrequencyNode** front, WordFrequencyNode** back) {
	WordFrequencyNode* slow = head;
	WordFrequencyNode* fast = head->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	*front = head;
	*back = slow->next;
	slow->next = nullptr;
	if (*back) {
		(*back)->prev = nullptr;
	}
}

WordFrequencyNode* LinkedList<review>::mergeSortWordFrequencyNodes(WordFrequencyNode* head) {
	if (!head || !head->next) {
		return head;
	}

	WordFrequencyNode *front, * back;
	splitWordFrequencyNodes(head, &front, &back);

	front = mergeSortWordFrequencyNodes(front);
	back = mergeSortWordFrequencyNodes(back);

	return mergeWordFrequencyNodes(front, back);
}

void LinkedList<review>::printTop5MostFrequentlyUsedWords(WordFrequencyNode* head) {
	int count = 0;

	while (head && count < 5) {
		cout << head->word << " : " << head->frequency << endl;
		head = head->next;
		count++;
	}
}

/*void LinkedList<review>::printWordList(WordNode* head) {
	while (head) {
		cout << head->word << " ";
		head = head->next;
	}
	cout << endl;
}*/

template class LinkedList<review>;