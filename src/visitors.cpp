#include"visitors.h"

int Number::getVal() const { return val; }
any Number::accept(Visitor* v, bool f) {
	return v->visitNumber(this);
}

string Var::getS() const { return s; }
int Var::getV() const { return v; }
any Var::accept(Visitor* v, bool f) {
	return v->visitVar(this, f);
}

Expr* BiOperation::getLeft() { return left; }
Expr* BiOperation::getRight() { return right; }
char BiOperation::getOp() const { return op; }
any BiOperation::accept(Visitor* v, bool f) {
	return v->visitBiOperation(this);
}

int PrintVisitor::visitNumber(Number* num) {
	std::cout << num->getVal();
	return 0;
}
any PrintVisitor::visitVar(Var* var, bool f) {
	std::cout << var->getS();
	return 0;
}
int PrintVisitor::visitBiOperation(BiOperation* op) {
	std::cout << '(';
	op->getLeft()->accept(this, true);
	std::cout << op->getOp();
	op->getRight()->accept(this,true);
	std::cout << ')';
	return 0;
}

int CalcVisitor::visitNumber(Number* num) {
	return num->getVal();
}
any CalcVisitor::visitVar(Var* var, bool f) {
	if(f)return var->getS();
	if (table->search(var->getS()))return table->get(var->getS());
	return var->getV();
}
int CalcVisitor::visitBiOperation(BiOperation* op) {

	if (op->getOp() == '+')
		return any_cast<int>(op->getLeft()->accept(this, false)) + any_cast<int>(op->getRight()->accept(this, false));
	if (op->getOp() == '-')
		return any_cast<int>(op->getLeft()->accept(this, false)) - any_cast<int>(op->getRight()->accept(this, false));
	if (op->getOp() == '*')
		return any_cast<int>(op->getLeft()->accept(this, false)) * any_cast<int>(op->getRight()->accept(this, false));
	if (op->getOp() == '/')
		return any_cast<int>(op->getLeft()->accept(this, false)) / any_cast<int>(op->getRight()->accept(this, false));
	if (op->getOp() == '=') {
		string s = any_cast<string>(op->getLeft()->accept(this, true));
		int v = any_cast<int>(op->getRight()->accept(this, false));
		(*table).insert(s, v);
		return 0;
	}
	if (op->getOp() == ';') {
		op->getLeft()->accept(this, false);
		op->getRight()->accept(this, true);
		return 0;
	}
}

int IterationVisitor::visitNumber(Number* num) {
	if (last) {
		val.push(num->getVal());
	}
	else {
		child.push(VisitPair(num, true));
	}
	return 0;
}
any IterationVisitor::visitVar(Var* var, bool f) {
	if (last) {
		val.push(var->getS());
	}
	else {
		child.push(VisitPair(var, true));
	}
	return 0;
}
int IterationVisitor::visitBiOperation(BiOperation* op) {
	if (last) {
		if (op->getOp() == '+') {
			int left = 0;
			int right = 0;
			any rv = val.pop();
			any lv = val.pop();
			try {
				left = any_cast<int>(lv);
			}
			catch (...) { left = table->get(any_cast<string>(lv)); }
			try {
				right = any_cast<int>(rv);
			}
			catch (...) { right = table->get(any_cast<string>(rv)); }
			val.push(left + right);
			return 0;
		}
		if (op->getOp() == '-') {
			int left = 0;
			int right = 0;
			any rv = val.pop();
			any lv = val.pop();
			try {
				left = any_cast<int>(lv);
			}
			catch (...) { left = table->get(any_cast<string>(lv)); }
			try {
				right = any_cast<int>(rv);
			}
			catch (...) { right = table->get(any_cast<string>(rv)); }
			val.push(left - right);
			return 0;
		}
		if (op->getOp() == '*') {
			int left = 0;
			int right = 0;
			any rv = val.pop();
			any lv = val.pop();
			try {
				left = any_cast<int>(lv);
			}
			catch (...) { left = table->get(any_cast<string>(lv)); }
			try {
				right = any_cast<int>(rv);
			}
			catch (...) { right = table->get(any_cast<string>(rv)); }
			val.push(left * right);
			return 0;
		}
		if (op->getOp() == '/') {
			int left = 0;
			int right = 0;
			any rv = val.pop();
			any lv = val.pop();
			try {
				left = any_cast<int>(lv);
			}
			catch (...) { left = table->get(any_cast<string>(lv)); }
			try {
				right = any_cast<int>(rv);
			}
			catch (...) { right = table->get(any_cast<string>(rv)); }
			val.push(left / right);
			return 0;
		}
		if (op->getOp() == '=') {
			int v = any_cast<int>(val.pop());
			string s = any_cast<string>(val.pop());
			(*table).insert(s, v);
			return 0;
		}
	}
	else {
		child.push(VisitPair(op, true));
		if (op->getRight()->ret() == 2) child.push(VisitPair(op->getRight(), false));
		else child.push(VisitPair(op->getRight(), true));
		if (op->getLeft()->ret() == 2) child.push(VisitPair(op->getLeft(), false));
		else child.push(VisitPair(op->getLeft(), true));
		return 0;
	}
	return 0;
}

Expr* number(int val) {
	return new Number(val);
}
Expr* add(Expr* l, Expr* r, char a) {
	return new BiOperation(a, l, r);
}
Expr* variable(string s, int v) {
	return new Var(s, v);
}