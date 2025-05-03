#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

void sortTransactionsMenu();
void searchTransactionsMenu();
void sortReviewsMenu();
void searchReviewsMenu();

int main() {
    int choice;
    bool running = true;

    while (running) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Sort transactions" << endl;
        cout << "2. Search transactions" << endl;
        cout << "3. Sort reviews" << endl;
        cout << "4. Search reviews" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            sortTransactionsMenu();
            break;
        case 2:
            searchTransactionsMenu();
            break;
        case 3:
            sortReviewsMenu();
            break;
        case 4:
            searchReviewsMenu();
            break;
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

void sortTransactionsMenu() {
    int structureChoice, sortChoice, columnChoice, orderChoice;
    string columnName;

    cout << "\n=== Sort Transactions ===" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> structureChoice) || structureChoice < 1 || structureChoice > 2) {
        cout << "Invalid input for structure choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nSorting Algorithm:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
        cout << "Invalid input for sort algorithm choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nAvailable columns: Customer ID, Product, Price, Date, Category, Payment Method" << endl;
    cout << "Enter column name to sort by: ";
    cin >> columnName;

    cout << "\nSort Order:" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> orderChoice) || orderChoice < 1 || orderChoice > 2) {
        cout << "Invalid input for sort order choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    string structure = (structureChoice == 1) ? "Array" : "Linked List";
    string algorithm = (sortChoice == 1) ? "Bubble Sort" : "Merge Sort";
    string order = (orderChoice == 1) ? "Ascending" : "Descending";

    cout << "\nSorting transactions in " << structure << " using " << algorithm
        << " by " << columnName << " in " << order << " order." << endl;
}

void searchTransactionsMenu() {
    int structureChoice, searchChoice, columnChoice;
    string columnName, keyword;

    cout << "\n=== Search Transactions ===" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> structureChoice) || structureChoice < 1 || structureChoice > 2) {
        cout << "Invalid input for structure choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nSearch Algorithm:" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 2) {
        cout << "Invalid input for search algorithm choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nAvailable columns: Customer ID, Product, Price, Date, Category, Payment Method" << endl;
    cout << "Enter column name to search in: ";
    cin >> columnName;

    cout << "Enter keyword to search for: ";
    cin.ignore();
    getline(cin, keyword);

    string structure = (structureChoice == 1) ? "Array" : "Linked List";
    string algorithm = (searchChoice == 1) ? "Linear Search" : "Binary Search";

    cout << "\nSearching transactions in " << structure << " using " << algorithm
        << " in column " << columnName << " for keyword: " << keyword << endl;
}

void sortReviewsMenu() {
    int structureChoice, sortChoice, columnChoice, orderChoice;
    string columnName;

    cout << "\n=== Sort Reviews ===" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> structureChoice) || structureChoice < 1 || structureChoice > 2) {
        cout << "Invalid input for structure choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nSorting Algorithm:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
        cout << "Invalid input for sort algorithm choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nAvailable columns: Product ID, Customer ID, Rating, Review Text" << endl;
    cout << "Enter column name to sort by: ";
    cin >> columnName;

    cout << "\nSort Order:" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> orderChoice) || orderChoice < 1 || orderChoice > 2) {
        cout << "Invalid input for sort order choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    string structure = (structureChoice == 1) ? "Array" : "Linked List";
    string algorithm = (sortChoice == 1) ? "Bubble Sort" : "Merge Sort";
    string order = (orderChoice == 1) ? "Ascending" : "Descending";

    cout << "\nSorting reviews in " << structure << " using " << algorithm
        << " by " << columnName << " in " << order << " order." << endl;
}

void searchReviewsMenu() {
    int structureChoice, searchChoice, columnChoice;
    string columnName, keyword;

    cout << "\n=== Search Reviews ===" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> structureChoice) || structureChoice < 1 || structureChoice > 2) {
        cout << "Invalid input for structure choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nSearch Algorithm:" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "Enter your choice (1-2): ";

    if (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 2) {
        cout << "Invalid input for search algorithm choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "\nAvailable columns: Product ID, Customer ID, Rating, Review Text" << endl;
    cout << "Enter column name to search in: ";
    cin >> columnName;

    cout << "Enter keyword to search for: ";
    cin.ignore();
    getline(cin, keyword);

    string structure = (structureChoice == 1) ? "Array" : "Linked List";
    string algorithm = (searchChoice == 1) ? "Linear Search" : "Binary Search";

    cout << "\nSearching reviews in " << structure << " using " << algorithm
        << " in column " << columnName << " for keyword: " << keyword << endl;
}