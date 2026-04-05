class Node {
    public:
    int elem;
    Node* parent;
    Node* left;
    Node* right;
	int height;

	Node(int val) : elem(val), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

class BinaryTree {
    public:
    virtual Node* left(Node*) = 0;
	virtual Node* right(Node*) = 0;
	virtual Node* addRoot(int e) = 0;
	virtual Node* addLeft(Node* p, int e) = 0;
	virtual Node* addRight(Node* p, int e) = 0;
	virtual int remove(Node* n) = 0;
	virtual Node* getRoot() = 0;
	virtual void print() = 0;
	virtual int set(Node* root, int num) = 0;
	virtual void attach(Node* root, BinaryTree* T1, BinaryTree* T2) = 0;
	virtual void clear() = 0;
	virtual void setRoot(Node* root) = 0;
	virtual void setSize(int num) = 0;

	virtual Node* sibling(Node* n) = 0;
};