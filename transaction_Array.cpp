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

template class Array<transaction>;

/*	if (!file.good()) {
		cout << "Something wrong with transaction file!" << endl;
	}

	this->typePointer = new transaction[index + 1];

	while (file.good()) {
		getline(file, custId, ',');
		getline(file, product, ',');
		getline(file, category, ',');
		getline(file, price, ',');
		getline(file, date, ',');
		getline(file, paymentMethod);
		if (custId == "Customer ID") {
			continue;
		}
		if (custId == "" && product == "" && category == "" && price == "" && date == "" && paymentMethod == "") {
			break; // stops when no more records
		}
		if (custId == "" || product == "" || category == "" || price == "" || date == "" || paymentMethod == "") { // data cleaning line
			continue; // skip missing values
		}
		if (isnan(stod(price))) { // check for NaN price value
			continue;
		}
		if (date == "Invalid Date") { // check if the text is invalid date, need to create another checker for invalid date that is NOT written in "Invalid Date"
			continue;
		}

		// TODO: optimize this part of the code, maybe use back idea 1
		transaction* oldtransactionList = this->typePointer;
		this->typePointer = new transaction[index + 1];
		for (int i = 0; i < index; i++) {
			this->typePointer[i] = oldtransactionList[i];
		}
		//cout << index+1 << endl;
		delete[] oldtransactionList;


		//// add item into array
		this->typePointer[index].custId = custId;
		this->typePointer[index].product = product;
		this->typePointer[index].category = category;
		this->typePointer[index].price = stod(price);
		this->typePointer[index].date = date;
		this->typePointer[index].paymentMethod = paymentMethod;

		index++;

	}

	cout << "Transaction Array Created!" << endl;
	this->arrayLength = index;
	//return this->typePointer;

template class Array<transaction>;
*/




