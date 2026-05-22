#include"TArithmeticExpression.h"
#include"stack.h"
#include"queue.h"
#include"lexem.h"
#include"AVL.h"
#include<iostream>

void TArithmeticExpression::ToInfix(std::string a) {
	int i = 0;
	big_fin_st_machine m;
	try {
		m.process(a, infix, i);
	}
	catch (...) {
		std::cout << "Error";
		throw - 1;
	}

	/*queue<lexem> tmp(a.size() + 1);
	fin_st_machine_queue m1;
	m1.process(a, tmp);
	fin_st_machine_lex m2;
	bool lex = m2.process(tmp, lex_err);
	fin_st_machine_synt m3;
	bool synt = m3.process(tmp, infix, synt_err);
	check = lex && synt;*/
}

queue<lexem> TArithmeticExpression:: ToPostfix() {
	queue<lexem> postfix(infix.get_size() + 1);
	queue<lexem> t = infix;
	stack<lexem> st(infix.get_size());
	lexem stackItem;
	while (!t.isEmpty()) {
		lexem item = t.pop();
		switch (item.tp) {
		case l_br:
			st.push(item);
			break;
		case r_br:
			stackItem = st.pop();
			while (stackItem.tp != l_br) {
				postfix.push(stackItem);
				stackItem = st.pop();
			}
			break;
		case op1: {
			while (!st.isEmpty()) {
				stackItem = st.pop();
				if (stackItem.tp == op2)
					postfix.push(stackItem);
				else {
					st.push(stackItem);
					break;
				}
			}
			st.push(item);
			break;
		}
		case op2: {
			st.push(item);
			break;
		}
		case eq: {
			while (!st.isEmpty()) {
				stackItem = st.pop();
				if ((stackItem.tp == op2)|| (stackItem.tp == op1)|| (stackItem.tp == eq))
					postfix.push(stackItem);
				else {
					st.push(stackItem);
					break;
				}
			}
			st.push(item);
			break;
		}
		case smc: {
			while (!st.isEmpty()) {
				stackItem = st.pop();
				if ((stackItem.tp == op2) || (stackItem.tp == op1) || (stackItem.tp == eq))
					postfix.push(stackItem);
				else {
					st.push(stackItem);
					break;
				}
			}
			st.push(item);
			break;
		}
		default:;
			postfix.push(item);
		}
	}
	while (!st.isEmpty()) {
		postfix.push(st.pop());
	}
	return postfix;
}

void TArithmeticExpression::ToTree() {
	queue<lexem> t = ToPostfix();
	stack<Expr*> st(t.get_size());
	Expr* tmp = nullptr;
	while (!t.isEmpty()) {
		lexem item = t.pop();
		switch (item.tp) {
		case op1: {
			Expr* r = st.pop();
			Expr* l = st.pop();
			Expr* n = add(l, r, item.ret_st()[0]);
			st.push(n);
			break;
		}
		case op2: {
			Expr* r = st.pop();
			Expr* l = st.pop();
			Expr* n = add(l, r, item.ret_st()[0]);
			st.push(n);
			break;
		}
		case smc: {
			Expr* r = st.pop();
			Expr* l = st.pop();
			Expr* n = add(l, r, item.ret_st()[0]);
			st.push(n);
			break;
		}
		case eq: {
			Expr* r = st.pop();
			Expr* l = st.pop();
			Expr* n = add(l, r, item.ret_st()[0]);
			st.push(n);
			break;
		}
		case var: {
			Expr* n = variable(item.ret_st(), 0);
			st.push(n);
			break;
		}
		case num: {
			Expr* n = number(item.ret_int());
			st.push(n);
			break;
		}
		default:
			throw - 1;
		}
	}
	tree = st.pop();
}

