#include "MyGenTree.hpp"
#include <iostream>

using namespace std;

class Tree24 {
private:
    MyGenTree tree;

    // ================= SEARCH =================
    node* search(int k, node*& last) {
        node* curr = tree.getRoot();
        last = nullptr;

        while (curr) {
            last = curr;

            int i = 0;
            while (i < curr->num_keys && k > curr->keys[i]) i++;

            if (i < curr->num_keys && k == curr->keys[i])
                return curr;

            if (curr->isLeaf()) break;
            curr = curr->children[i];
        }
        return nullptr;
    }

    // ================= INSERT INTO NODE =================
    void insertIntoNode(node* n, int k, node* rightChild) {
        int i = n->num_keys - 1;

        while (i >= 0 && n->keys[i] > k) {
            n->keys[i + 1] = n->keys[i];
            n->children[i + 2] = n->children[i + 1];
            i--;
        }

        n->keys[i + 1] = k;
        n->children[i + 2] = rightChild;

        if (rightChild) rightChild->parent = n;

        n->num_keys++;
        if (rightChild) n->num_child++;
    }

    // ================= SPLIT =================
    void split(node* w) {
        node* left = new node();
        node* right = new node();

        // keys
        left->keys[0] = w->keys[0];
        left->keys[1] = w->keys[1];
        left->num_keys = 2;

        right->keys[0] = w->keys[3];
        right->num_keys = 1;

        // children
        if (!w->isLeaf()) {
            for (int i = 0; i < 3; i++) {
                left->children[i] = w->children[i];
                if (left->children[i]) left->children[i]->parent = left;
            }
            left->num_child = 3;

            for (int i = 3; i < 5; i++) {
                right->children[i - 3] = w->children[i];
                if (right->children[i - 3]) right->children[i - 3]->parent = right;
            }
            right->num_child = 2;
        }

        int mid = w->keys[2];

        if (w == tree.getRoot()) {
            node* newRoot = new node();
            newRoot->keys[0] = mid;
            newRoot->num_keys = 1;

            newRoot->children[0] = left;
            newRoot->children[1] = right;
            newRoot->num_child = 2;

            left->parent = newRoot;
            right->parent = newRoot;

            tree.setRoot(newRoot);
        } else {
            node* p = w->parent;

            int pos = 0;
            while (p->children[pos] != w) pos++;

            for (int i = p->num_keys; i > pos; i--) {
                p->keys[i] = p->keys[i - 1];
                p->children[i + 1] = p->children[i];
            }

            p->keys[pos] = mid;
            p->children[pos] = left;
            p->children[pos + 1] = right;

            left->parent = p;
            right->parent = p;

            p->num_keys++;
            p->num_child++;

            if (p->num_keys == 4)
                split(p);
        }

        delete w;
    }

    // ================= UNDERFLOW =================
    void fixUnderflow(node* w) {
        if (w == tree.getRoot()) return;
        if (w->num_keys >= 1) return;

        node* p = w->parent;

        int idx = 0;
        while (p->children[idx] != w) idx++;

        node* left = (idx > 0) ? p->children[idx - 1] : nullptr;
        node* right = (idx < p->num_child - 1) ? p->children[idx + 1] : nullptr;

        // transfer
        if (left && left->num_keys > 1) {
            w->keys[0] = p->keys[idx - 1];
            p->keys[idx - 1] = left->keys[left->num_keys - 1];
            left->num_keys--;
            w->num_keys = 1;
            return;
        }

        if (right && right->num_keys > 1) {
            w->keys[0] = p->keys[idx];
            p->keys[idx] = right->keys[0];

            for (int i = 0; i < right->num_keys - 1; i++)
                right->keys[i] = right->keys[i + 1];

            right->num_keys--;
            w->num_keys = 1;
            return;
        }

        // fusion (simplified)
        if (left) {
            left->keys[left->num_keys++] = p->keys[idx - 1];

            for (int i = idx - 1; i < p->num_keys - 1; i++) {
                p->keys[i] = p->keys[i + 1];
                p->children[i + 1] = p->children[i + 2];
            }

            p->num_keys--;
            p->num_child--;

            delete w;
            fixUnderflow(p);
        }
    }

public:
    void insert(int k) {
        if (!tree.getRoot()) {
            tree.addRoot(k);
            return;
        }

        node* last = nullptr;
        node* found = search(k, last);
        if (found) return;

        insertIntoNode(last, k, nullptr);

        if (last->num_keys == 4)
            split(last);
    }

    void remove(int k) {
        node* last = nullptr;
        node* n = search(k, last);
        if (!n) return;

        int idx = 0;
        while (n->keys[idx] != k) idx++;

        if (!n->isLeaf()) {
            node* pred = n->children[idx];
            while (!pred->isLeaf())
                pred = pred->children[pred->num_child - 1];

            n->keys[idx] = pred->keys[pred->num_keys - 1];
            n = pred;
            idx = n->num_keys - 1;
        }

        for (int i = idx; i < n->num_keys - 1; i++)
            n->keys[i] = n->keys[i + 1];

        n->num_keys--;

        fixUnderflow(n);
    }

    void print() {
        tree.print();
    }

    bool find(int k) {
        node* last = nullptr;
        return search(k, last) != nullptr;
    }
};