#include "Array.hpp"
#include <iostream>
using namespace std;
string TrnasFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

int main() {
	Array<transaction> _Transaction(TrnasFILENAME);
	Array<review> _review(ReviewFILENAME);

	// init this
	_Transaction.createArray();

	transaction* arrayTransaction = _Transaction.getArray();
	cout << _Transaction.getArrayLength() << endl;

	//for (int i = 0; i < _Transaction.getArrayLength(); i++) {
	//	cout << arrayTransaction->category << " | "
	//		<< arrayTransaction->custId << " | "
	//		<< arrayTransaction->date << " | "
	//		<< arrayTransaction->paymentMethod << " | "
	//		<< arrayTransaction->price << " | "
	//		<< arrayTransaction->product << endl;
	//}
}

