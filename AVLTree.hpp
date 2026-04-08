#include "MyBinaryTree.hpp"

using namespace std;

class AVLTree {

    public:

    BinaryTree* tree = new MyBinaryTree();


    bool insert_helper(Node* root, int num) {
        if (num == root->elem) return false;
        
        else if (num < root->elem) {
            if (root->left)
                return insert_helper(root->left, num);
            else {
                tree->addLeft(root, num);
                return true;
            }
        } else  {
            if (root->right)
                return insert_helper(root->right, num);
            else {
                tree->addRight(root, num);
                return true;
            }
        }
    }

    bool search_helper(Node* root, int num) {
            if (!root) {
                return false;
            }   
            if (root->elem == num) return true;
            if (num < root->elem) {
                return search_helper(root->left, num);
            } else {
                return search_helper(root->right, num);
            }
    }
    
    Node* findNode(Node* root, int num) {
        if (!root) return nullptr;
        if (root->elem == num) return root;
        else if (num < root->elem) return findNode(root->left, num);
        else return findNode(root->right, num);
    }

    Node* findMin(Node* root) {
        while (root->left) {
            root=root->left;
        }
        return root;
    }

    void transplant(Node* u, Node* v) {
        if (!u->parent) {
            tree->setRoot(v);
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        if (v) {
            v->parent = u->parent;
        }
    }

    bool remove_helper(Node* root, int num) {
        if (!root) return false;

        Node* target = findNode(root, num);
        if (!target) return false;

        if (!target->left) {
            transplant(target, target->right);
        }
        else if (!target->right) {
            transplant(target, target->left);
        }
        else {
            Node* succ = findMin(target->right);

            if (succ->parent != target) {
                transplant(succ, succ->right);

                succ->right = target->right;
                succ->right->parent = succ;
            }

            transplant(target, succ);

            succ->left = target->left;
            succ->left->parent = succ;
        }

        delete target;
        tree->setSize(-1);

        return true;
    }

    
    // NEW METHODS FOR AVL TREE
    
    int getHeight(Node* n) {
        return n? n->height: 0;
    }

    int getBalance(Node* n) {
        return n? getHeight(n->left) - getHeight(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (n)
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2) T2->parent = y;

        x->parent = y->parent;
        y->parent = x;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2) T2->parent = x;

        y->parent = x->parent;
        x->parent = y;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rebalance(Node* node) {
        updateHeight(node);
        int balance = getBalance(node);

        // LEFT HEAVY
        if (balance > 1) {
            if (getBalance(node->left) >= 0) {
                // Zig Right (LL)
                return rotateRight(node);
            } else {
                // Zig-Zag (LR)
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        // RIGHT HEAVY
        if (balance < -1) {
            if (getBalance(node->right) <= 0) {
                // Zig Left (RR)
                return rotateLeft(node);
            } else {
                // Zig-Zag (RL)
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }


    void rebalanceUpwards(Node* node) {
        Node* curr = node;

        while (curr) {
            updateHeight(curr);

            int balance = getBalance(curr);

            if (balance > 1 || balance < -1) {
                Node* parent = curr->parent;
                Node* newRoot = rebalance(curr);

                if (parent) {
                    if (parent->left == curr)
                        parent->left = newRoot;
                    else
                        parent->right = newRoot;

                    newRoot->parent = parent;
                } else {
                    tree->setRoot(newRoot);
                    newRoot->parent = nullptr;
                }

                curr = newRoot;
            }

            curr = curr->parent;
        }
    }

    Node* insertHelper(Node* root, int key) {
        if (!root) return nullptr;

        if (key < root->elem) {
            if (root->left) {
                return insertHelper(root->left, key);
            } else {
                return tree->addLeft(root, key);
            }
        } 
        else if (key > root->elem) {
            if (root->right) {
                return insertHelper(root->right, key);
            } else {
                return tree->addRight(root, key);
            }
        }

        return nullptr; // duplicate
    }

    bool insert(int key) {
        if (!tree->getRoot()) {
            tree->addRoot(key);
            return true;
        }

        Node* inserted = insertHelper(tree->getRoot(), key);
        if (!inserted) return false;

        rebalanceUpwards(inserted);
        return true;
    }

    Node* removeHelper(int key) {
        Node* target = findNode(tree->getRoot(), key);
        if (!target) return nullptr;

        Node* rebalanceStart = target->parent;

        if (target->left && target->right) {
            Node* succ = findMin(target->right);
            target->elem = succ->elem;
            rebalanceStart = succ->parent;
            tree->remove(succ);
        } else {
            tree->remove(target);
        }

        return rebalanceStart;
    }

    bool remove(int key) {
        Node* start = removeHelper(key);
        if (!start) return false;

        rebalanceUpwards(start);
        return true;
    }



    bool search(int num) {
        Node* root = tree->getRoot();
        if (!root) {
            throw invalid_argument("Empty Tree!");
        }
        return search_helper(root, num);
    }

    
};