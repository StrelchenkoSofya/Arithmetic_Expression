#pragma once

#include"Pair.h"
#include <iostream>
#include<string>
#include<any>

using namespace std;

class Number;
class BiOperation;
class Var;

class Visitor {
public:
	virtual int visitNumber(Number* num) = 0;
	virtual int visitBiOperation(BiOperation* op) = 0;
	virtual any visitVar(Var* var, bool f) = 0;
};

class Expr {
public:
	virtual any accept(Visitor* v, bool f) = 0;
	virtual int ret() = 0;
};

class Number : public Expr {
	int val;
public:
	Number(int _val) : val(_val) {}
	int getVal() const;
	virtual any accept(Visitor* v, bool f) override;
	virtual int ret() { return 0; }
};

class Var : public Expr {
	string s;
	int v;
public:
	Var(string _s, int _v) : s(_s), v(_v) {}
	string getS() const;
	int getV() const;
	virtual any accept(Visitor* v, bool f) override;
	virtual int ret() { return 1; }
};

class BiOperation : public Expr {
	char op;
	Expr* left;
	Expr* right;
public:
	BiOperation(char _op, Expr* l, Expr* r) :
		op(_op), left(l), right(r) {}
	virtual any accept(Visitor* v, bool f) override;
	Expr* getLeft();
	Expr* getRight();
	char getOp() const;
	virtual int ret() { return 2; }
};

class PrintVisitor : public Visitor {
public:
	virtual int visitNumber(Number* num) override;
	virtual any visitVar(Var* var, bool f) override;
	virtual int visitBiOperation(BiOperation* op) override;
};

class CalcVisitor : public Visitor {
	PairTable* table;
public:
	CalcVisitor(PairTable* t) :table(t) {};
	virtual int visitNumber(Number* num) override;
	virtual any visitVar(Var* var, bool f) override;
	virtual int visitBiOperation(BiOperation* op) override;
};

class IterationVisitor : public Visitor {
	struct VisitPair {
		Expr* e;
		bool f;
		VisitPair() :e(nullptr), f(bool()) {};
		VisitPair(Expr* _e, bool _f) :e(_e), f(_f) {};
	};
	PairTable* table;
	stack<VisitPair> child;
	stack<any> val;
	bool last;
public:
	IterationVisitor(PairTable* t, size_t sz) :table(t), child(stack<VisitPair>(sz)), val(stack<any>(sz)), last(false) {};
	virtual int visitNumber(Number* num);
	virtual int visitBiOperation(BiOperation* op);
	virtual any visitVar(Var* var, bool f);
	void calculate(Expr* root) {
		root->accept(this, true);
		while (!child.isEmpty()) {
			VisitPair tmp = child.pop();
			last = tmp.f;
			tmp.e->accept(this, true);
		}
	}
};

Expr* number(int val);
Expr* add(Expr* l, Expr* r, char a);
Expr* variable(string s, int v);