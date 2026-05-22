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
	/*queue<lexem> postfix;
	queue<int> lex_err;
	queue<int> synt_err;
	bool check;*/

	void construct_to_eq(stack<expr_and_lex>&child);
	void construct_to_lbr(stack<expr_and_lex>&child);
	void construct(stack<expr_and_lex>&child);

	queue<lexem> ToPostfix();
	void ToInfix(std::string a);
	void ToTree();
	void ToTree_inf();

public:
	TArithmeticExpression(std::string a, PairTable* tab): infix(queue<lexem>(a.size() * 2)), tree(nullptr), table(tab) {
		//lex_err = queue<int>(a.size() + 1);
		//synt_err = queue<int>(a.size() + 1);
		//postfix = queue<lexem>(a.size() * 2);
		ToInfix(a);
		//ToPostfix();
		ToTree_inf();
	}

	queue<lexem> GetInfix() const;
	//queue<lexem> GetPostfix() const;

	//queue<int> GetLexErr() const;
	//queue<int> GetSyntErr() const;

	//int Calculate();
	void CalculateTree();
	void CalculateIterationTree();
	void printTable();
};
