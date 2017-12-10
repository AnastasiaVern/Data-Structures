#include <iostream>
#include <queue>
#include <fstream>
#include "RBSTCLass.hpp"

	int RBST:: getsize(node* p) 
	{
		if (!p) return 0;
		return p->size;
	}
	void RBST::fixsize(node* p) // установление корректного размера дерева
	{
		p->size = getsize(p->left) + getsize(p->right) + 1; 
	}
	node* RBST::rotateRight(node*&p)  //правый поворот относительно р
	{
		node *q = p->left;
		if (!q) return p;

		p->left = q->right;
		q->right = p;
		q->size = p->size;
		fixsize(p);
		return q;
	}

	node* RBST::rotateLeft(node*& q) // левый поворот относительно q
	{
		node* p = q->right;
		if (!p) return q;

		q->right = p->left;
		p->left = q;
		p->size = q->size;
		fixsize(q);
		return p;
	}

	node* RBST::insertRoot(node*&p, int k, int data ) // вставка нового узла с ключом k в корень дерева p 
	{
		if (!p) return new node(k,data);
		if (k<p->key)
		{
			p->left = insertRoot(p->left, k, data);
			return rotateRight(p);
		}
		else
		{
			p->right = insertRoot(p->right, k, data);
			return rotateLeft(p);
		}
	}
	void RBST::insert(int k, int data) 
	{
		root = insert(root, k,data);
	}
	node* RBST::insert(node*&p, int k, int data) // рандомизированная вставка нового узла с ключом k и данными data в дерево p
	{
		if (!p) return new node(k,data);
		if (rand() % (p->size + 1) == 0)
			return insertRoot(p, k, data);
		if (p->key>k)
			p->left = insert(p->left, k, data);
		else
			p->right = insert(p->right, k, data);
		fixsize(p);
		return p;
	}

	void RBST::inorder(std::ofstream &out)
	{
		inorder(root,out);
		out << std::endl;
	}

	void RBST::inorder(node *q, std::ofstream &out) //симметричный обход
	{
		if (q != nullptr)
		{
			inorder(q->left, out);
			out << q->key << "-" << q->data << " ";
			inorder(q->right, out);
		}
	}
	void RBST::preorder(std::ofstream &out)
	{
		preorder(root, out);
		out << std::endl;
	}
	void RBST:: preorder(node *&q, std::ofstream &out) //прямой обход
	{
		if (q != nullptr)
		{
		    out<< q->key << "-" <<q->data<<" ";
			preorder(q->left,out);
			preorder(q->right,out);
		}
	}
	void RBST::postorder(std::ofstream &out)
	{
		postorder(root,out);
		out<<std::endl;
	}
	void RBST::postorder(node *q, std::ofstream &out) //обратный обход
	{
		if (q != nullptr)
		{
			postorder(q->left,out);
			postorder(q->right,out);
			out << q->key << "-" << q->data << " ";
		}
	}
	node* RBST::join(node *&p, node *&q) // объединение двух деревьев
	{
		if (!p) return q;
		if (!q) return p;
		int sum = p->size+q->size;
		if (sum == 0) { 
			delete root;
			root = nullptr;
			return	nullptr;
		};
		if (rand() % (p->size + q->size) < p->size)
		{
			p->right = join(p->right, q);
			fixsize(p);
			return p;
		}
		else
		{
			q->left = join(p, q->left);
			fixsize(q);
			return q;
		}
	}
	bool RBST::remove(int k)
	{
		if (remove(root, k)) return true;
		else return false;
	}
	node* RBST::remove(node*& p, int k) // удаление из дерева p первого найденного узла с ключом k 
	{
		if (!p) { return p; }
		if (p->key == k)
		{
			node* q = join(p->left, p->right);
			delete p;
			p = nullptr;
			return q;
		}
		else if (k<p->key)
			p->left = remove(p->left, k);
		else
			p->right = remove(p->right, k);
		return p;
	} 
	int  RBST::find(int k) //ищет значение по ключу
	{
		node *rez = find(root, k);
		if (rez) return rez->data;
		else return false;
	}
	node* RBST::find(node *&p, int k) // поиск значения  по ключу k в дереве p
	{
		if (!p) return 0; // в пустом дереве можно не искать
		if (k == p->key)
			return p;
		if (k < p->key)
			return find(p->left, k);
		else
			return find(p->right, k);
	}
	int RBST:: findMax() 
	{
		node* max = findMax(root);
		if (max != nullptr) return max->key;
		else return false;
	}
	node* RBST::findMax(node* q)
	{
		if (!q) return nullptr;
		while (q->right != nullptr)
		{
			q = q->right;
		}
		return q;
	}
	int RBST::findMin() 
	{
		node* min=findMin(root);
		if (min != nullptr) return min->key;
		else return false;
	}
	node* RBST:: findMin(node* q)
	{
		if (!q) return nullptr;
		while (q->left!= nullptr)
		{
			q = q->left;
		}
		return q;
	}
	void RBST::  levelTraversal(std::ofstream &out)
	{
		levelTraversal(root,out);
		out << std::endl;
	}
	void RBST::levelTraversal(node *&root, std::ofstream &out)// обход по уровням дерева слева-направо
	{
		if (root == nullptr)
		{
			out << "empty" ;
			return;
		}

		std::queue<node *> q;
		q.push(root);

		while (!q.empty())
		{
			node *p = q.front();

			out << p->key << "-" << p->data << " ";
			q.pop();

			if (p->left != nullptr)
				q.push(p->left);

			if (p->right != nullptr)
				q.push(p->right);
		}
	}
