#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class transaction {
	// Attributes
private:
	string custId;
	string product;
	string category;
	double price;
	string date;
	string paymentMethod;

public:
	// Constructors
	transaction(){}

	transaction(string custId, string product, string category, string priceStr, string date, string paymentMethod) {
		if (custId.empty() || product.empty() || category.empty() || priceStr.empty() || date.empty() || paymentMethod.empty()) {
			throw invalid_argument("Transaction has missing field(s)!");
		}

		if (date == "Invalid Date") {
			throw invalid_argument("Transaction Date = Invalid Date!");
		}

		try {
			price = stod(priceStr);
		}
		catch (...) {
			throw invalid_argument("Transaction Price is invalid!");
		}

		this->custId = custId;
		this->product = product;
		this->category = category;
		this->date = date;
		this->paymentMethod = paymentMethod;
	}

	// Getters
	string getCustId() const{
		return custId;
	}
	string getProduct() const{
		return product;
	}
	string getCategory() const {
		return category;
	}
	double getPrice() const {
		return price;
	}
	string getDate() const {
		return date;
	}
	string getPaymentMethod() const{
		return paymentMethod;
	}
};

struct review {
	// Attributes
private:
	string prodId;
	string custId;
	int rating;
	string reviewText;

public:
	// Constructors
	review(){}

	review(string prodId, string custId, string ratingStr, string reviewText) {
		if (prodId.empty() || custId.empty() || ratingStr.empty() || reviewText.empty()) {
			throw invalid_argument("Review has missing field(s)!");
		}

		try {
			rating = stoi(ratingStr);
		}
		catch (...) {
			throw invalid_argument("Review Rating = Invalid Rating!");
		}

		this->prodId = prodId;
		this->custId = custId;
		this->reviewText = reviewText;
	}

	// Getters
	string getProdId() const{
		return prodId;
	}
	string getCustId() const {
		return custId;
	}
	int getRating() const {
		return rating;
	}
	string getReviewText() const{
		return reviewText;
	}
};
