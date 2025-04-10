#pragma once
#include <iostream>
using namespace std;

struct transaction
{
	string custId;
	string product;
	string catagory;
	double price;
	string date;
	string paymentMethod;
};

struct review {
	string prodId;
	string custId;
	int rating;
	string reviewText;
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