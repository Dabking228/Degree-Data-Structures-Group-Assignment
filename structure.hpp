#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
using namespace std;

struct transaction {
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
			double checkPrice = stod(priceStr);
			if (!isnan(checkPrice)) {
				this->price = checkPrice;
			}
			else {
				throw invalid_argument("Transaction Price is invalid!");
			}
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

	inline static bool isValidTransaction(string custId, string product, string category, string priceStr, string date, string paymentMethod) {
		if (custId.empty() || product.empty() || category.empty() || priceStr.empty() || date.empty() || paymentMethod.empty()) {
			return false;
		}

		try {
			double price = stod(priceStr);
			if (isnan(price)) {
				return false;
			}

			if (date == "Invalid Date") {
				return false;
			}
			return true;
		}
		catch (...) {
			return false;
		}
		return false;
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

	// Setters
	void setCustId(string custId) {
		this->custId = custId;
	}
	void setProduct(string product) {
		this->product = product;
	}
	void setCategory(string category) {
		this->category = category;
	}
	void setPrice(string priceStr) {
		try {
			double checkPrice = stod(priceStr);
			if (!isnan(checkPrice)) {
				this->price = checkPrice;
			}
			else {
				return;
			}
		}
		catch (...) {
			return;
		}
	}
	void setDate(string date) {
		this->date = date;
	}
	void setPaymentMethod(string paymentMethod) {
		this->paymentMethod = paymentMethod;
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

	inline static bool isValidReview(string prodId, string custId, string ratingStr, string reviewText) {
		if (prodId.empty() || custId.empty() || ratingStr.empty() || reviewText.empty()) {
			return false;
		}

		try {
			int rating = stoi(ratingStr);
			return true;
		}
		catch (...) {
			return false;
		}
		return false;
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

	// Setters
	void setProdId(string prodId) {
		this->prodId = prodId;
	}
	void setCustId(string custId) {
		this->custId = custId;
	}
	void setRating(string ratingStr) {
		try {
			this->rating = stoi(ratingStr);
		}
		catch (...) {
			return;
		}
	}
	void setReviewText(string reviewText) {
		this->reviewText = reviewText;
	}
};

struct WordFrequency {
	// Attributes
private:
	string word;
	int frequency;
public:
	// Constructors
	WordFrequency(){}

	WordFrequency(string word, int frequency) {
		this->word = word;
		this->frequency = frequency;
	}
	
	// Getters
	string getWord() const{
		return word;
	}
	int getFrequency() const{
		return frequency;
	}

	// Setters
	void setWord(string word) {
		this->word = word;
	}
	void setFrequency(int frequency) {
		this->frequency = frequency;
	}

	// Add Frequency
	void addFrequency() {
		this->frequency += 1;
	}
};
