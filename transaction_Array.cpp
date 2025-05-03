#include "Array.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iomanip>
#include <stdexcept>
using namespace std;



template<>
int Array<transaction>::getNumOfValidLines() {
	ifstream file(this->FILENAME);
	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
		return 0;
	}

	string line;
	int numOfValidLines = 0;

	// Skip header
	getline(file, line);

	// Time Complexity: O(N)
	while (getline(file, line)) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;

		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			numOfValidLines++;
		}
		else {
			continue;
		}
	}
	return numOfValidLines;
}


void Array<transaction>::createArray() {
	cout << "Creating Transaction Array... \t";
	string custId, product, category, price, date, paymentMethod;
	int numOfValidLines = getNumOfValidLines(); // Time Complexity = O(N)

	if (numOfValidLines == 0) {
		cout << "No valid transactions found!" << endl;
		return;
	}

	this->typePointer = new transaction[numOfValidLines];

	ifstream file(this->FILENAME);

	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	// Time Complexity: O(N)
	while (getline(file, line) && index < numOfValidLines) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;

		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			this->typePointer[index] = transaction(custId, product, category, priceStr, date, paymentMethod);
			index++;
		}
		else {
			continue;
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << arrayLength << " valid transactions!" << endl;
}

int Array<transaction>::countMatches(const string& category, const string& keyword) const {
	int matchCount = 0;

	for (int i = 0; i < arrayLength; ++i) {
		if ((category == "customerid" && typePointer[i].getCustId() == keyword) ||
			(category == "product" && typePointer[i].getProduct() == keyword) ||
			(category == "category" && typePointer[i].getCategory() == keyword) ||
			(category == "price" && to_string(typePointer[i].getPrice()) == keyword) ||
			(category == "date" && typePointer[i].getDate() == keyword) ||
			(category == "payment method" && typePointer[i].getPaymentMethod() == keyword)) {
			++matchCount;
		}
	}

	return matchCount;
}

void Array<transaction>::printList() const {
	const string separator = string(120, '=');

	cout << separator << endl;
	for (int i = 0; i < arrayLength; ++i) {
		cout << "CustomerID: " << typePointer[i].getCustId()
			<< ", Product: " << typePointer[i].getProduct()
			<< ", Category: " << typePointer[i].getCategory()
			<< ", Price: " << typePointer[i].getPrice()
			<< ", Date: " << typePointer[i].getDate()
			<< ", Payment Method: " << typePointer[i].getPaymentMethod() << endl;
	}
	cout << separator << endl;
}

