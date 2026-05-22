#pragma once
#include<algorithm>
#include"stack.h"

template<typename T>
struct Node {
	Node* l, * r;
	T val;
	int h;
	Node() : l(nullptr), r(nullptr), val(T()), h(0) {};
	Node(T v) : l(nullptr), r(nullptr), val(v), h(0) {};
};

template<typename T>
class Iterator {
	stack<Node<T>*> st;
public:
	Iterator(Node<T>* _tmp, size_t sz) : st(stack<Node<T>*>(sz)) {
		pushLeft(_tmp);
	}
	void pushLeft(Node<T>* node) {
		while (node != nullptr) {
			st.push(node);
			node = node->l;
		}
	}
	bool hasNext() {
		return !st.isEmpty();
	}
	T Next() {
		if (!hasNext()) throw - 1;
		Node<T>* node = st.pop();
		T result = node->val;
		if (node->r != nullptr) {
			pushLeft(node->r);
		}
		return result;
	}
};

template<typename T>
class AVLTree {
	Node<T>* root;
	size_t size;
public:
	AVLTree() :root(nullptr), size(0) {};
	Node<T>* copy(Node<T>* oth) {
		if (!oth) return nullptr;
		Node<T>* res = new Node<T>(oth->val);
		res->h = oth->h;
		res->l = copy(oth->l);
		res->r = copy(oth->r);
		return res;
	}
	Node<T>* clear(Node<T>* oth) {
		if (!oth) return nullptr;
		clear(oth->l);
		clear(oth->r);
		delete oth;
		return nullptr;
	}
	AVLTree(const AVLTree& oth) {
		size = oth.size;
		if (this != &oth) {
			root = clear(root);
			root = copy(oth.root);
		}
	}
	AVLTree& operator=(const AVLTree& oth) {
		size = oth.size;
		if (this != &oth) {
			root = clear(root);
			root = copy(oth.root);
		}
		return *this;
	}
	~AVLTree() {
		root = clear(root);
	}
	int getHeight(Node<T>* left, Node<T>* right) {
		if (!left->h) {
			if (!right->h) {
				return 0;
			}
			return right->h + 1;
		}
		if (!right->h) {
			return left->h + 1;
		}
		return std::max(left->h, right->h) + 1;
	}
	int updateHeight(Node<T>* curr) {
		if (!curr)return 0;
		int lh = 0, rh = 0;
		if (curr->l)lh = curr->l->h;
		if (curr->r)rh = curr->r->h;
		curr->h = std::max(rh, lh) + 1;
		return curr->h;
	}
	int getDiff(Node<T>* left, Node<T>* right) {
		return updateHeight(left) - updateHeight(right);
	}
	Node<T>* rotateSmallLeft(Node<T>* a) {
		//int dif = getDiff(a->r, a->l);
		//if (dif < 2)return a;
		Node<T>* b = a->r;
		//if (getDiff(b->l, b->r) > 0)return a;
		//Node<T>* l = a->l;
		Node<T>* m = b->l;
		//Node<T>* r = b->r;
		b->l = a;
		a->r = m;
		updateHeight(a);
		updateHeight(b);
		return b;
	}
	Node<T>* rotateBigLeft(Node<T>* a) {
		//int dif = getDiff(a->r, a->l);
		//if (dif < 2)return a;
		Node<T>* b = a->r;
		//if (getDiff(b->l, b->r) <= 0)return a;
		//Node<T>* l = a->l;
		Node<T>* c = b->l;
		Node<T>* ml = c->l;
		Node<T>* mr = c->r;
		//Node<T>* r = b->r;
		c->l = a;
		c->r = b;
		a->l = ml;
		b->r = mr;
		updateHeight(a);
		updateHeight(b);
		updateHeight(c);
		return c;
	}
	Node<T>* rotateSmallRight(Node<T>* a) {
		//int dif = getDiff(a->l, a->r);
		//if (dif < 2)return a;
		Node<T>* b = a->l;
		//if (getDiff(b->r, b->l) > 0)return a;
		//Node<T>* r = a->r;
		Node<T>* m = b->r;
		//Node<T>* l = b->l;
		b->r = a;
		a->l = m;
		updateHeight(a);
		updateHeight(b);
		return b;
	}
	Node<T>* rotateBigRight(Node<T>* a) {
		//int dif = getDiff(a->l, a->r);
		//if (dif < 2)return a;
		Node<T>* b = a->l;
		//if (getDiff(b->r, b->l) <= 0)return a;
		//Node<T>* r = a->r;
		Node<T>* c = b->r;
		Node<T>* mr = c->r;
		Node<T>* ml = c->l;
		//Node<T>* l = b->l;
		c->r = a;
		c->l = b;
		a->r = mr;
		b->l = ml;
		updateHeight(a);
		updateHeight(b);
		updateHeight(c);
		return c;
	}
	Node<T>* balance(Node<T>* curr) {
		int dif = getDiff(curr->l, curr->r);
		if ((dif < 2) && (dif > -2))return curr;
		if (dif < 0) {
			Node<T>* tmp = curr->r;
			if (getDiff(tmp->l, tmp->r) > 0)curr = rotateBigLeft(curr);
			else curr = rotateSmallLeft(curr);
		}
		else {
			Node<T>* tmp = curr->l;
			if (getDiff(tmp->r, tmp->l) > 0)curr = rotateBigRight(curr);
			else curr = rotateSmallRight(curr);
		}
		return curr;
	}
	Node<T>* search(T value) {
		if (!root) return nullptr;
		Node<T>* curr = root;
		while (curr && curr->val != value) {
			if (value > curr->val) curr = curr->r;
			else curr = curr->l;
		}
		return curr;
	}
	void Insert(T value) {
		if (!root) {
			root = new Node<T>(value);
			root->h = 0;
			size++;
			return;
		}
		if (search(value))throw - 1;
		Node<T>* n = new Node<T>(value);
		stack<Node<T>*> p = stack<Node<T>*>(size*2);
		Node<T>* curr = root;
		int h = 1;
		p.push(curr);
		while (curr) {
			if (value > curr->val) {
				if (!curr->r) {
					n->h = h;
					curr->r = n;
					break;
				}
				h++;
				curr = curr->r;
			}
			else {
				if (!curr->l) {
					n->h = h;
					curr->l = n;
					break;
				}
				h++;
				curr = curr->l;
			}
			p.push(curr);
		}
		while (!p.isEmpty()) {
			Node<T>* tmp = p.pop();
			tmp = balance(tmp);
		}
		size++;
	}
	void del(T value) {
		if (!root)throw - 1;
		if (!search(value))throw - 1;
		stack<Node<T>*> p = stack<Node<T>*>(size*2);
		Node<T>* curr = root;
		while (curr->val != value) {
			p.push(curr);
			if (value > curr->val)curr = curr->r;
			else curr = curr->l;
		}
		Node<T>* curr1 = curr;
		bool f_h = false;
		while (curr1) {
			if (curr1->r) {
				if ((!curr1->r->r) && (!curr1->r->l)) {
					if (!curr1->l)f_h = true;
					curr->val = curr1->r->val;
					curr1->r = nullptr;
					break;
				}
				curr1 = curr1->r;
			}
			else if (curr1->l) {
				if ((!curr1->l->r) && (!curr1->l->l)) {
					if (!curr1->r)f_h = true;
					curr->val = curr1->l->val;
					curr1->l = nullptr;
					break;
				}
				curr1 = curr1->l;
			}
			p.push(curr1);
		}
		while (!p.isEmpty()) {
			Node<T>* tmp = p.pop();
			if (f_h)tmp->h -= 1;
			tmp = balance(tmp);
		}
		size--;
	}

	Iterator<T> itr() const {
		return Iterator<T>(root, size);
	}
	friend std::ostream& operator<<(std::ostream& ostr, const AVLTree& other) {
		Iterator<T> i = other.itr();
		while (i.hasNext())ostr << i.Next();
		return ostr;
	}
};