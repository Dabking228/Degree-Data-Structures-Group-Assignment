#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.h"

// this file creates transaction and review array and linked list

int getNumberofLines(string filepath) {
	int numberOfLines = 0;
	string lines;

	ifstream file(filepath);
	getline(file, lines); // skip the header line
	while (getline(file, lines)) {
		if (!lines.empty()) {
			++numberOfLines;
		}
	}
	file.close();
	return numberOfLines;
}

transaction* transactionCreate(string filepath) {
	string custId, product, category, price, date, paymentMethod;

	int numberOfTransaction = 0;
	string lines;
	int index = 0;


	ifstream file(filepath);

	if (!file.good()) {
		cout << "Something wrong with transaction file!" << endl;
		return nullptr;
	}

	numberOfTransaction = getNumberofLines(filepath);
	// 4128
	//cout << numberOfTransaction << endl;

	transaction* transactionList = new transaction[numberOfTransaction];

	getline(file, lines); // skip header line
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
		if (index >= numberOfTransaction) {
			break;
		}

		// array creation
		transactionList[index].setCustId(custId);
		transactionList[index].setProduct(product);
		transactionList[index].setCatagory(category);
		transactionList[index].setPrice(stod(price));
		transactionList[index].setDate(date);
		transactionList[index].setPaymentMethod(paymentMethod);
		
		index++;
	}

	return transactionList;
	

}

review* reviewCreate(string filepath) {
	string prodId, custId, rating, reviewText;

	int numberOfReview = 0;
	string lines;
	int index = 0;


	ifstream file(filepath);

	if (!file.good()) {
		cout << "Something wrong with review file!" << endl;
		return nullptr;
	}

	numberOfReview = getNumberofLines(filepath);
	// 3372
	 //cout << numberOfReview << endl;

	review* reviewList = new review[numberOfReview];

	getline(file, lines); // skip header line
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
		if (prodId == "" || custId == "" || rating == "" || reviewText == "" ) { // data cleaning line
			continue; // skip missing values
		}
		// test if the rating can convert to interger
		try {
			stoi(rating);
		}
		catch (exception& err) {
			continue;
		}
		if (index >= numberOfReview) {
			break;
		}

		// array creation
		reviewList[index].setProdId(prodId);
		reviewList[index].setCustId(custId);
		reviewList[index].setRating(stoi(rating));
		reviewList[index].setReviewText(reviewText);
		
		index++;
	}

	return reviewList;


}


review* reviewNodeCreate(string prodId, string custId, string rating, string reviewText) {
	review* _reviewNode = new review(prodId, custId, stoi(rating), reviewText);
	return _reviewNode;
}

reviewNode* reviewCreateLinked(string filepath) {
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
		catch (exception &err) {
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

	if (HEAD != NULL) {
		HEAD->prevnode = prev;
		curr->nextnode = HEAD;
	}
	return HEAD;
}



transaction* transactionNodeCreate(string custId, string product, string category, string price, string date, string paymentMethod) {
	transaction* _transactionNode = new transaction(custId, product,category,stod(price),date,paymentMethod);
	return _transactionNode;
}

transactionNode* transactionCreateLinked(string filepath) {
	transactionNode* HEAD{};
	transactionNode* curr{};
	transactionNode* prev{};
	string custId, product, category, price, date, paymentMethod;

	ifstream file(filepath);

	if (!file.good()) {
		cout << "Something wrong with review file under LinkedList!" << endl;
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

		if (HEAD == NULL) {
			transactionNode* newnode = new transactionNode;
			newnode->_transaction = transactionNodeCreate(custId, product,category,price, date, paymentMethod);
			HEAD = curr = prev = newnode;
			continue;
		}
		else {
			transactionNode* newnode = new transactionNode;
			curr = newnode;
			curr->_transaction = transactionNodeCreate(custId, product, category, price, date, paymentMethod);
			curr->prevnode = prev;
			prev->nextnode = curr;
			curr = newnode;
			prev = newnode;
			continue;
		}
	}

	if (HEAD != NULL) {
		HEAD->prevnode = prev;
		curr->nextnode = HEAD;
	}
	return HEAD;
}

