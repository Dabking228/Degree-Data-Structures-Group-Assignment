#include "Array.hpp"
#include "LinkedList.hpp"
#include "Utils.hpp"
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
        transaction t = sortedArray->getArray()[i];
        cout << i << " : "
            << "Customer ID: " << t.getCustId() << " | "
            << "Product: " << t.getProduct() << " | "
            << "Category: " << t.getCategory() << " | "
            << "Price: " << t.getPrice() << " | "
            << "Date: " << t.getDate() << " | "
            << "Payment Method: " << t.getPaymentMethod()
            << endl;
    }
}

void displayReviewSortResults(Array<review>* sortedArray, int sortColumn) {
    for (int i = 0; i < min(10, sortedArray->getArrayLength()); i++) {
        review r = sortedArray->getArray()[i];
        cout << i << " : "
            << "Customer ID: " << r.getCustId() << " | "
            << "Product ID: " << r.getProdId() << " | "
            << "Rating: " << r.getRating() << " | "
            << "Review Text: " << r.getReviewText()
            << endl;
    }
}

string callSearch(int columnChoice, string data) {

    if (data == "transaction") {
        if (columnChoice == 1) return "customerid";
        else if (columnChoice == 2) return "product";
        else if (columnChoice == 3) return "category";
        else if (columnChoice == 4) return "price";
        else if (columnChoice == 5) return "date";
        else if (columnChoice == 6) return "paymentmethod";
    }

    else if (data == "review") {
        if (columnChoice == 1) return "customerid";
        else if (columnChoice == 2) return "productid";
        else if (columnChoice == 3) return "rating";
        else if (columnChoice == 4) return "review";
    }

    return "invalid";
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
        cout << "5. Review analysis" << endl;
        cout << "Enter your choice (1-5, -1 to exit): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == -1) {
            cout << "System shutting down..." << endl;
            return 0;
        }

        switch (choice) {
        case 1: { // Sort transactions
            int structureChoice;
            cout << "\n=== Sort Transactions ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter column number to sort by (1-6, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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

                    // Display all fields for the current transaction
                    cout << i << ":"
                    << " Customer ID: " << current->_T->getCustId()
                    << " Product: " << current->_T->getProduct() 
                    << " Category: " << current->_T->getCategory() 
                    << " Price: " << current->_T->getPrice() 
                    << " Date: " << current->_T->getDate()
                    << " Payment Method: " << current->_T->getPaymentMethod() << endl;

                    current = current->nextnode;
                }

                delete sortedList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nOverall sorting time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 2: { // Search transactions
            int structureChoice;
            cout << "\n=== Search Transactions ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter column number to search in (1-6, -1 to go back to main menu): ";

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
            cout << "Enter keyword to search for (or -1 to go back to main menu): ";
            cin.ignore();
            getline(cin, keyword);

            if (keyword == "-1") continue;

            // Perform the search
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<transaction>* searchArray = _TransactionArray.clone();
                string category = callSearch(columnChoice, "transaction");

                if (searchChoice == 1) { // Linear search
                    searchArray->arrayLinearSearch(category, keyword);
                }

                if (searchChoice == 2) { // Binary search requires sorted data
                    cout << "Performing sorting for " << category << "... Please wait a moment..." << endl;
                    searchArray->sortBy(BubbleSort, static_cast<sortColTransaction>(columnChoice), true);
                    searchArray->arrayBinarySearch(category, keyword);
                }

                delete searchArray;
            }
            else { // Linked List
                LinkedList<transaction>* searchList = _TransactionLinked.clone();
                string category = callSearch(columnChoice, "transaction");

                if (searchChoice == 1) { // Linear search
                    searchList->linearSearch(category, keyword);
                }

                if (searchChoice == 2) { // Binary search requires sorted data
                    cout << "Performing sorting for " << category << "... Please wait a moment..." << endl;
                    searchList->sortBy(BubbleSort, static_cast<sortColTransaction>(columnChoice), true);
                    searchList->binarySearch(category, keyword);
                }

                delete searchList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nOverall search time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 3: { // Sort reviews
            int structureChoice;
            cout << "\n=== Sort Reviews ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter column number to sort by (1-4, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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

                    // Display all fields for the current review
                    cout << i << ":"
                    << " Customer ID: " << current->_T->getCustId()
                    << " Product ID: " << current->_T->getProdId() 
                    << " Rating: " << current->_T->getRating()
                    << " Review Text: " << current->_T->getReviewText() << endl;

                    current = current->nextnode;
                }

                delete sortedList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nOverall sorting time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 4: { // Search reviews
            int structureChoice;
            cout << "\n=== Search Reviews ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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
            cout << "-1. Back to main menu" << endl;
            cout << "Enter column number to search in (1-4, -1 to go back to main menu): ";

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
            cout << "Enter keyword to search for (or -1 to go back to main menu): ";
            cin.ignore();
            getline(cin, keyword);

            if (keyword == "-1") continue;

            // Perform the search
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<review>* searchArray = _ReviewArray.clone();
                string category = callSearch(columnChoice, "review");

                if (searchChoice == 1) { // Linear search
                    searchArray->arrayLinearSearch(category, keyword);
                }

                if (searchChoice == 2) { // Binary search requires sorted data
                    cout << "Performing sorting for " << category << "... Please wait a moment..." << endl;
                    searchArray->sortBy(BubbleSort, static_cast<sortColReview>(columnChoice), true);
                    searchArray->arrayBinarySearch(category, keyword);
                }

                delete searchArray;
            }
            else { // Linked List
                LinkedList<review>* searchList = _ReviewLinked.clone();
                string category = callSearch(columnChoice, "review");

                if (searchChoice == 1) { // Linear search
                    searchList->linearSearch(category, keyword);
                }

                if (searchChoice == 2) { // Binary search requires sorted data
                    cout << "Performing sorting for " << category << "... Please wait a moment..." << endl;
                    searchList->sortBy(BubbleSort, static_cast<sortColReview>(columnChoice), true);
                    searchList->binarySearch(category, keyword);
                }

                delete searchList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nOverall search time: " << taken.count() << " seconds" << endl;
            break;
        }
        case 5: {
            int structureChoice;
            cout << "\n=== Review Analysis ===" << endl;
            cout << "1. Array" << endl;
            cout << "2. Linked List" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Enter your choice (1-2, -1 to go back to main menu): ";

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

            int ratingInput;
            cout << "\nRatings: (To find most frequently used words in product reviews)" << endl;
            cout << "1. 1 Star" << endl;
            cout << "2. 2 Stars" << endl;
            cout << "3. 3 Stars" << endl;
            cout << "4. 4 Stars" << endl;
            cout << "5. 5 Stars" << endl;
            cout << "-1. Back to main menu" << endl;
            cout << "Select rating (1-5, -1 to go back to main menu): ";

            if (!(cin >> ratingInput)) {
                cout << "Invalid input." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (ratingInput == -1) continue;
            if (ratingInput < 1 || ratingInput > 5) {
                cout << "Invalid rating." << endl;
                continue;
            }

            // Perform review analysis
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            if (structureChoice == 1) { // Array
                Array<review>* reviewArray = _ReviewArray.clone();
                reviewArray->runArrayFindingMostFrequentWordInReview(ratingInput);
                delete reviewArray;
            }
            else { // Linked List
                LinkedList<review>* reviewList = _ReviewLinked.clone();
                reviewList->runLinkedListFindingMostFrequentWordInReview(ratingInput);
                delete reviewList;
            }

            end = chrono::system_clock::now();
            chrono::duration<double> taken = end - start;
            cout << "\nOverall time taken: " << taken.count() << " seconds" << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }
    }

    return 0;
}

