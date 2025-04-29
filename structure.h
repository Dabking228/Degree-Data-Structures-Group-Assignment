#pragma once
#include <iostream>
using namespace std;

// this file contains all class / struct for transaction and review

class transaction{
private:
	// Attributes
	string custId;
	string product;
	string category;
	double price;
	string date;
	string paymentMethod;

public:
	//Constructor
	transaction(string custId, string product, string category, double price, string date, string paymentMethod) {
		this->custId = custId;
		this->product = product;
		this->category = category;
		this->price = price;
		this->date = date;
		this->paymentMethod = paymentMethod;
	}
	transaction(){
		
	}

	// Getters
	string getCustId() {
		return custId;
	}

	string getProduct() {
		return product;
	}

	string getCategory() {
		return category;
	}

	double getPrice() {
		return price;
	}

	string getDate() {
		return date;
	}

	string getPaymentMethod() {
		return paymentMethod;
	}

	// Setter
	void setCustId(string custId) {
		this->custId = custId;
	}

	void setProduct(string product) {
		this->product = product;
	}

	void setCatagory(string category) {
		this->category = category;
	}

	void setPrice(double price) {
		this->price = price;
	}

	void setDate(string date) {
		this->date = date;
	}

	void setPaymentMethod(string paymentMethod) {
		this->paymentMethod = paymentMethod;
	}
	// Destructor
	~transaction() {
		cout << "Transaction done by " << custId << " for " << product << " on " << date << " is deleted!" << endl;
	}
};

class review {
private:
	// Attributes
	string prodId;
	string custId;
	int rating;
	string reviewText;

public:
	// Constructor
	review(string prodId, string custId, int rating, string reviewText) {
		this->prodId = prodId;
		this->custId = custId;
		this->rating = rating;
		this->reviewText = reviewText;
	}

	review() {}

	// Getters
	string getProdId() {
		return prodId;
	}

	string getCustId() {
		return custId;
	}

	int getRating() {
		return rating;
	}

	string getReviewText() {
		return reviewText;
	}

	// Setter
	void setProdId(string prodId) {
		this->prodId = prodId;
	}

	void setCustId(string custId) {
		this->custId = custId;
	}

	void setRating(int rating) {
		this->rating = rating;
	}

	void setReviewText(string review) {
		this->reviewText = review;
	}

	// Destructor
	~review() {
		cout << "Review for " << prodId << " by " << custId << " is deleted!" << endl;
	}
};

struct transactionNode {
	~transactionNode() {
		cout << "transaction node is deleted" << endl;
	}

	transactionNode* prevnode;
	transaction* _transaction;
	transactionNode* nextnode;
};

struct reviewNode {
	~reviewNode() {
		cout << "Review node is deleted" << endl;
	}

	reviewNode* prevnode;
	review* _review;
	reviewNode* nextnode;
};