#pragma once
#include <iostream>
#include<string>
#include"AVL.h"
#include"HashTable.h"

using namespace std;

struct Pair {
	string s;
	int v;
	Pair() :s(string()), v(int()) {};
	Pair(string _s, int _v) :s(_s), v(_v) {};
	bool operator==(const Pair& p);
	bool operator!=(const Pair& p);
	bool operator>=(const Pair& p);
	bool operator<=(const Pair& p);
	bool operator>(const Pair& p);
	bool operator<(const Pair& p);
	friend std::ostream& operator<<(std::ostream& ostr, const Pair& other);
};

class PairTable {
public:
	virtual void insert(string s, int v) = 0;
	virtual void del(string s) = 0;
	virtual void set(string s, int v) = 0;
	virtual int get(string s) = 0;
	virtual bool search(string s) = 0;
	virtual void print() = 0;
};

class AVLTable: public PairTable {
	AVLTree<Pair> tree;
public:
	AVLTable() :tree(AVLTree<Pair>()) {};
	void insert(string s, int v);
	void del(string s);
	void set(string s, int v);
	int get(string s);
	bool search(string s);
	void print();
};

class HashTable : public PairTable {
	HTable<string, int> tree;
public:
	HashTable() :tree(HTable<string, int>()) {};
	void insert(string s, int v);
	void del(string s);
	void set(string s, int v);
	int get(string s);
	bool search(string s);
	void print();
};