class node {
public:
    int keys[4];        // max 3 keys, 4 used temporarily during split
    node* children[5];  // max 4 children, 5 used temporarily
    node* parent;
    
    int num_keys;
    int num_child;

    node() {
        parent = nullptr;
        num_keys = 0;
        num_child = 0;
        for (int i = 0; i < 5; i++) children[i] = nullptr;
    }

    bool isLeaf() {
        return num_child == 0;
    }
};