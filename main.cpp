#include "Array.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <chrono>
#include <limits>
#include <string>
using namespace std;

string TransactionFILENAME = "./datasets/transactions.csv";
string ReviewFILENAME = "./datasets/reviews.csv";

enum sortBy {
    BubbleSort = 1,
    MergeSort = 2
};

enum sortColTransaction {
    trans_custId = 1,
    trans_product = 2,
    trans_category = 3,
    trans_price = 4,
    trans_date = 5,
    trans_paymentMethod = 6
};

enum sortColReview {
    rv_custId = 1,
    rv_prodId = 2,
    rv_rating = 3,
    rv_reviewText = 4
};

namespace {
    LinkedList<transaction> _TransactionLinked(TransactionFILENAME);
    LinkedList<review> _ReviewLinked(ReviewFILENAME);

    Array<transaction> _TransactionArray(TransactionFILENAME);
    Array<review> _ReviewArray(ReviewFILENAME);
}

void initializeData() {
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    _TransactionLinked.createLinkedList();
    _ReviewLinked.createLinkedList();

    _TransactionArray.createArray();
    _ReviewArray.createArray();

    end = chrono::system_clock::now();
    chrono::duration<double> taken = end - start;
    cout << "Data initialization time: " << taken.count() << " seconds" << endl;
}

void displayTransactionSortResults(Array<transaction>* sortedArray, int sortColumn) {
    for (int i = 0; i < min(10, sortedArray->getArrayLength()); i++) {
        switch (sortColumn) {
        case trans_custId:
            cout << i << " : Customer ID - " << sortedArray->getArray()[i].getCustId() << endl;
            break;
        case trans_product:
            cout << i << " : Product - " << sortedArray->getArray()[i].getProduct() << endl;
            break;
        case trans_category:
            cout << i << " : Category - " << sortedArray->getArray()[i].getCategory() << endl;
            break;
        case trans_price:
            cout << i << " : Price - " << sortedArray->getArray()[i].getPrice() << endl;
            break;
        case trans_date:
            cout << i << " : Date - " << sortedArray->getArray()[i].getDate() << endl;
            break;
        case trans_paymentMethod:
            cout << i << " : Payment Method - " << sortedArray->getArray()[i].getPaymentMethod() << endl;
            break;
        }
    }
}

void displayReviewSortResults(Array<review>* sortedArray, int sortColumn) {
    for (int i = 0; i < min(10, sortedArray->getArrayLength()); i++) {
        switch (sortColumn) {
        case rv_custId:
            cout << i << " : Customer ID - " << sortedArray->getArray()[i].getCustId() << endl;
            break;
        case rv_prodId:
            cout << i << " : Product ID - " << sortedArray->getArray()[i].getProdId() << endl;
            break;
        case rv_rating:
            cout << i << " : Rating - " << sortedArray->getArray()[i].getRating() << endl;
            break;
        case rv_reviewText:
            cout << i << " : Review Text - " << sortedArray->getArray()[i].getReviewText() << endl;
            break;
        }
    }
}

