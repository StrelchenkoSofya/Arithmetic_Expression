#pragma once
#include<iostream>

enum type {
	num,
	var,
	op1,
	op2,
	eq,
	r_br,
	l_br,
	smc,
	no_type
};
struct lexem {
	std::string val_st = " ";
	//char val_ch = ' ';
	int val_int = -1;
	type tp = no_type;
	lexem() {}
	lexem(std::string s, type t) {
		val_st = s;
		tp = t;
	}
	/*lexem(char c, type t) {
		val_ch = c;
		tp = t;
	}*/
	lexem(int n) {
		val_int = n;
		tp = num;
	}
	//char ret_ch() { return val_ch; }
	std::string ret_st() { return val_st; }
	int ret_int() { return val_int; }
	bool operator==(const lexem& t) const {
		if (val_st != t.val_st)return false;
		if (val_int != t.val_int)return false;
		if (tp != t.tp)return false;
		return true;
	}
	bool operator!=(const lexem& t) const {
		return !(*this == t);
	}
	friend std::ostream& operator<<(std::ostream& ostr, const lexem& other);
};