void TArithmeticExpression::construct(stack<expr_and_lex>&child) {
	expr_and_lex right = child.pop();
	expr_and_lex item = child.pop();
	expr_and_lex left = child.pop();
	expr_and_lex n(add(left.e, right.e, item.l.ret_st()[0]), lexem(0));
	child.push(n);
	return;
}
void TArithmeticExpression::construct_to_lbr(stack<expr_and_lex>&child) {
	stack<expr_and_lex>tmp(child.size());
	while (child.top().l.tp != l_br) {
		expr_and_lex item = child.pop();
		switch (item.l.tp) {
		case op1: {
			tmp.push(item);
			break;
		}
		case op2: {
			child.push(item);
			child.push(tmp.pop());
			construct(child);
			break;
		}
		case num: {
			tmp.push(item);
			break;
		}
		case var: {
			tmp.push(item);
			break;
		}
		default:throw - 1;
		}
	}
	expr_and_lex t;
	if (!tmp.isEmpty())t = tmp.pop();
	while (!tmp.isEmpty()) {
		tmp.push(t);
		expr_and_lex left = tmp.pop();
		expr_and_lex item = tmp.pop();
		expr_and_lex right = tmp.pop();
		expr_and_lex n(add(left.e, right.e, item.l.ret_st()[0]), lexem(0));
		t = n;
	}
	child.pop();
	child.push(t);
	return;
}
void TArithmeticExpression::construct_to_eq(stack<expr_and_lex>&child) {
	stack<expr_and_lex>tmp(child.size());
	while (child.top().l.tp != eq) {
		expr_and_lex item = child.pop();
		switch (item.l.tp) {
		case op2: {
			child.push(item);
			child.push(tmp.pop());
			construct(child);
			break;
		}
		case op1: {
			tmp.push(item);
			break;
		}
		case num: {
			tmp.push(item);
			break;
		}
		case var: {
			tmp.push(item);
			break;
		}
		default:throw - 1;
		}
	}
	expr_and_lex t;
	if (!tmp.isEmpty())t = tmp.pop();
	while (!tmp.isEmpty()) {
		tmp.push(t);
		expr_and_lex left = tmp.pop();
		expr_and_lex item = tmp.pop();
		expr_and_lex right = tmp.pop();
		expr_and_lex n(add(left.e, right.e, item.l.ret_st()[0]), lexem(0));
		t = n;
	}
	child.push(t);
	return;
}

void TArithmeticExpression::ToTree_inf() {
	queue<lexem> inf = infix;
	stack<expr_and_lex>child(infix.get_size());
	while (!inf.isEmpty()) {
		lexem item = inf.pop();
		switch (item.tp) {
		case l_br: {
			child.push(expr_and_lex(nullptr, item));
			break;
		}
		case r_br: {
			construct_to_lbr(child);
			break;
		}
		case op1: {
			child.push(expr_and_lex(nullptr, item));
			break;
		}
		case op2: {
			child.push(expr_and_lex(nullptr, item));
			break;
		}
		case smc: {
			construct_to_eq(child);
			construct(child);
			child.push(expr_and_lex(nullptr, item));
			break;
		}
		case eq: {
			child.push(expr_and_lex(nullptr, item));
			break;
		}
		case var: {
			child.push(expr_and_lex(variable(item.ret_st(), 0), item));
			cout << child.top().l.ret_st() << ' ';
			break;
		}
		case num: {
			child.push(expr_and_lex(number(item.ret_int()), item));
			break;
		}
		default:
			throw - 1;
		}
	}
	construct_to_eq(child);
	construct(child);
	expr_and_lex t;
	if (!child.isEmpty())t = child.pop();
	while (!child.isEmpty()) {
		child.push(t);
		expr_and_lex right = child.pop();
		expr_and_lex item = child.pop();
		expr_and_lex left = child.pop();
		expr_and_lex n(add(left.e, right.e, item.l.ret_st()[0]), lexem(0));
		t = n;
	}
	tree = t.e;
}

queue<lexem> TArithmeticExpression:: GetInfix() const
{
	queue<lexem> a = infix;
	return a;
}
/*queue<lexem> TArithmeticExpression::GetPostfix() const
{
	if (!check)throw - 1;
	queue<lexem> a = postfix;
	return a;
}

queue<int> TArithmeticExpression::GetLexErr() const
{
	queue<int> a = lex_err;
	return a;
}
queue<int> TArithmeticExpression::GetSyntErr() const
{
	queue<int> a = synt_err;
	return a;
}
int TArithmeticExpression:: Calculate() {
	if (!check)throw -1;
	stack<int> st(postfix.get_size());
	int leftOperand, rightOperand;
	while (!postfix.isEmpty())
	{
		lexem l = postfix.pop();
		switch (l.val_st[0])
		{
		case '+':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand + rightOperand);
			break;
		case '-':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand - rightOperand);
			break;
		case '*':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand * rightOperand);
			break;
		case '/':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand / rightOperand);
			break;
		default:
			st.push(l.val_int);
		}
	}
	return st.pop();
}*/

void TArithmeticExpression::CalculateTree() {
	CalcVisitor v(&*table);
	tree->accept(&v, true);
}
void TArithmeticExpression::CalculateIterationTree() {
	IterationVisitor v(&*table, infix.get_size());
	v.calculate(tree);
}
void TArithmeticExpression::printTable() {
	table->print();
}