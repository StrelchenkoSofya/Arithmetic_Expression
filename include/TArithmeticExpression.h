#pragma once
#include"stack.h"
#include"queue.h"
#include"lexem.h"
#include"fin_st_machine.h"

class TArithmeticExpression
{
	queue<lexem> infix;
	queue<lexem> postfix;
	queue<int> lex_err;
	queue<int> synt_err;
	bool check;

	void ToPostfix();
	void ToInfix(std::string a);

public:
	TArithmeticExpression(std::string a) {
		lex_err = queue<int>(a.size() + 1);
		synt_err = queue<int>(a.size() + 1);
		infix = queue<lexem>(a.size() * 2);
		postfix = queue<lexem>(a.size() * 2);
		ToInfix(a);
		ToPostfix();
	}

	queue<lexem> GetInfix() const;
	queue<lexem> GetPostfix() const;

	queue<int> GetLexErr() const;
	queue<int> GetSyntErr() const;

	int Calculate();
};
