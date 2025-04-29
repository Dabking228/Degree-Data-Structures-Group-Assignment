#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

transaction* transactionNodeCreate(string custId, string product, string category, string price, string date, string paymentMethod) {
	transaction* _transactionNode = new transaction(custId, product, category, stod(price), date, paymentMethod);
	return _transactionNode;
}

transactionNode* transactionCreateLinked(string filepath) {
	cout << "Creating Trans Linked List.." << endl;
	transactionNode* HEAD{};
	transactionNode* curr{};
	transactionNode* prev{};
	string custId, product, category, price, date, paymentMethod;

	ifstream file(filepath);

	if (!file.good()) {
		cout << "Something wrong with transation file under LinkedList!" << endl;
		return nullptr;
	}

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

		if (HEAD == NULL) {
			transactionNode* newnode = new transactionNode;
			newnode->_transaction = transactionNodeCreate(custId, product, category, price, date, paymentMethod);
			HEAD = curr = prev = newnode;
			continue;
		}
		else {
			transactionNode* newnode = new transactionNode;
			curr = newnode;
			curr->_transaction = transactionNodeCreate(custId, product, category, price, date, paymentMethod);
			curr->prevnode = prev;
			prev->nextnode = curr;
			prev = newnode;
			continue;
		}
	}

	// Uncomment this code box for CLL
	/*if (HEAD != NULL) {
		HEAD->prevnode = prev;
		curr->nextnode = HEAD;
	}*/

	// this code box for TWLL
	if (HEAD != NULL) {
		HEAD->prevnode = nullptr;
		curr->nextnode = nullptr;
	}

	cout << "Trans Linked List Done " << endl;
	return HEAD;
}

review* reviewNodeCreate(string prodId, string custId, string rating, string reviewText) {
	review* _reviewNode = new review(prodId, custId, stoi(rating), reviewText);
	return _reviewNode;
}

reviewNode* reviewCreateLinked(string filepath) {
	cout << "Creating Review Linked List.. " << endl;
	reviewNode* HEAD{};
	reviewNode* curr{};
	reviewNode* prev{};
	string prodId, custId, rating, reviewText;

	ifstream file(filepath);

	if (!file.good()) {
		cout << "Something wrong with review file under LinkedList!" << endl;
		return nullptr;
	}

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

		if (HEAD == NULL) {
			reviewNode* newnode = new reviewNode;
			newnode->_review = reviewNodeCreate(prodId, custId, rating, reviewText);
			HEAD = curr = prev = newnode;
			continue;
		}
		else {
			reviewNode* newnode = new reviewNode;
			curr = newnode;
			curr->_review = reviewNodeCreate(prodId, custId, rating, reviewText);
			curr->prevnode = prev;
			prev->nextnode = curr;
			curr = newnode;
			prev = newnode;
			continue;
		}
	}

	// uncomment this for CLL
	/*if (HEAD != NULL) {
		HEAD->prevnode = prev;
		curr->nextnode = HEAD;
	}*/
	// this code box for TWLL
	if (HEAD != NULL) {
		HEAD->prevnode = nullptr;
		curr->nextnode = nullptr;
	}

	cout << "Done Creating Review Linked" << endl;
	return HEAD;
}
