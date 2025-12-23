#include"TArithmeticExpression.h"
#include"stack.h"
#include"queue.h"
#include"lexem.h"

void TArithmeticExpression::ToInfix(std::string a) {
	queue<lexem> tmp(a.size() + 1);
	fin_st_machine_queue m1;
	m1.process(a, tmp);

	fin_st_machine_lex m2;
	bool lex = m2.process(tmp, lex_err);

	fin_st_machine_synt m3;
	bool synt = m3.process(tmp, synt_err, infix);

	check = lex && synt;
}

void TArithmeticExpression:: ToPostfix() {
	if (!check)return;
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
		default:;
			postfix.push(item);
		}
	}
	while (!st.isEmpty()) {
		stackItem = st.pop();
		postfix.push(stackItem);
	}
}

queue<lexem> TArithmeticExpression:: GetInfix() const
{
	queue<lexem> a = infix;
	return a;
}
queue<lexem> TArithmeticExpression:: GetPostfix() const
{
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
		switch (l.val_ch)
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
}