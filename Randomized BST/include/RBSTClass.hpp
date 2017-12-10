struct node
{
	node *left;
	node *right;

	int key;
	int data;
	int size;

	node(int k, int d)
	{
		key = k;
		data = d;
		left = 0;
		right = 0;
		size = 1;
	}
};
class RBST
{
private:
	node *root;
public:
	RBST() { root = nullptr; }
	~RBST() { root = nullptr; delete root; }
	int getsize(node *p);
	void fixsize(node* p);
	node *rotateRight(node*&p);
	node* rotateLeft(node*& q);
	node* insertRoot(node*&p, int k, int data);
	void insert(int k, int data);
	node* insert(node*&p, int k, int data);
	void inorder(std::ofstream &out);
	void inorder(node *q, std::ofstream &out);
	void preorder(std::ofstream &out);
	void preorder(node *&q, std::ofstream &out);
	void postorder(node *q, std::ofstream &out);
	void postorder(std::ofstream &out);
	node* join(node *&p, node *&q);
	bool remove(int k);
	node* remove(node*& p, int k);
	int find(int k);
	node* find(node *&p, int k);
	int findMax();
	node* findMax(node* q);
	int findMin();
	node *findMin(node *q);
	void  levelTraversal(std::ofstream &out);
	void  levelTraversal(node *&root, std::ofstream &out);
};
