//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <chrono>
//#include "structure.h"
//#include "createList.h"
//#include "CreateArray.h"
//string TransFILENAME = "./datasets/transactions_cleaned.csv";
//string reviewFILENAME = "./datasets/reviews_cleaned.csv";
//
//void showArray() {
//	transaction* transArray = transactionCreate(TransFILENAME);
//	review* reviewArray = reviewCreate(reviewFILENAME);
//
//	int transNumOfLines = getNumberofLines(transArray);
//	int reviewNumOfLines = getNumberofLines(reviewArray);
//
//	for (int i = 0; i < transNumOfLines; i++) {
//		cout << transArray[i].getCustId() << ", " << transArray[i].getProduct() << ", " << transArray[i].getCategory() << endl;
//	}
//
//	for (int i = 0; i < reviewNumOfLines; i++) {
//		cout << reviewArray[i].getCustId() << ", " << reviewArray[i].getProdId() << ", " << reviewArray[i].getRating() << ", " << reviewArray[i].getReviewText() << endl;
//	}
//
//	delete[] transArray;
//	delete[] reviewArray;
//}
//
//int main() {
//	chrono::time_point<chrono::system_clock> Tstart, Tend, Rstart, Rend;
//
//	Tstart = chrono::system_clock::now();
//	transaction* temp = transactionCreate(TransFILENAME);
//	Tend = chrono::system_clock::now();
//
//	chrono::duration<double> Ttaken = Tend - Tstart;
//	cout << "time take: " << Ttaken.count() << endl;
//
//	Rstart = chrono::system_clock::now();
//	review* temp2 = reviewCreate(reviewFILENAME);
//	Rend = chrono::system_clock::now();
//
//	chrono::duration<double> Rtaken = Rend - Rstart;
//	cout << "time take: " << Rtaken.count() << endl;
//
//}