#include "Array.hpp"
#include "LinkedList.hpp"
#include "Utils.hpp"
#include <iostream>
#include <chrono>
using namespace std;
string TransactionFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

namespace {
	LinkedList<transaction> _TransactionLinked(TransactionFILENAME);
	LinkedList<review> _ReviewLinked(ReviewFILENAME);

	Array<transaction> _TransactionArray(TransactionFILENAME);
	Array<review> _ReviewArray(ReviewFILENAME);
}

void initializeData() {
	chrono::time_point<chrono::system_clock> startArray, endArray;
	startArray = chrono::system_clock::now();

	_TransactionArray.createArray();
	_ReviewArray.createArray();

	endArray = chrono::system_clock::now();
	chrono::duration<double> takenArray = endArray - startArray;
	cout << "Time taken for Array Creation: " << takenArray.count() << endl;


	chrono::time_point<chrono::system_clock> startLinkedList, endLinkedList;
	startLinkedList = chrono::system_clock::now();

	_TransactionLinked.createLinkedList();
	_ReviewLinked.createLinkedList();

	endLinkedList = chrono::system_clock::now();
	chrono::duration<double> takenLinkedList = endLinkedList - startLinkedList;
	cout << "Time taken for Linked List Creation: " << takenLinkedList.count() << endl;
}

void callSearch(string search) {
	string category, keyword;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (search == "transactions") {

		while (true) {
			cout << "Enter your Search Category: ";
			getline(cin, category);
			category = toLower(category);

			if (category.empty()) {
				cout << "Error! Category is empty!" << endl;
				continue;
			}

			if (category != "customerid" &&
				category != "product" &&
				category != "category" &&
				category != "price" &&
				category != "date" &&
				category != "payment method") {
				cout << "Invalid category! Please enter one of: customerId, product, category, price, date, payment method." << endl;
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

		_TransactionArray.arrayLinearSearch(category, keyword);
	}

	//else if (search == "binary")
		//_TransactionArray.arrayBinarySearch(category, keyword);
	else if (search == "reviews") {

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
				cout << "Invalid category! Please enter one of: customerId, productid, rating, review." << endl;
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

		_ReviewArray.arrayLinearSearch(category, keyword);
	}

}

void testQ3forArrays() {
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	int ratingInput = 5;
	int totalNumOfReviewWords = _ReviewArray.getTotalNumOfWords(ratingInput);
	string* allReviewWords = _ReviewArray.extractAllWords(totalNumOfReviewWords, ratingInput);
	string* allSortedReviewWords = _ReviewArray.mergeSortAndReturnAllReviewWords(allReviewWords, totalNumOfReviewWords);
	int totalNumOfUniqueWords = _ReviewArray.getTotalNumOfUniqueReviewWords(allSortedReviewWords, totalNumOfReviewWords);
	WordFrequency* allUniqueWords = _ReviewArray.getUniqueWordsAndCount(allSortedReviewWords, totalNumOfReviewWords, totalNumOfUniqueWords);
	WordFrequency* allSortedUniqueWordsByFrequency = _ReviewArray.mergeSortUniqueWordsByFrequency(allUniqueWords, totalNumOfUniqueWords);
	_ReviewArray.printTop5MostFrequentlyUsedWords(allSortedUniqueWordsByFrequency, totalNumOfUniqueWords, ratingInput);

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "Time taken for Most Frequent Words: " << taken.count() << endl;

	delete[] allReviewWords;
	delete[] allSortedReviewWords;
	delete[] allUniqueWords;
	delete[] allSortedUniqueWordsByFrequency;
}

void testQ3forLinkedList() {
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	Node<review>* reviewNode = _ReviewLinked.getHEAD();

	if (!reviewNode) {
		cout << "Review list is empty!";
		return;
	}

	int ratingInput = 1;
	WordNode* words = _ReviewLinked.extractAllWordsByRating(reviewNode, ratingInput);
	words = _ReviewLinked.mergeSortWordNodes(words);
	WordFrequencyNode* wordFrequencyList = _ReviewLinked.countWordFrequency(words);
	wordFrequencyList = _ReviewLinked.mergeSortWordFrequencyNodes(wordFrequencyList);

	cout << "The Top 5 Most Frequent Words for " << ratingInput << "-star(s) review:\n";
	_ReviewLinked.printTop5MostFrequentlyUsedWords(wordFrequencyList);

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;
	cout << "Time taken for Most Frequent Words: " << taken.count() << endl;

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

int main() {
	initializeData();



	return 0;
}
	/*while (true) {

		int option;
		cout << "Enter 2 to search trans array, 3 to search reviews array, or -1 to exit: ";
		cin >> option;

		switch (option) {
		case 2: {
			callSearch("transactions"); // changed parameter to what you want to test
			break;
		}
		case 3: {
			callSearch("reviews");
			break;
		}
		case -1: {
			return 0;
		}
		}
	}*/

	//cout << _TransactionLinked.getListLength() << endl;
	//cout << _ReviewLinked.getListLength() << endl;

	//cout << _TransactionArray.getArrayLength() << endl;
	//cout << _ReviewArray.getArrayLength() << endl;