int main() {
    initializeData();

    int choice;
    bool running = true;

    while (running) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Sort transactions" << endl;
        cout << "2. Search transactions" << endl;
        cout << "3. Sort reviews" << endl;
        cout << "4. Search reviews" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5, -1 to go back): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == -1) {
            cout << "Already at main menu." << endl;
            continue;
        }

        switch (choice) {
        case 1: { // Sort transactions
            int structureChoice;
            cout << "\n=== Sort Transactions ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> structureChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (structureChoice == -1) continue;
            if (structureChoice < 1 || structureChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int sortChoice;
            cout << "\nSorting Algorithm:" << endl;
            cout << "1. Bubble Sort" << endl;
            cout << "2. Merge Sort" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> sortChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (sortChoice == -1) continue;
            if (sortChoice < 1 || sortChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int columnChoice;
            cout << "\nAvailable columns:" << endl;
            cout << "1. Customer ID" << endl;
            cout << "2. Product" << endl;
            cout << "3. Category" << endl;
            cout << "4. Price" << endl;
            cout << "5. Date" << endl;
            cout << "6. Payment Method" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter column number to sort by (1-6, -1 to go back): ";

            if (!(cin >> columnChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (columnChoice == -1) continue;
            if (columnChoice < 1 || columnChoice > 6) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int orderChoice;
            cout << "\nSort Order:" << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> orderChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (orderChoice == -1) continue;
            if (orderChoice < 1 || orderChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            bool ascending = (orderChoice == 1); // convert to bool when asce is selected

            // Perform the sorting
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<transaction>* sortedArray = _TransactionArray.clone();
                sortedArray->sortBy(static_cast<sortBy>(sortChoice), static_cast<sortColTransaction>(columnChoice), ascending);

                cout << "\nSorting completed. First 10 results:" << endl;
                displayTransactionSortResults(sortedArray, columnChoice);

                delete sortedArray;
            }
            else { // Linked List
                LinkedList<transaction>* sortedList = _TransactionLinked.clone();
                sortedList->sortBy(static_cast<sortBy>(sortChoice), static_cast<sortColTransaction>(columnChoice), ascending);

                cout << "\nSorting completed. First 10 results:" << endl;
                int displayCount = min(10, sortedList->getListLength());
                Node<transaction>* current = sortedList->getHEAD();
                for (int i = 0; i < displayCount && current != nullptr; i++) {
                    switch (columnChoice) {
                    case trans_custId:
                        cout << i << " : Customer ID - " << current->_T->getCustId()<< endl;
                        break;
                    case trans_product:
                        cout << i << " : Product - " << current->_T->getProduct() << endl;
                        break;
                    case trans_category:
                        cout << i << " : Category - " << current->_T->getCategory() << endl;
                        break;
                    case trans_price:
                        cout << i << " : Price - " << current->_T->getPrice() << endl;
                        break;
                    case trans_date:
                        cout << i << " : Date - " << current->_T->getDate() << endl;
                        break;
                    case trans_paymentMethod:
                        cout << i << " : Payment Method - " << current->_T->getPaymentMethod() << endl;
                        break;
                    }
                    current = current->nextnode;
                }

                delete sortedList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nSorting time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 2: { // Search transactions
            int structureChoice;
            cout << "\n=== Search Transactions ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> structureChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (structureChoice == -1) continue;
            if (structureChoice < 1 || structureChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int searchChoice;
            cout << "\nSearch Algorithm:" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> searchChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (searchChoice == -1) continue;
            if (searchChoice < 1 || searchChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int columnChoice;
            cout << "\nAvailable columns:" << endl;
            cout << "1. Customer ID" << endl;
            cout << "2. Product" << endl;
            cout << "3. Category" << endl;
            cout << "4. Price" << endl;
            cout << "5. Date" << endl;
            cout << "6. Payment Method" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter column number to search in (1-6, -1 to go back): ";

            if (!(cin >> columnChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (columnChoice == -1) continue;
            if (columnChoice < 1 || columnChoice > 6) {
                cout << "Invalid choice." << endl;
                continue;
            }

            string keyword;
            cout << "Enter keyword to search for (or -1 to go back): ";
            cin.ignore();
            getline(cin, keyword);

            if (keyword == "-1") continue;

            // Perform the search
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<transaction>* searchArray = _TransactionArray.clone();
                if (searchChoice == 2) { // Binary search requires sorted data
                    searchArray->sortBy(BubbleSort, static_cast<sortColTransaction>(columnChoice), true);
                }

                // Implement search logic here
                // searchArray->search(static_cast<sortColTransaction>(columnChoice), keyword);

                delete searchArray;
            }
            else { // Linked List
                LinkedList<transaction>* searchList = _TransactionLinked.clone();
                if (searchChoice == 2) { // Binary search requires sorted data
                    searchList->sortBy(BubbleSort, static_cast<sortColTransaction>(columnChoice), true);
                }

                // Implement search logic here
                // searchList->search(static_cast<sortColTransaction>(columnChoice), keyword);

                delete searchList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nSearch time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 3: { // Sort reviews
            int structureChoice;
            cout << "\n=== Sort Reviews ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> structureChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (structureChoice == -1) continue;
            if (structureChoice < 1 || structureChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int sortChoice;
            cout << "\nSorting Algorithm:" << endl;
            cout << "1. Bubble Sort" << endl;
            cout << "2. Merge Sort" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> sortChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (sortChoice == -1) continue;
            if (sortChoice < 1 || sortChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int columnChoice;
            cout << "\nAvailable columns:" << endl;
            cout << "1. Customer ID" << endl;
            cout << "2. Product ID" << endl;
            cout << "3. Rating" << endl;
            cout << "4. Review Text" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter column number to sort by (1-4, -1 to go back): ";

            if (!(cin >> columnChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (columnChoice == -1) continue;
            if (columnChoice < 1 || columnChoice > 4) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int orderChoice;
            cout << "\nSort Order:" << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> orderChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (orderChoice == -1) continue;
            if (orderChoice < 1 || orderChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            bool ascending = (orderChoice == 1);

            // Perform the sorting
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<review>* sortedArray = _ReviewArray.clone();
                sortedArray->sortBy(static_cast<sortBy>(sortChoice), static_cast<sortColReview>(columnChoice), ascending);

                cout << "\nSorting completed. First 10 results:" << endl;
                displayReviewSortResults(sortedArray, columnChoice);

                delete sortedArray;
            }
            else { // Linked List
                LinkedList<review>* sortedList = _ReviewLinked.clone();
                sortedList->sortBy(static_cast<sortBy>(sortChoice), static_cast<sortColReview>(columnChoice), ascending);

                cout << "\nSorting completed. First 10 results:" << endl;
                int displayCount = min(10, sortedList->getListLength());
                Node<review>* current = sortedList->getHEAD();
                for (int i = 0; i < displayCount && current != nullptr; i++) {
                    switch (columnChoice) {
                    case rv_custId:
                        cout << i << " : Customer ID - " << current->_T->getCustId() << endl;
                        break;
                    case rv_prodId:
                        cout << i << " : Product ID - " << current->_T->getProdId() << endl;
                        break;
                    case rv_rating:
                        cout << i << " : Rating - " << current->_T->getRating() << endl;
                        break;
                    case rv_reviewText:
                        cout << i << " : Review Text - " << current->_T->getReviewText() << endl;
                        break;
                    }
                    current = current->nextnode;
                }

                delete sortedList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nSorting time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 4: { // Search reviews
            int structureChoice;
            cout << "\n=== Search Reviews ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> structureChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (structureChoice == -1) continue;
            if (structureChoice < 1 || structureChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int searchChoice;
            cout << "\nSearch Algorithm:" << endl;
            cout << "1. Linear Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter your choice (1-2, -1 to go back): ";

            if (!(cin >> searchChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (searchChoice == -1) continue;
            if (searchChoice < 1 || searchChoice > 2) {
                cout << "Invalid choice." << endl;
                continue;
            }

            int columnChoice;
            cout << "\nAvailable columns:" << endl;
            cout << "1. Customer ID" << endl;
            cout << "2. Product ID" << endl;
            cout << "3. Rating" << endl;
            cout << "4. Review Text" << endl;
            cout << "-1. Back" << endl;
            cout << "Enter column number to search in (1-4, -1 to go back): ";

            if (!(cin >> columnChoice)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (columnChoice == -1) continue;
            if (columnChoice < 1 || columnChoice > 4) {
                cout << "Invalid choice." << endl;
                continue;
            }

            string keyword;
            cout << "Enter keyword to search for (or -1 to go back): ";
            cin.ignore();
            getline(cin, keyword);

            if (keyword == "-1") continue;

            // Perform the search
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<review>* searchArray = _ReviewArray.clone();
                if (searchChoice == 2) { // Binary search requires sorted data
                    searchArray->sortBy(BubbleSort, static_cast<sortColReview>(columnChoice), true);
                }

                // Implement search logic here
                // searchArray->search(static_cast<sortColReview>(columnChoice), keyword);

                delete searchArray;
            }
            else { // Linked List
                LinkedList<review>* searchList = _ReviewLinked.clone();
                if (searchChoice == 2) { // Binary search requires sorted data
                    searchList->sortBy(BubbleSort, static_cast<sortColReview>(columnChoice), true);
                }

                // Implement search logic here
                // searchList->search(static_cast<sortColReview>(columnChoice), keyword);

                delete searchList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nSearch time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 5:
            running = false;
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }
    }

    return 0;
}