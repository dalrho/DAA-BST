#include <iostream>
#include "Tree24.hpp"

using namespace std;

int main() {
    Tree24 t;

    int choice, value;

    while (true) {
        cout << "\n===== BTREE MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Find\n";
        cout << "4. Print\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                t.insert(value);
                cout << "Inserted.\n";
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                t.remove(value);
                cout << "Deleted (if existed).\n";
                break;

            case 3: 
                cout << "Enter value to find: ";
                cin >> value;

                if (t.find(value))
                    cout << "Found!\n";
                else
                    cout << "Not found.\n";
                break;

            case 4:
                cout << "\nTree Structure:\n";
                t.print();
                break;

            case 0:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}