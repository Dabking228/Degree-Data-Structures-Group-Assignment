#pragma once
#include <iostream>
using namespace std;

struct transaction {
	// Attributes
	string custId;
	string product;
	string category;
	double price;
	string date;
	string paymentMethod;
};

struct review {
	// Attributes
	string prodId;
	string custId;
	int rating;
	string reviewText;
};
