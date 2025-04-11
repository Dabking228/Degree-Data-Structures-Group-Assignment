#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "strucuture.h"

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

transaction* transactionCreate(string filepath, transactionNode* transNodeAddress) {
	string custId, product, catagory, price, date, paymentMethod;

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
		getline(file, catagory, ',');
		getline(file, price, ',');
		getline(file, date, ',');
		getline(file, paymentMethod);
		if (custId == "Customer ID") {
			continue;
		}
		if (custId == "") {
			break;
		}
		if (index >= numberOfTransaction) {
			break;
		}

		// array creation
		transactionList[index].setCustId(custId);
		transactionList[index].setProduct(product);
		transactionList[index].setCatagory(catagory);
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
		if (prodId == "") {
			break;
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

/*
create head node if not exsit
the asign the head node and as current
head node exist
then create newnode -> assign prew addr from curr (newnode) -> assign next addr from newnode (curr)
done? then update addr of curr from newnode addr
*/

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
		if (prodId == "") {
			break;
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



transaction* transactionNodeCreate(string custId, string product, string catagory, string price, string date, string paymentMethod) {
	transaction* _transactionNode = new transaction(custId, product,catagory,stod(price),date,paymentMethod);
	return _transactionNode;
}

/*
create a functiton that read through the file, for both transaction and review.
but i want it to return a memory address for that array
maybe i should try it inside main.cpp 1st before
*/
