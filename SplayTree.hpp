#include "MyBinaryTree.hpp"

using namespace std;

class SplayTree {
public:
    BinaryTree* tree = new MyBinaryTree();


    void rotateLeft(Node* x) {
        Node* y = x->right;
        if (!y) return;

        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->parent = x->parent;

        if (!x->parent) tree->setRoot(y);
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        if (!y) return;

        x->left = y->right;
        if (y->right) y->right->parent = x;

        y->parent = x->parent;

        if (!x->parent) tree->setRoot(y);
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->right = x;
        x->parent = y;
    }


    void splay(Node* x) {
        while (x->parent) {
            Node* p = x->parent;
            Node* g = p->parent;

            // ZIG
            if (!g) {
                if (x == p->left) rotateRight(p);
                else rotateLeft(p);
            }

            // ZIG-ZIG
            else if (x == p->left && p == g->left) {
                rotateRight(g);
                rotateRight(p);
            }
            else if (x == p->right && p == g->right) {
                rotateLeft(g);
                rotateLeft(p);
            }

            // ZIG-ZAG
            else {
                if (x == p->left) {
                    rotateRight(p);
                    rotateLeft(g);
                } else {
                    rotateLeft(p);
                    rotateRight(g);
                }
            }
        }
    }



    bool search(int key) {
        Node* curr = tree->getRoot();
        Node* last = nullptr;

        while (curr) {
            last = curr;

            if (key == curr->elem) {
                splay(curr);
                return true;
            }
            else if (key < curr->elem) curr = curr->left;
            else curr = curr->right;
        }

        // Not found, splay last visited
        if (last) splay(last);
        return false;
    }


    bool insert(int key) {
        Node* root = tree->getRoot();

        if (!root) {
            tree->addRoot(key);
            return true;
        }

        Node* curr = root;
        Node* parent = nullptr;

        while (curr) {
            parent = curr;

            if (key == curr->elem) {
                splay(curr); // duplicate, splay
                return false;
            }
            else if (key < curr->elem) curr = curr->left;
            else curr = curr->right;
        }

        Node* newNode;
        if (key < parent->elem)
            newNode = tree->addLeft(parent, key);
        else
            newNode = tree->addRight(parent, key);

        splay(newNode);
        return true;
    }


    bool remove(int key) {
        if (!search(key)) return false; 
        // search already splays

        Node* root = tree->getRoot();

        Node* leftSub = root->left;
        Node* rightSub = root->right;

        if (leftSub) leftSub->parent = nullptr;
        if (rightSub) rightSub->parent = nullptr;

        // Case 1: no left subtree
        if (!leftSub) {
            tree->setRoot(rightSub);
        }

        // Case 2: no right subtree
        else if (!rightSub) {
            tree->setRoot(leftSub);
        }

        // Case 3: both exist
        else {
            // Find leftmost of right subtree
            Node* minRight = rightSub;
            while (minRight->left) minRight = minRight->left;

            // Splay it
            splay(minRight);

            // Attach left subtree
            minRight->left = leftSub;
            leftSub->parent = minRight;

            tree->setRoot(minRight);
        }

        delete root;
        return true;
    }


    void print() {
        tree->print();
    }

    Node* getRoot() {
        return tree->getRoot();
    }

    void clear() {
        tree->clear();
    }
};