void Array<transaction>::searchAgain(string search) {
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
void Array<transaction>::arrayLinearSearch(string category, string keyword) {

	if (typePointer == nullptr || arrayLength == 0) {
		cout << "Error! Array is empty!" << endl;
		return;
	}

	// Count number of results
	int matchCount = countMatches(category, keyword);

	// Create a new array to hold results
	Array<transaction> resultArray("filtered_results");
	resultArray.arrayLength = matchCount;
	resultArray.typePointer = new transaction[matchCount];

	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	int j = 0;
	for (int i = 0; i < arrayLength; ++i) {
		if ((category == "customerid" && typePointer[i].getCustId() == keyword) ||
			(category == "product" && typePointer[i].getProduct() == keyword) ||
			(category == "category" && typePointer[i].getCategory() == keyword) ||
			(category == "price" && to_string(typePointer[i].getPrice()) == keyword) ||
			(category == "date" && typePointer[i].getDate() == keyword) ||
			(category == "payment method" && typePointer[i].getPaymentMethod() == keyword)) {
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

bool Array<transaction>::isSortedByCategory(string category, bool& isAscending) {
	isAscending = true;
	bool isDescending = true;

	for (int i = 1; i < arrayLength; ++i) {
		string prev, curr;

		if (category == "customerid") {
			prev = typePointer[i - 1].getCustId();
			curr = typePointer[i].getCustId();
		}
		else if (category == "product") {
			prev = typePointer[i - 1].getProduct();
			curr = typePointer[i].getProduct();
		}
		else if (category == "category") {
			prev = typePointer[i - 1].getCategory();
			curr = typePointer[i].getCategory();
		}
		else if (category == "price") {
			prev = to_string(typePointer[i - 1].getPrice());
			curr = to_string(typePointer[i].getPrice());
		}
		else if (category == "date") {
			prev = typePointer[i - 1].getDate();
			curr = typePointer[i].getDate();
		}
		else if (category == "payment method") {
			prev = typePointer[i - 1].getPaymentMethod();
			curr = typePointer[i].getPaymentMethod();
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
void Array<transaction>::arrayBinarySearch(string category, string keyword) {

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
		else if (category == "product") value = typePointer[mid].getProduct();
		else if (category == "category") value = typePointer[mid].getCategory();
		else if (category == "price") value = to_string(typePointer[mid].getPrice());
		else if (category == "date") value = typePointer[mid].getDate();
		else if (category == "payment method") value = typePointer[mid].getPaymentMethod();

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
		else if (category == "product") value = typePointer[left].getProduct();
		else if (category == "category") value = typePointer[left].getCategory();
		else if (category == "price") value = to_string(typePointer[left].getPrice());
		else if (category == "date") value = typePointer[left].getDate();
		else if (category == "payment method") value = typePointer[left].getPaymentMethod();

		if (value == keyword) {
			matchCount++;
			left--;
		}
		else break;
	}

	while (right < arrayLength) {
		string value;
		if (category == "customerid") value = typePointer[right].getCustId();
		else if (category == "product") value = typePointer[right].getProduct();
		else if (category == "category") value = typePointer[right].getCategory();
		else if (category == "price") value = to_string(typePointer[right].getPrice());
		else if (category == "date") value = typePointer[right].getDate();
		else if (category == "payment method") value = typePointer[right].getPaymentMethod();

		if (value == keyword) {
			matchCount++;
			right++;
		}
		else break;
	}

	end = chrono::system_clock::now();
	chrono::duration<double> taken = end - start;

	// 4. Create result array
	Array<transaction> resultArray("binary_results");
	resultArray.arrayLength = matchCount;
	resultArray.typePointer = new transaction[matchCount];

	int idx = 0;
	for (int i = left + 1; i < right; ++i) {
		resultArray.typePointer[idx++] = typePointer[i];
	}

	resultArray.printList();
	cout << "Number of results found: " << matchCount << " out of " << arrayLength << " entries." << endl;
	cout << "Time taken: " << fixed << setprecision(6) << taken.count() << " seconds" << endl << endl;

	resultArray.searchAgain("binary");
}

template class Array<transaction>;

	if (!file) {
		cerr << "Error in opening transaction file for Array Creation!" << endl;
		return;
	}

	string line;
	int index = 0;

	// Skip header
	getline(file, line);

	// Time Complexity: O(N)
	while (getline(file, line) && index < numOfValidLines) {
		stringstream ss(line);
		string custId, product, category, priceStr, date, paymentMethod;

		getline(ss, custId, ',');
		getline(ss, product, ',');
		getline(ss, category, ',');
		getline(ss, priceStr, ',');
		getline(ss, date, ',');
		getline(ss, paymentMethod);

		if (transaction::isValidTransaction(custId, product, category, priceStr, date, paymentMethod)) {
			this->typePointer[index] = transaction(custId, product, category, priceStr, date, paymentMethod);
			index++;
		}
		else {
			continue;
		}
	}
	this->arrayLength = index;
	cout << "Successfully loaded " << arrayLength << " valid transactions!" << endl;
}



// Bubble Sorting

bool Array<transaction>::compareByField(const transaction& a, const transaction& b, int field) {
	switch (field) {
	case 1: return a.getCustId() < b.getCustId();
	case 2: return a.getProduct() < b.getProduct();
	case 3: return a.getCategory() < b.getCategory(); 
	case 4: return a.getPrice() < b.getPrice(); 
	case 5: //good
	{
		stringstream ssA(a.getDate()), ssB(b.getDate());
		tm tmA = {};
		tm tmB = {};

		ssA >> get_time(&tmA, "%d/%m/%Y");
		ssB >> get_time(&tmB, "%d/%m/%Y");
		if (ssA.fail() || ssB.fail()) {
			return false;

			cout << "Failed to parse date" << endl;
		}

		//cout << mktime(&tmA) << " | " << mktime(&tmB) << endl;

		return mktime(&tmA) < mktime(&tmB);
	}
	case 6: return a.getPaymentMethod() < b.getPaymentMethod();
	default: return false;
	}
}



template class Array<transaction>;
*/




