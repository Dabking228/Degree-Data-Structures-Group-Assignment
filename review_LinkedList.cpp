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
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	cout << "Creating Review Linked List... \t";

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening review file for Linked List Creation!" << endl;
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

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	cout << "Successfully loaded " << getListLength() << " valid reviews! Time taken: " << taken.count() << " seconds." << endl;
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

		//cout << "Option is: " << option;

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
				
				int sortField = -1;
				if (category == "productid") sortField = 1;
				else if (category == "customerid") sortField = 2;
				else if (category == "rating") sortField = 3;
				else if (category == "review") sortField = 4;

				this->sortBy(1, sortField, true);
				this->binarySearch(category, keyword);

				return;
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
	
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	
	Node<review>* current = _NodeHEAD;
	bool found = false;

	// Create a new linked list to store results
	LinkedList<review> results("search_results");

	while (current != nullptr) {
		bool match = false;

		if (category == "productid" && current->_T->getProdId() == keyword) match = true;
		else if (category == "customerid" && current->_T->getCustId() == keyword) match = true;
		else if (category == "rating" && to_string(current->_T->getRating()) == keyword) match = true;
		else if (category == "review" && current->_T->getReviewText() == keyword) match = true;

		if (match) {
			// Clone the data and add to results list
			Node<review>* matchedNode = new Node<review>();
			matchedNode->_T = new review(*current->_T);  // deep copy
			matchedNode->nextnode = nullptr;
			matchedNode->prevnode = nullptr;
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
	cout << "Time taken for searching: " << fixed << setprecision(6) << taken.count() << endl << endl;

	if (!found) {
		cout << "No matching records found!" << endl;
	}

	results.searchAgain("linear");
}

bool LinkedList<review>::compareByField(const review* nodeA, const review* nodeB, int field) {
	switch (field) {
	case 1: return nodeA->getCustId() < nodeB->getCustId();
	case 2: return nodeA->getProdId() < nodeB->getProdId();
	case 3: return nodeA->getRating() < nodeB->getRating();
	case 4: return nodeA->getReviewText() < nodeB->getReviewText();
	//desencdng
	case 11: return nodeA->getCustId() > nodeB->getCustId();
	case 12: return nodeA->getProdId() > nodeB->getProdId();
	case 13: return nodeA->getRating() > nodeB->getRating();
	case 14: return nodeA->getReviewText() > nodeB->getReviewText();
	default: return false;
	}
}

template<>
bool LinkedList<review>::isSortedByCategory(string category, bool& isAscending) {
	isAscending = true;
	bool isDescending = true;

	Node<review>* curr = _NodeHEAD;
	if (curr == nullptr || curr->nextnode == nullptr) return true;

	while (curr->nextnode != nullptr) {
		string prev, next;

		if (category == "customerid") {
			prev = curr->_T->getCustId();
			next = curr->nextnode->_T->getCustId();
		}
		else if (category == "productid") {
			prev = curr->_T->getProdId();
			next = curr->nextnode->_T->getProdId();
		}
		else if (category == "rating") {
			prev = to_string(curr->_T->getRating());
			next = to_string(curr->nextnode->_T->getRating());
		}
		else if (category == "review") {
			prev = curr->_T->getReviewText();
			next = curr->nextnode->_T->getReviewText();
		}
		else {
			cout << "Invalid category!" << endl;
			return false;
		}

		if (prev > next) isAscending = false;
		if (prev < next) isDescending = false;

		curr = curr->nextnode;
	}

	return isAscending || isDescending;
}

template<>
void LinkedList<review>::binarySearch(string category, string keyword) {
	
	chrono::time_point<chrono::system_clock> begin, finish;
	begin = chrono::system_clock::now();
	
	if (_NodeHEAD == nullptr) {
		cout << "Error! Linked list is empty!" << endl;
		return;
	}

	bool isAscending;
	if (!isSortedByCategory(category, isAscending)) {
		cout << "Error! The list is not sorted by category '" << category << "'." << endl;
		return;
	}

	Node<review>* left = _NodeHEAD;
	Node<review>* right = _NodeTAIL;
	Node<review>* mid = nullptr;
	int matchCount = 0;

	while (left != right) {
		// Find the middle node using slow and fast pointer technique
		mid = left;
		Node<review>* fast = left;
		while (fast != right && fast->nextnode != right) {
			mid = mid->nextnode;
			fast = fast->nextnode;
			if (fast != right) fast = fast->nextnode;
		}

		string value;
		if (category == "customerid") value = mid->_T->getCustId();
		else if (category == "productid") value = mid->_T->getProdId();
		else if (category == "rating") value = to_string(mid->_T->getRating());
		else if (category == "review") value = mid->_T->getReviewText();


		if (value == keyword) {
			matchCount = 1;
			break;
		}
		else if ((isAscending && value < keyword) || (!isAscending && value > keyword)) {
			left = mid->nextnode;  // Move left pointer to the right of mid
		}
		else {
			right = mid->prevnode;  // Move right pointer to the left of mid
		}
	}

	if (matchCount == 0) {
		cout << "No results found for '" << keyword << "' in " << category << "." << endl;
		return;
	}

	// Expand left and right from the found mid to get all matching results
	int resultsCount = 1;
	Node<review>* start = mid;
	while (start->prevnode != nullptr) {
		string value;
		if (category == "customerid") value = start->prevnode->_T->getCustId();
		else if (category == "productid") value = start->prevnode->_T->getProdId();
		else if (category == "rating") value = to_string(start->prevnode->_T->getRating());
		else if (category == "review") value = start->prevnode->_T->getReviewText();

		if (value == keyword) {
			resultsCount++;
			start = start->prevnode;
		}
		else {
			break;
		}
	}

	Node<review>* end = mid;
	while (end->nextnode != nullptr) {
		string value;
		if (category == "customerid") value = end->nextnode->_T->getCustId();
		else if (category == "productid") value = end->nextnode->_T->getProdId();
		else if (category == "rating") value = to_string(end->nextnode->_T->getRating());
		else if (category == "review") value = end->nextnode->_T->getReviewText();

		if (value == keyword) {
			resultsCount++;
			end = end->nextnode;
		}
		else {
			break;
		}
	}

	end = end->nextnode; // Move to the last matching node

	// Print the results
	LinkedList<review> resultList("linked_binary_results");
	Node<review>* current = start;
	while (current != end) {
		resultList.addEndOfList(resultList.createNode(current->_T));
		resultList.addLength();
		current = current->nextnode;
	}

	// Print the final results and time taken
	resultList.printList();
	cout << "Number of results found: " << resultsCount << " entries. " << endl;

	finish = chrono::system_clock::now();
	chrono::duration<double> taken = finish - begin;
	cout << "Time taken for searching: " << fixed << setprecision(6) << taken.count() << " seconds" << endl << endl;

	resultList.toggleClone();

	resultList.searchAgain("binary");

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
	WordNode* front, * back;
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

	WordFrequencyNode* front, * back;
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

void LinkedList<review>::runLinkedListFindingMostFrequentWordInReview(int ratingInput) {
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	Node<review>* reviewNode = LinkedList<review>::getHEAD();

	if (!reviewNode) {
		cout << "Review list is empty!";
		return;
	}

	WordNode* words = LinkedList<review>::extractAllWordsByRating(reviewNode, ratingInput);
	words = LinkedList<review>::mergeSortWordNodes(words);
	WordFrequencyNode* wordFrequencyList = LinkedList<review>::countWordFrequency(words);
	wordFrequencyList = LinkedList<review>::mergeSortWordFrequencyNodes(wordFrequencyList);

	cout << "\nThe Top 5 Most Frequent Words for " << ratingInput << "-Star(s) Reviews:\n";
	LinkedList<review>::printTop5MostFrequentlyUsedWords(wordFrequencyList);

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "Time taken: " << taken.count() << endl;

	while (words) {
		WordNode* temp = words;
		words = words->next;
		delete temp;
		temp = nullptr;
	}

	while (wordFrequencyList) {
		WordFrequencyNode* temp = wordFrequencyList;
		wordFrequencyList = wordFrequencyList->next;
		delete temp;
		temp = nullptr;
	}
}

template class LinkedList<review>;