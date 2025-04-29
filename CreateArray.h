//#pragma once
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "structure.h"
//
//
//int getNumberofLines(transaction* transactionPointer) {
//	return 0;
//}
//
//int getNumberofLines(review* reviewPointer) {
//	return 0;
//}
//
//int getNumberofLines(string filepath) {
//	int numberOfLines = 0;
//	string lines;
//
//	ifstream file(filepath);
//	while (getline(file, lines)) {
//		if (!lines.empty()) {
//			++numberOfLines;
//		}
//	}
//	file.close();
//	return numberOfLines;
//}
//
//transaction* transactionCreate(string filepath) {
//	cout << "Creating Transaction Array." << endl;
//	string custId, product, category, price, date, paymentMethod;
//
//	int numberOfTransaction = 0;
//	string lines;
//	int index = 0;
//
//
//	ifstream file(filepath);
//
//	if (!file.good()) {
//		cout << "Something wrong with transaction file!" << endl;
//		return nullptr;
//	}
//
//
//	//transaction* transactionList = new transaction[numberOfTransaction];
//	transaction* transactionList = new transaction[index + 1];
//	int numOfLineInFile = getNumberofLines(filepath);
//
//
//	/*
//	idea 1
//	create new while, get number, crete array
//	 
//	idea 2
//	create array, if there is new data, create and copy old array + 1, add item
//
//
//	4183??? shd be 4128
//	price got NaN, date got "Invalid Date"
//	neeed to filter those out
//
//	*/
//
//	while (file.good()) {
//		getline(file, custId, ',');
//		getline(file, product, ',');
//		getline(file, category, ',');
//		getline(file, price, ',');
//		getline(file, date, ',');
//		getline(file, paymentMethod);
//		if (custId == "Customer ID") {
//			continue;
//		}
//		if (custId == "" && product == "" && category == "" && price == "" && date == "" && paymentMethod == "") {
//			break; // stops when no more records
//		}
//		if (custId == "" || product == "" || category == "" || price == "" || date == "" || paymentMethod == "") { // data cleaning line
//			continue; // skip missing values
//		}
//		if (isnan(stod(price))) { // check for NaN price value
//			continue;
//		}
//		if (date == "Invalid Date") { // check if the text is invalid date, need to create another checker for invalid date that is NOT written in "Invalid Date"
//			continue;
//		}
//
//		// TODO: optimize this part of the code, maybe use back idea 1
//		transaction* oldtransactionList = transactionList;
//		transactionList = new transaction[index + 1];
//		for (int i = 0; i < index; i++) {
//			transactionList[i] = oldtransactionList[i];
//		}
//		//cout << index+1 << endl;
//		delete[] oldtransactionList;
//		
//
//		// add item into array
//		transactionList[index].setCustId(custId);
//		transactionList[index].setProduct(product);
//		transactionList[index].setCatagory(category);
//		transactionList[index].setPrice(stod(price));
//		transactionList[index].setDate(date);
//		transactionList[index].setPaymentMethod(paymentMethod);
//
//		index++;
//		
//	}
//
//	cout << "Transaction Array Created!" << endl;
//	return transactionList;
//}
//
//review* reviewCreate(string filepath) {
//	//cout << "Creating Review Array.. " << endl;
//	//string prodId, custId, rating, reviewText;
//
//	//int numberOfReview = 0;
//	//string lines;
//	//int index = 0;
//
//
//	//ifstream file(filepath);
//
//	//if (!file.good()) {
//	//	cout << "Something wrong with review file!" << endl;
//	//	return nullptr;
//	//}
//
//	////numberOfReview = getNumberofLines(filepath);
//	////// 3372
//	////cout << numberOfReview << endl;
//
//	////review* reviewList = new review[numberOfReview-1];
//
//	//review* reviewList = new review[index + 1];
//
//	//while (file.good()) {
//	//	getline(file, prodId, ',');
//	//	getline(file, custId, ',');
//	//	getline(file, rating, ',');
//	//	getline(file, reviewText);
//	//	if (prodId == "Product ID") {
//	//		continue;
//	//	}
//	//	if (prodId == "" && custId == "" && rating == "" && reviewText == "") {
//	//		break; // stops when no more records
//	//	}
//	//	if (prodId == "" || custId == "" || rating == "" || reviewText == "") { // data cleaning line
//	//		continue; // skip missing values
//	//	}
//	//	// test if the rating can convert to interger
//	//	try {
//	//		stoi(rating);
//	//	}
//	//	catch (exception& err) {
//	//		continue;
//	//	}
//	//	
//	//	//TODO: same as the on for transaction, need to optimize
//	//	review* oldReivewList = reviewList;
//	//	reviewList = new review[index + 1];
//	//	for (int i = 0; i < index; i++) {
//	//		reviewList[i] = oldReivewList[i];
//	//	}
//	//	//cout << index + 1 << endl;
//	//	delete[] oldReivewList;
//
//	//	// array creation
//	//	reviewList[index].setProdId(prodId);
//	//	reviewList[index].setCustId(custId);
//	//	reviewList[index].setRating(stoi(rating));
//	//	reviewList[index].setReviewText(reviewText);
//
//	//	index++;
//	//}
//
//	//cout << "Review Array Created!" << endl;
//	//return reviewList;
//}