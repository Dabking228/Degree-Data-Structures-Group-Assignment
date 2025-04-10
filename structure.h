#pragma once
#include <iostream>
using namespace std;

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

	// Destructor
	~review() {
		cout << "Review for " << prodId << " by " << custId << " is deleted!" << endl;
	}
};

struct transactionNode {
	transactionNode* prevnode;
	transaction _transaction;
	transactionNode* nextnode;
};

struct reviewNode {
	reviewNode* prevnode;
	review* _review;
	reviewNode* nextnode;
};