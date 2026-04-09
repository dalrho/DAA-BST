
#include "GenTree.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

class MyGenTree : public GenTree {


public:
    MyGenTree() {
        root = nullptr;
        size = 0;
    }

    node* addRoot(int key) {
        if (root) throw logic_error("Root exists");

        root = new node();
        root->keys[0] = key;
        root->num_keys = 1;
        size++;
        return root;
    }

    node* addChild(node* parent, int key) {
        node* child = new node();
        child->keys[0] = key;
        child->num_keys = 1;
        child->parent = parent;

        parent->children[parent->num_child++] = child;
        size++;
        return child;
    }

    void remove(node* n) {
        if (!n) return;

        if (n == root) {
            delete n;
            root = nullptr;
            size--;
            return;
        }

        node* p = n->parent;

        int idx = -1;
        for (int i = 0; i < p->num_child; i++) {
            if (p->children[i] == n) {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            for (int i = idx; i < p->num_child - 1; i++) {
                p->children[i] = p->children[i + 1];
            }
            p->num_child--;
        }

        delete n;
        size--;
    }

    int getSize() { return size; }
    node* getRoot() { return root; }
};