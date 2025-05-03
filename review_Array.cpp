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
				int sortField = -1;
				if (category == "productid") sortField = 1;
				else if (category == "customerid") sortField = 2;
				else if (category == "rating") sortField = 3;
				else if (category == "review") sortField = 4;

				Array<review>* cloned_results = clone();
				cloned_results->sortBy(1, sortField);
				cloned_results->arrayBinarySearch(category, keyword);
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
            (category == "review" && typePointer[i].getReviewText() == keyword))  {
            resultArray.typePointer[j++] = typePointer[i];
        }
    }

    end = chrono::system_clock::now();
    chrono::duration<double> taken = end - start;

    resultArray.printList();

    cout << "Number of results found: " << matchCount << " out of 3372 entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << endl << endl;

    resultArray.searchAgain("linear");

    return;

}

bool Array<review>::isSortedByCategory(string category, bool& isAscending) {
	isAscending = true;
	bool isDescending = true;

	for (int i = 1; i < arrayLength; ++i) {
		string prev, curr;

		if (category == "customerid") {
			prev = typePointer[i - 1].getCustId();
			curr = typePointer[i].getCustId();
		}
		else if (category == "productid") {
			prev = typePointer[i - 1].getProdId();
			curr = typePointer[i].getProdId();
		}
		else if (category == "rating") {
			prev = to_string(typePointer[i - 1].getRating());
			curr = to_string(typePointer[i].getRating());
		}
		else if (category == "review") {
			prev = typePointer[i - 1].getReviewText();
			curr = typePointer[i].getReviewText();
		}
		else {
			cout << "Invalid category!" << endl;
			return false;
		}

		if (prev > curr) isAscending = false;
		if (prev < curr) isDescending = false;
	}

	return isAscending || isDescending;
}

template<>
void Array<review>::arrayBinarySearch(string category, string keyword) {

	if (typePointer == nullptr || arrayLength == 0) {
		cout << "Error! Array is empty!" << endl;
		return;
	}

	// 1. Check if the array is sorted (ascending or descending)
	bool isAscending;
	if (!isSortedByCategory(category, isAscending)) {
		cout << "Error! The array is not sorted by category '" << category << "'." << endl;
		return;
	}

	// 2. Perform binary search to find ONE matching record
	int low = 0, high = arrayLength - 1, foundIndex = -1;

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	while (low <= high) {
		int mid = (low + high) / 2;
		string value;

		if (category == "customerid") value = typePointer[mid].getCustId();
		else if (category == "productid") value = typePointer[mid].getProdId();
		else if (category == "rating") value = to_string(typePointer[mid].getRating());
		else if (category == "review") value = typePointer[mid].getReviewText();

		if (value == keyword) {
			foundIndex = mid;
			break;
		}
		else if ((isAscending && value < keyword) || (!isAscending && value > keyword)) {
			// target is on the right
			low = mid + 1;
		}
		else {
			// target is on the left
			high = mid - 1;
		}
	}

	// 3. If found, expand left and right to get all matching records
	if (foundIndex == -1) {
		cout << "No results found for '" << keyword << "' in " << category << "." << endl;
		return;
	}

	int left = foundIndex - 1;
	int right = foundIndex + 1;
	int matchCount = 1;

	while (left >= 0) {
		string value;
		if (category == "customerid") value = typePointer[left].getCustId();
		else if (category == "productid") value = typePointer[left].getProdId();
		else if (category == "rating") value = to_string(typePointer[left].getRating());
		else if (category == "review") value = typePointer[left].getReviewText();

		if (value == keyword) {
			matchCount++;
			left--;
		}
		else break;
	}

	while (right < arrayLength) {
		string value;
		if (category == "customerid") value = typePointer[right].getCustId();
		else if (category == "productid") value = typePointer[right].getProdId();
		else if (category == "rating") value = to_string(typePointer[right].getRating());
		else if (category == "review") value = typePointer[right].getReviewText();

		if (value == keyword) {
			matchCount++;
			right++;
		}
		else break;
	}

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	// 4. Create result array
	Array<review> resultArray("binary_results");
	resultArray.arrayLength = matchCount;
	resultArray.typePointer = new review[matchCount];

	int idx = 0;
	for (int i = left + 1; i < right; ++i) {
		resultArray.typePointer[idx++] = typePointer[i];
	}

	resultArray.printList();
	cout << "Number of results found: " << matchCount << " out of " << arrayLength << " entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << " seconds" << endl << endl;

	resultArray.searchAgain("binary");
}

bool Array<review>::compareByField(const review& a, const review& b, int field) {
	switch (field) {
	case 1: return a.getCustId() < b.getCustId();
	case 2: return a.getProdId() < b.getProdId();
	case 3: return a.getRating() < b.getRating();
	case 4: return a.getReviewText() < a.getReviewText();
	default: return false;
	}
}

template class Array<review>;

/*	int index = 0;


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

bool Array<review>::compareByField(const review& a, const review& b, int field) {
	switch (field) {
	case 1: return a.getCustId() < b.getCustId();
	case 2: return a.getProdId() < b.getProdId();
	case 3: return a.getRating() < b.getRating();
	case 4: return a.getReviewText() < a.getReviewText();
	default: return false;
	}
}

template class Array<review>;
*/

