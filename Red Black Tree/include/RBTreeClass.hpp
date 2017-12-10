#include <fstream>
enum Color { RED, BLACK };

struct node
{
	node *left;
	node *right;
	node *parent;

	int key;
	int data;
	int color;

	node(int k)
	{
		key = k;
		color = BLACK;
	}
	node(node *&nil, int k, int d)
	{
		color = BLACK;
		key = k;
		data = d;
		left = nil;
		right = nil;
		parent = nil;

	}
};

class RBTree
{
private:
	node *root;
	node *nil;
public:
	RBTree() {
		nil = new node(0);
		nil->left = nil;
		nil->right = nil;
		root = nil;
		root->parent = nil;
	}
	~RBTree()
	{
		nil = nullptr;
		delete nil;
	}
	void transplant(node*&x, node*&y);
	void leftrotate(node *p);
	void rightrotate(node *p);
	node* insert(node *&p);
	void insert(int k, int d);
	void insert_fixup(node *&p);
	void remove_fixup(node *&p);
	bool remove(int k);
	node* remove(node *&p);
	node*  findMin(node *&p);
	node*  findMax(node *&p);
	int findMin();
	int findMax();
	void  rbDelete(node*&z);
	node* successor(node *&x);
	node*  find(node* p, int k);
	int  find(int k);
	void inorder(std::ofstream &out);
	void  postorder(std::ofstream &out);
	void  preorder(std::ofstream &out);
	void levelTraversal(std::ofstream &out);
	void  inorder(node *p, std::ofstream &out);
	void  postorder(node *p, std::ofstream &out);
	void preorder(node *&p, std::ofstream &out);
	void levelTraversal(node *&p, std::ofstream &out);
};
