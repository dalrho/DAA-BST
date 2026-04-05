#include "BinaryTree.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

class MyBinaryTree : public BinaryTree {

    private:
    Node* root;
    int size;
    
    void clearHelper(Node* root) {
        if (!root) return;
        clearHelper(root->left);
        clearHelper(root->right);
        delete root;
    }


    public:
    MyBinaryTree() {
        root = nullptr;
        size = 0;
    }

    void setRoot(Node* root) {
        this->root = root;
    }

    void setSize(int num) {
        this->size += num;
    }

    Node* left(Node* p) {
        if (!p){
            throw invalid_argument("The Node is  null");
            return nullptr;
        } 
        return p->left;
    }
	Node* right(Node* p) {
        if (!p){
            throw invalid_argument("The Node is  null");
            return nullptr;
        } 
        return p->right;
    }
	Node* addRoot(int e) {
        if (root != nullptr) {
            throw invalid_argument("Already has a root");
        }
        Node* n = (Node*)calloc(1, sizeof(Node));
        n->elem = e;
        root=n;
        size++;
        return root;
    }

	Node* addLeft(Node* p, int e) {
        if (p->left != nullptr) {
            throw invalid_argument("Node " + to_string(p->elem) + " already has a left child");
        }

        Node* n = (Node*)calloc(1, sizeof(Node));
        n->elem = e;
        n->parent = p;
        p->left=n;
        size++;
        return n;
    }

	Node* addRight(Node* p, int e) {
        if (p->right != nullptr) {
            throw invalid_argument("Node " + to_string(p->elem) + " already has a right child");
        }

        Node* n = (Node*)calloc(1, sizeof(Node));
        n->elem = e;
        n->parent = p;
        p->right=n;
        size++;
        return n;
    }

	int remove(Node* n) {
        if (!n) {
            throw invalid_argument("You can't remove a null node.");
        }

        if (n->left && n->right) {
            throw invalid_argument("You can't delete a node with two children");
        }

        // one child or no child
        
        Node* parent = n->parent;
        Node* child;

        if (n->left) {
            child = n->left;
        } else {
            child = n->right;
        }

        // only the root has no parent, all other nodes have one
        if (!parent) {
            root = child;
            if (child) child->parent = nullptr;
        } else {
            if (n == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }

            if (child) {
                child->parent = parent;
            }
        }

        delete(n);
        size--;
        
        return 1;

    }

	Node* getRoot() {
        return root;
    }


    void preorder(Node* root) {
        if (!root) return;
        cout << root->elem << " ";
        preorder(root->left);
        preorder(root->right);
    }

	void print() {
        cout << "Size: " << size << endl;
        if (!root) return;

        printHelper(root, "", true);
    }

    void printHelper(Node* node, string prefix, bool isRoot) {
        if (!node) return;

        if (isRoot) {
            cout << "+--R: " << node->elem << endl;
        }

        // LEFT CHILD
        if (node->left) {
            cout << prefix << "|   +--L: " << node->left->elem << endl;
            printHelper(node->left, prefix + "|   ", false);
        }

        // RIGHT CHILD
        if (node->right) {
            cout << prefix << "|   +--R: " << node->right->elem << endl;
            printHelper(node->right, prefix + "|   ", false);
        }
    }

	Node* sibling(Node* n) {
        Node* parent = n->parent;
        if (!parent) {
            throw logic_error("The root has no sibling");
        }
        return (parent->left == n) ? parent->right : parent->left;
    }

    int set(Node* root, int num) {
        if (!root) throw logic_error("Cannot set value of null node");
        int res = root->elem;
        root->elem = num;
        return res;
    }

    void attach(Node* root, BinaryTree* T1, BinaryTree* T2) {
        if (root->left || root->right) {
            throw logic_error(to_string(root->elem) + " already has a child");
        } else {
            Node* root1 = T1 ? T1->getRoot() : nullptr;
            Node* root2 = T2 ? T2->getRoot() : nullptr;

            if (root1) {
                root->left = root1;
                root1->parent = root;
            }

            if (root2) {
                root->left = root2;
                root2->parent = root;
            }
            
            if (T1) T1->remove(root1);
            if (T2) T2->remove(root2);
        }
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
    }

};