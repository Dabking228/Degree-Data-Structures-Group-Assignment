#include <iostream>
#include <fstream>
#include <sstream>
#include "structure.h"
#include "createList.h"
string TransFILENAME = "transactions.csv";
string reviewFILENAME = "reviews.csv";

void showArray() {
	int transNumOfLines = getNumberofLines(TransFILENAME);
	int reviewNumOfLines = getNumberofLines(reviewFILENAME);

	transaction* transArray = transactionCreate(TransFILENAME);
	review* reviewArray = reviewCreate(reviewFILENAME);

	for (int i = 0; i < transNumOfLines; i++) {
		cout << transArray[i].getCustId() << ", " << transArray[i].getProduct() << ", " << transArray[i].getCategory() << endl;
	}

	for (int i = 0; i < reviewNumOfLines; i++) {
		cout << reviewArray[i].getCustId() << ", " << reviewArray[i].getProdId() << ", " << reviewArray[i].getRating() << ", " << reviewArray[i].getReviewText() << endl;
	}

	delete[] transArray;
	delete[] reviewArray;
}

int main() {

}