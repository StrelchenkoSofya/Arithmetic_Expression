#include"fin_st_machine.h"
#include"queue.h"
#include"lexem.h"
#include"stack.h"
#include<iostream>
#include<string>


void fin_st_machine_queue:: record_int(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem(n));
	n = 0;
}
void fin_st_machine_queue:: record_op1(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem(c, op1));
	i++;
}
void fin_st_machine_queue:: record_op2(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem(c, op2));
	i++;
}
void fin_st_machine_queue:: record_lbr(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem('(', l_br));
	i++;
}
void fin_st_machine_queue:: record_rbr(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem(')', r_br));
	i++;
}
void fin_st_machine_queue:: record_else(size_t& i, char c, int& n, queue<lexem>& res) {
	res.push(lexem());
	i++;
}
void fin_st_machine_queue:: to_int(size_t& i, char c, int& n, queue<lexem>& res) {
	n = n * 10 + (c - 48);
	i++;
}
void fin_st_machine_queue:: skip(size_t& i, char c, int& n, queue<lexem>& res) {
}
fin_st_machine_queue:: sign fin_st_machine_queue:: sign_decode(char c) {
	if ((c <= '9') && (c >= '0')) {
		return NUM;
	}
	switch (c) {
	case '+': return OP1;
	case'-':return OP1;
	case'*': return OP2;
	case'/':return OP2;
	case'(':return L_BR;
	case')':return R_BR;
	case'\n':return FIN;
	default:return ELSE;
	}
}
fin_st_machine_queue:: st fin_st_machine_queue:: st_decode(char c) {
	if ((c <= '9') && (c >= '0')) {
		return ST1;
	}
	if (c == '\n') {
		return STF;
	}
	return ST0;
}
void fin_st_machine_queue:: process(string a, queue<lexem>& res) {
	a += '\n';
	int n = 0;
	st ST = ST0;
	size_t i = 0;
	size_t s = a.size();
	while (ST != STF) {
		char c = a[i];
		call[ST][sign_decode(c)](i, c, n, res);
		ST = next[ST][st_decode(c)];
	}
}



void fin_st_machine_lex:: error(int i, queue<int>& err) {
	err.push(i);
}
void fin_st_machine_lex:: skip(int i, queue<int>& err) {
}
fin_st_machine_lex:: sign fin_st_machine_lex:: sign_decode(lexem l) {
	if (l.tp == no_type) {
		return FALSE;
	}
	return TRUE;
}
fin_st_machine_lex:: st fin_st_machine_lex:: st_decode(lexem l) {
	if (l.tp == no_type) {
		return ST_F;
	}
	return ST_T;
}
bool fin_st_machine_lex:: process(queue<lexem> str, queue<int>& err) {
	st ST = ST_T;
	int i = 0;
	while (!str.isEmpty()) {
		lexem l = str.pop();
		call[ST][sign_decode(l)](i, err);
		ST = next[ST][st_decode(l)];
		i++;
	}
	if (ST == ST_T) {
		return true;
	}
	return false;
}




void fin_st_machine_synt:: error(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	err.push(i);
	i++;
}
void fin_st_machine_synt:: skip(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	i++;
	new_str.push(l);
}
void fin_st_machine_synt:: smul(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	i++;
}
void fin_st_machine_synt:: dmul(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	i++;
	new_str.push(lexem(-1));
	new_str.push(lexem('*', op2));
}
void fin_st_machine_synt:: lbr(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	try {
		br.push(1);
		br_err.push(i);
	}
	catch (...) { br_err.push(i); }
	i++;
	new_str.push(l);
}
void fin_st_machine_synt:: rbr(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err) {
	try {
		br.pop();
		br_err.pop();
	}
	catch (...) { br_err.push(i); }
	i++;
	new_str.push(l);
}
fin_st_machine_synt:: sign fin_st_machine_synt:: sign_decode(lexem l) {
	switch (l.tp) {
	case num: {
		if (l.val_int == 0)return ZERO;
		return NUM;
	};
	case op1: {
		if (l.val_ch == '+')return SUM;
		return DIF;
	};
	case op2: return OP2;
	case l_br:return L_BR;
	case r_br:return R_BR;
	default:return ELSE;
	}
}
fin_st_machine_synt:: st fin_st_machine_synt:: st_decode(lexem l, st ST) {
	switch (l.tp) {
	case num: return ST_NUM;
	case op1: return ST_OP1;
	case op2: {
		if (l.val_ch == '*')return ST_MUL;
		return ST_DIV;
	}
	case l_br:return ST_L_BR;
	case r_br:return ST_R_BR;
	default:return ST;
	}
}
bool fin_st_machine_synt:: process(queue<lexem> str, queue<int>& err, queue<lexem>& new_str) {
	st ST = ST0;
	stack<char> br(str.get_size());
	stack<int> br_err(str.get_size());
	int i = 0;
	lexem l;
	while (!str.isEmpty()) {
		l = str.pop();
		call[ST][sign_decode(l)](i, err, br, l, new_str, br_err);
		ST = st_decode(l, ST);
	}
	call[ST][FIN](i, err, br, l, new_str, br_err);
	while (!br_err.isEmpty()) {
		err.push(br_err.pop());
	}
	if (err.isEmpty()) return true;
	return false;
}