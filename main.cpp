#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std;


int main() {
    BinarySearchTree tree;
    int choice, val;

    while (true) {
        cout << "\n===== BST MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Find\n";
        cout << "4. Print (Inorder)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                tree.insert(val);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> val;
                if (tree.remove(val)) cout << "Deleted\n";
                else cout << "Not found\n";
                break;

            case 3:
                cout << "Enter value: ";
                cin >> val;
                if (tree.findNode(tree.getRoot(), val))
                    cout << "Found\n";
                else
                    cout << "Not found\n";
                break;

            case 4:
                tree.print();
                break;

            case 0:
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}