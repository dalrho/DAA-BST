#include "node.hpp"
#include <iostream>

using namespace std;

class GenTree {
protected:
    node* root;
    int size;

public:
    GenTree() {
        root = nullptr;
        size = 0;
    }

    virtual node* addRoot(int key) = 0;

    // We avoid general operations since we are dealing with search trees here
    // We cannot have a pure general tree and a search tree at the same time
    // virtual void insertKey(node*, int) = 0;
    // virtual void removeKey(node*, int) = 0;

    node* getRoot() { return root; }
    int getSize() { return size; }

    void print_node(string prefix, node* n) {
        cout << prefix << "[ ";
        for (int i = 0; i < n->num_keys; i++)
            cout << n->keys[i] << " ";
        cout << "]\n";

        for (int i = 0; i < n->num_child; i++) {
            print_node(prefix + "  ", n->children[i]);
        }
    }

    void print() {
        if (!root) {
            cout << "EMPTY\n";
            return;
        }
        print_node("", root);
    }
    void setRoot(node* newRoot) { root = newRoot; }
};