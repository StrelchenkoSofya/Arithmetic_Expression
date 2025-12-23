#pragma once
#include<iostream>

enum type {
	num,
	op1,
	op2,
	r_br,
	l_br,
	no_type
};
struct lexem {
	char val_ch = ' ';
	int val_int = -1;
	type tp = no_type;
	lexem() {}
	lexem(char c, type t) {
		val_ch = c;
		tp = t;
	}
	lexem(int n) {
		val_int = n;
		tp = num;
	}
	bool operator==(const lexem& t) const {
		if (val_ch != t.val_ch)return false;
		if (val_int != t.val_int)return false;
		if (tp != t.tp)return false;
		return true;
	}
	bool operator!=(const lexem& t) const {
		return !(*this == t);
	}
	friend std::ostream& operator<<(std::ostream& ostr, const lexem& other);
};