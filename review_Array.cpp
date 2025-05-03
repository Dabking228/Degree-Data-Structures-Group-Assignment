#include "Array.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <iomanip>
using namespace std;

template<>
int Array<review>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening review file for Array Creation!" << endl;
		return 0;
	}

	string line;
	int numOfValidLines = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line)) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText); // So that review text with comma ',' will not be wrongly cut

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
			numOfValidLines++;
		}
		else {
			continue;
		}
	}
	return numOfValidLines;
}

void Array<review>::createArray() {
	cout << "Creating Review Array... \t";
	string prodId, custId, ratingStr, reviewText;
	int numOfValidLines = getNumOfValidLines();

	if (numOfValidLines == 0) {
		cout << "No valid reviews found!" << endl;
		return;
	}

	this->typePointer = new review[numOfValidLines];

	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening review file for Array Creation!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	while (getline(file, line) && index < numOfValidLines) {
		stringstream ss(line);
		string prodId, custId, ratingStr, reviewText;
		getline(ss, prodId, ',');
		getline(ss, custId, ',');
		getline(ss, ratingStr, ',');
		getline(ss, reviewText); // So that review text with comma ',' will not be wrongly cut

		if (review::isValidReview(prodId, custId, ratingStr, reviewText)) {
			this->typePointer[index] = review(prodId, custId, ratingStr, reviewText);
			index++;
		}
		else {
			continue;
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << index << " valid reviews!" << endl;
}

int Array<review>::countMatches(const string& category, const string& keyword) const {
	int matchCount = 0;

	for (int i = 0; i < arrayLength; ++i) {
		if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
			(category == "customerid" && typePointer[i].getCustId() == keyword) ||
			(category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
			(category == "review" && typePointer[i].getReviewText() == keyword)) {
			++matchCount;
		}
	}

	return matchCount;
}

void Array<review>::printList() const {
	const string separator = string(100, '=');

	cout << separator << endl;
	for (int i = 0; i < arrayLength; ++i) {
		cout << "ProductID: " << typePointer[i].getProdId()
			<< ", CustomerID: " << typePointer[i].getCustId()
			<< ", Rating: " << to_string(typePointer[i].getRating())
			<< ", Review: " << typePointer[i].getReviewText() << endl;
	}
	cout << separator << endl;
}

void Array<review>::searchAgain(string search) {
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
				arrayLinearSearch(category, keyword);
			}
			else if (search == "binary") {
				//arrayBinarySearch(category, keyword);
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
void Array<review>::arrayLinearSearch(string category, string keyword) {

	if (typePointer == nullptr || arrayLength == 0) {
		cout << "Error! Array is empty!" << endl;
		return;
	}

	// Count number of results
	int matchCount = countMatches(category, keyword);


	// Create a new array to hold results
	Array<review> resultArray("filtered_results");
	resultArray.arrayLength = matchCount;
	resultArray.typePointer = new review[matchCount];

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	int j = 0;
	for (int i = 0; i < arrayLength; ++i) {
		if ((category == "productid" && typePointer[i].getProdId() == keyword) ||
			(category == "customerid" && typePointer[i].getCustId() == keyword) ||
			(category == "rating" && to_string(typePointer[i].getRating()) == keyword) ||
			(category == "review" && typePointer[i].getReviewText() == keyword)) {
			resultArray.typePointer[j++] = typePointer[i];
		}
	}

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	resultArray.printList();

	cout << "Number of results found: " << matchCount << " out of 4128 entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << endl << endl;

	resultArray.searchAgain("linear");

	return;

}

// For assignment question 3
template<>
int Array<review>::getTotalNumOfWords(int ratingInput) {
	if (ratingInput < 1 || ratingInput > 5) {
		cout << "Invalid rating!" << endl;
		return 0;
	}
	int totalWords = 0;

	for (int i = 0; i < getArrayLength(); ++i) {
		if (typePointer[i].getRating() == ratingInput) { // Assume it's 1 for assignment question
			string text = typePointer[i].getReviewText();
			stringstream ss(text);
			string word;
			while (ss >> word) {
				totalWords++;
			}
		}
	}
	return totalWords;
}

string* Array<review>::extractAllWords(const int& wordCount, int ratingInput) {
	if (wordCount == 0) {
		cout << "There are no words in reviews!" << endl;
		return nullptr;
	}
	if (ratingInput < 1 || ratingInput > 5) {
		cout << "Invalid rating!" << endl;
		return nullptr;
	}
	string* allReviewWords = new string[wordCount]; // Get Word Count from getTotalNumOfWords(int ratingInput)
	int index = 0;

	for (int i = 0; i < getArrayLength(); ++i) {
		if (typePointer[i].getRating() == ratingInput) { // Assume it's 1 for assignment question
			string text = typePointer[i].getReviewText();
			stringstream ss(text);
			string word;
			while (ss >> word) {
				allReviewWords[index] = toLower(word); // Remove punctuations and convert to lowercase
				index++;
			}
		}
	}
	return allReviewWords;
}

// Do sorting for allReviewWords based on alphabetical order
void Array<review>::mergeAllReviewWords(string* allReviewWords, int left, int mid, int right) {
	if (allReviewWords == nullptr) {
		cout << "There are no words in reviews!" << endl;
		return;
	}
	int n1 = mid - left + 1;
	int n2 = right - mid;

	string* leftWord = new string[n1];
	string* rightWord = new string[n2];

	for (int i = 0; i < n1; i++) { 
		leftWord[i] = allReviewWords[left + i];
	}
	for (int j = 0; j < n2; j++) {
		rightWord[j] = allReviewWords[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftWord[i] <= rightWord[j]) {
			allReviewWords[k] = leftWord[i];
			i++;
		}
		else {
			allReviewWords[k] = rightWord[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		allReviewWords[k] = leftWord[i];
		i++;
		k++;
	}
	while (j < n2) {
		allReviewWords[k] = rightWord[j];
		j++;
		k++;
	}

	delete[] leftWord;
	delete[] rightWord;
}

void Array<review>::mergeSortAllReviewWords(string* allReviewWords, int left, int right) {
	if (allReviewWords == nullptr) {
		cout << "There are no words in reviews!" << endl;
		return;
	}
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSortAllReviewWords(allReviewWords, left, mid);
		mergeSortAllReviewWords(allReviewWords, mid + 1, right);
		mergeAllReviewWords(allReviewWords, left, mid, right);
	}
}

string* Array<review>::mergeSortAndReturnAllReviewWords(string* allReviewWords, const int& wordCount) {
	if (allReviewWords == nullptr || wordCount == 0) {
		cout << "There are no words in reviews!" << endl;
		return nullptr;
	}
	string* allSortedReviewWords = new string[wordCount];
	for (int i = 0; i < wordCount; i++) {
		allSortedReviewWords[i] = allReviewWords[i];
	}
	mergeSortAllReviewWords(allSortedReviewWords, 0, wordCount - 1);
	return allSortedReviewWords; // Sorted version 
	
	// Must delete[] allSortedReviewWords after this
}

int Array<review>::getTotalNumOfUniqueReviewWords(string* allSortedReviewWords, const int& wordCount) {
	if (allSortedReviewWords == nullptr || wordCount == 0) {
		cout << "There are no words in reviews!" << endl;
		return 0;
	}
	int currentPoint = 0;
	int nextPoint = 1;
	int totalNumOfUniqueWords = 1; // For first word;

	while (nextPoint < wordCount) {
		if (allSortedReviewWords[currentPoint] != allSortedReviewWords[nextPoint]) {
			totalNumOfUniqueWords++;
		}
		currentPoint++;
		nextPoint++;
	}
	return totalNumOfUniqueWords;
}

WordFrequency* Array<review>::getUniqueWordsAndCount(string* allSortedReviewWords, const int& wordCount, int uniqueWordCount) {
	if (allSortedReviewWords == nullptr || wordCount == 0 || uniqueWordCount == 0) {
		cout << "There are no words in reviews!" << endl;
		return nullptr;
	}
	
	WordFrequency* allUniqueWords = new WordFrequency[uniqueWordCount];
	int currentPoint = 0;
	int nextPoint = 1;
	int allUniqueWordsIndex = 0;

	allUniqueWords[0] = WordFrequency(allSortedReviewWords[0], 1); // To add first word

	while (nextPoint < wordCount) {
		if (allSortedReviewWords[currentPoint] != allSortedReviewWords[nextPoint]) { // Unique Word
			if (allUniqueWordsIndex + 1 >= uniqueWordCount) {
				break;
			}
			allUniqueWordsIndex++;
			allUniqueWords[allUniqueWordsIndex] = WordFrequency(allSortedReviewWords[nextPoint], 1);
		}
		else { // Same Word
			allUniqueWords[allUniqueWordsIndex].addFrequency();
		}
		currentPoint++;
		nextPoint++;
	}
	return allUniqueWords;
}

void Array<review>::mergeUniqueWords(WordFrequency* allUniqueWords, int left, int mid, int right) {
	if (allUniqueWords == nullptr) {
		cout << "There are no words in reviews!" << endl;
		return;
	}

	int n1 = mid - left + 1;
	int n2 = right - mid;

	WordFrequency* leftWord = new WordFrequency[n1];
	WordFrequency* rightWord = new WordFrequency[n2];

	for (int i = 0; i < n1; i++) {
		leftWord[i] = allUniqueWords[left + i];
	}
	for (int j = 0; j < n2; j++) {
		rightWord[j] = allUniqueWords[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftWord[i].getFrequency() <= rightWord[j].getFrequency()) {
			allUniqueWords[k] = leftWord[i];
			i++;
		}
		else {
			allUniqueWords[k] = rightWord[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		allUniqueWords[k] = leftWord[i];
		i++;
		k++;
	}
	while (j < n2) {
		allUniqueWords[k] = rightWord[j];
		j++;
		k++;
	}

	delete[] leftWord;
	delete[] rightWord;
}

void Array<review>::mergeSortUniqueWords(WordFrequency* allUniqueWords, int left, int right) {
	if (allUniqueWords == nullptr) {
		cout << "There are no words in reviews!" << endl;
		return;
	}
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSortUniqueWords(allUniqueWords, left, mid);
		mergeSortUniqueWords(allUniqueWords, mid + 1, right);
		mergeUniqueWords(allUniqueWords, left, mid, right);
	}
}

WordFrequency* Array<review>::mergeSortUniqueWordsByFrequency(WordFrequency* allUniqueWords, int uniqueWordCount) {
	if (allUniqueWords == nullptr || uniqueWordCount == 0) {
		cout << "There are no words in reviews!" << endl;
		return nullptr;
	}
	WordFrequency* allSortedUniqueWordsByFrequency = new WordFrequency[uniqueWordCount];
	for (int i = 0; i < uniqueWordCount; i++) {
		allSortedUniqueWordsByFrequency[i] = allUniqueWords[i];
	}
	mergeSortUniqueWords(allSortedUniqueWordsByFrequency, 0, uniqueWordCount - 1);
	return allSortedUniqueWordsByFrequency;

	// Must delete[] allSortedUniqueWordsByFrequency after this
}

void Array<review>::printTop5MostFrequentlyUsedWords(WordFrequency* allSortedUniqueWordsByFrequency, int uniqueWordCount, int ratingInput) {
	if (allSortedUniqueWordsByFrequency == nullptr || uniqueWordCount == 0) {
		cout << "No words to display!" << endl;
		return;
	}
	if (ratingInput < 1 || ratingInput > 5) {
		cout << "Invalid rating!" << endl;
		return;
	}
	// Prevent out of bounds if 5 > uniqueWordCount
	// int startIndex = max(0, uniqueWordCount - 5); Similar Implementation
	int startIndex;
	if (uniqueWordCount - 5 <= 0) {
		startIndex = 0;
	}
	else {
		startIndex = uniqueWordCount - 5;
	}
	
	cout << "Top " << (uniqueWordCount - startIndex) << " Most Frequent Words for " << ratingInput << "-star(s) review:\n";
	for (int i = uniqueWordCount - 1; i >= startIndex; i--) {
		cout << allSortedUniqueWordsByFrequency[i].getWord() << " : " << allSortedUniqueWordsByFrequency[i].getFrequency() << endl;
	}
}

template class Array<review>;

/*	int index = 0;


	ifstream file(this->FILENAME);

	if (!file.good()) {
		cout << "Something wrong with review file!" << endl;
	}

	this->typePointer = new review[index + 1];

	while (file.good()) {
		getline(file, prodId, ',');
		getline(file, custId, ',');
		getline(file, rating, ',');
		getline(file, reviewText);
		if (prodId == "Product ID") {
			continue;
		}
		if (prodId == "" && custId == "" && rating == "" && reviewText == "") {
			break; // stops when no more records
		}
		if (prodId == "" || custId == "" || rating == "" || reviewText == "") { // data cleaning line
			continue; // skip missing values
		}
		// test if the rating can convert to interger
		try {
			stoi(rating);
		}
		catch (exception& err) {
			continue;
		}

		//TODO: same as the on for transaction, need to optimize
		review* oldReivewList = this->typePointer;
		this->typePointer = new review[index + 1];
		for (int i = 0; i < index; i++) {
			this->typePointer[i] = oldReivewList[i];
		}
		//cout << index + 1 << endl;
		delete[] oldReivewList;

		// array creation
		this->typePointer[index].prodId = prodId;
		this->typePointer[index].custId = custId;
		this->typePointer[index].rating = stoi(rating);
		this->typePointer[index].reviewText = reviewText;

		index++;
	}

	cout << "Review Array Created!" << endl;
	this->arrayLength = index;
}

template class Array<review>;
*/