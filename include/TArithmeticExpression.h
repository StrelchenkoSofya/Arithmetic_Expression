#pragma once
#include"stack.h"
#include"queue.h"
#include"lexem.h"
#include"fin_st_machine.h"
#include"visitors.h"
#include"Pair.h"

struct expr_and_lex {
	Expr* e;
	lexem l;
	expr_and_lex() :e(nullptr), l(lexem()) {};
	expr_and_lex(Expr* _e, lexem _l) :e(_e), l(_l) {};
};

class TArithmeticExpression
{
	queue<lexem> infix;
	Expr* tree;
	PairTable* table;

	void construct_to_eq(stack<expr_and_lex>&child);
	void construct_to_lbr(stack<expr_and_lex>&child);
	void construct(stack<expr_and_lex>&child);

	queue<lexem> ToPostfix();
	void ToInfix(std::string a);
	void ToTree();
	void ToTree_inf();

public:
	TArithmeticExpression(std::string a, PairTable* tab): infix(queue<lexem>(a.size() * 2)), tree(nullptr), table(tab) {
		ToInfix(a);
		ToTree_inf();
	}

	queue<lexem> GetInfix() const;

	void CalculateTree();
	void CalculateIterationTree();
	void printTable();
};
