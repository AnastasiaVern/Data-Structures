#include "RBTreeClass.hpp"
#include <iostream>
#include <queue>

void RBTree::leftrotate(node* p) //поворот дерева влево
{
    node* y = p->right;
    p->right = y->left;

    if (p->left != nil)
        y->left->parent = p;
    y->parent = p->parent;
    if (p->parent == nil)
        root = y;
    else if (p == p->parent->left)
        p->parent->left = y;
    else
        p->parent->right = y;

    y->left = p;
    p->parent = y;
}
void RBTree::rightrotate(node* p) //поворот дерева вправо
{
    node* y = p->left;
    p->left = y->right;
    if (p->right != nil)
        y->right->parent = p;
    y->parent = p->parent;
    if (p->parent == nil)
        root = y;
    else if (p == p->parent->left)
        p->parent->left = y;

    else
        p->parent->right = y;

    y->right = p;
    p->parent = y;
}

void RBTree::insert(int k, int d)
{
    node* p = new node(nil, k, d);
    insert(p);
}
node* RBTree::insert(node*& p)
{
    node* y = nil;
    node* x = root;
    while (x != nil) {
        y = x;
        if (p->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    p->parent = y;
    if (y == nil)
        root = p;
    else if (p->key < y->key)
        y->left = p;
    else
        y->right = p;
    p->color = RED;
    insert_fixup(p);
    return p;
}
void RBTree::insert_fixup(node*& p)
{
    while (p->parent->color == RED) {
        node* y;
        if (p->parent == p->parent->parent->left) {
            y = p->parent->parent->right;
            if (y->color == RED) {
                p->parent->color = BLACK;
                y->color = BLACK;
                p->parent->parent->color = RED;
                p = p->parent->parent;
            }
            else {
                if (p == p->parent->right) {
                    p = p->parent;
                    leftrotate(p);
                }

                p->parent->color = BLACK;
                p->parent->parent->color = RED;
                p->parent->right->color = BLACK;
                rightrotate(p->parent->parent);
            }
        }
        else {
            y = p->parent->parent->left;
            if (y->color == RED) {
                p->parent->color = BLACK;
                y->color = BLACK;
                p->parent->parent->color = RED;
                p = p->parent->parent;
            }
            else {
                if (p == p->parent->left) {
                    p = p->parent;
                    rightrotate(p);
                }
                p->parent->color = BLACK;
                p->parent->parent->color = RED;
                p->parent->left->color = BLACK;
                leftrotate(p->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
node* RBTree::successor(node*& x)
{
    if (x->right != nil) {
        return findMin(x->right);
    }
    node* y = x->parent;
    while (y != nil && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}
bool RBTree::remove(int k)
{
    node *p = find(root, k);
	if (p == root) 
	{
		rbDelete(p); return 0;
	}
	else if (p != nil)
	{
		rbDelete(p); 
		return 0; 
	}
	else return 1; 
}
void RBTree::rbDelete(node*& z)
{
    node* x = nil;
    node* y = nil;
    if (z->left == nil || z->right == nil)
        y = z;
    else
        y = successor(z);
    if (y->left != nil)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != z) {
        z->key = y->key;
        z->data = y->data;
    }
    if (y->color == BLACK)
        remove_fixup(x);
    delete y;
}
void RBTree::remove_fixup(node*& p)
{
    while (p != root && p->color == BLACK) {
        node* y;
        if (p == p->parent->left) {
            y = p->parent->right;
            if (y->color == RED) //случай 1
            {
                y->color = BLACK;
                p->parent->color = RED;
                leftrotate(p->parent);
                y = p->parent->right;
            }
            if (y->left->color == BLACK && y->right->color == BLACK) //случай 2
            {
                y->color = RED;
                p = p->parent;
            }
            else {
                if (y->right->color == BLACK) //случай 3
                {
                    y->left->color = BLACK;
                    y->color = RED;
                    rightrotate(y);
                    y = p->parent->right;
                }
                y->color = p->parent->color;
                p->parent->color = BLACK;
                y->right->color = BLACK;
                leftrotate(p->parent);
                p = root;
            }
        }
        else {
            y = p->parent->left;
            if (y->color == RED) {
                y->color = BLACK;
                p->parent->color = RED;
                rightrotate(p->parent);
                y = p->parent->left;
            }
            if ((y->right->color == BLACK) && (y->left->color == BLACK)) {
                y->color = RED;
                p = p->parent;
            }
            else {
                if (y->left->color == BLACK) {
                    y->right->color = BLACK;
                    y->color = RED;
                    leftrotate(y);
                    y = p->parent->left;
                }
                y->color = p->parent->color;
                p->parent->color = BLACK;
                y->left->color = BLACK;
                rightrotate(y->parent);
                p = root;
            }
        }
    }
    p->color = BLACK;
}

/*...........
                                      ...........
                                        FIND-ы
                                      ...........
                                      ...........
                                                    */
int RBTree::findMax()
{
    node* p = root;
    node* max = findMax(p);
    if (max != nil) {
        return max->key;
    }
    else
        return false;
};
node* RBTree::findMax(node*& p) //ищет максимальный элемент в дереве р
{
    node* y = nil;
    while (p != nil) {
        y = p;
        p = p->right;
    }
    return y;
}
int RBTree::findMin()
{
    node* p = root;
    node* min = findMin(p);
    if (min != nil) {
        return min->key;
    }
    else
        return false;
}
node* RBTree::findMin(node*& p) //ищет минимальный элемент в дереве р
{
    node* y = nil;
    while (p != nil) {
        y = p;
        p = p->left;
    }
    return y;
}
int RBTree::find(int k) //ищет значение по ключу
{
    node* rez = find(root, k);
    if (rez != nil)
        return rez->data;
    else
        return false;
}
node* RBTree::find(node* p, int k) // поиск значения по ключу k в дереве p
{
    if (p == nil)
        return nil;
    if (k == p->key)
        return p;
    if (k < p->key)
        return find(p->left, k);
    else
        return find(p->right, k);
}

/*...........
							          ...........
								        PRINT-ы
								      ...........
								      ...........
							                  	    */

void RBTree::preorder(std::ofstream& out)
{
    node* rt = root;
    preorder(rt, out);
    out << std::endl;
}
void RBTree::preorder(node*& q, std::ofstream& out)
{
    if (q != nil) {
        out << q->key << "-" << q->data << " ";
        preorder(q->left, out);
        preorder(q->right, out);
    }
};
void RBTree::inorder(std::ofstream& out)
{
    node* rt = root;
    inorder(rt, out);
    out << std::endl;
}
void RBTree::inorder(node* q, std::ofstream& out)
{
    if (q != nil) {
        inorder(q->left, out);
        out << q->key << " ";
        inorder(q->right, out);
    }
}
void RBTree::postorder(std::ofstream& out)
{
    node* rt = root;
    postorder(rt, out);
    out << std::endl;
}
void RBTree::postorder(node* q, std::ofstream& out)
{
    if (q != nil) {
        postorder(q->left, out);
        postorder(q->right, out);
        out << q->key << " ";
    }
}
void RBTree::levelTraversal(std::ofstream& out)
{
    node* rt = root;
    levelTraversal(rt, out);
    out << std::endl;
};
void RBTree::levelTraversal(node*& rt, std::ofstream& out) // обход по уровням дерева слева-направо
{
    if (rt == nil) {
        out << "empty";
        return;
    }

    std::queue<node*> q;
    q.push(rt);

    while (!q.empty()) {
        node* p = q.front();
        if (p != nil) {
            out << p->key << "-" << p->data << " ";
        };
        q.pop();

        if (p->left != nil) {
            q.push(p->left);
        }

        if (p->right != nil) {
            q.push(p->right);
        }
    }
}
