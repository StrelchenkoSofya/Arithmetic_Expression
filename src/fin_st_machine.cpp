#include"fin_st_machine.h"
#include"queue.h"
#include"lexem.h"
#include"stack.h"
#include<iostream>
#include<string>

using namespace std;


void big_fin_st_machine::to_string(queue<lexem>& res, string& s, char c, bool& f) {
	s += c;
}
void big_fin_st_machine::rec_var(queue<lexem>& res, string& s, char c, bool& f) {
	if ((s[0] <= '9') && (s[0] >= '0'))throw - 1;
	if (f)res.push(lexem(";", smc));
	res.push(lexem(s, var));
	s = "";
	string cs; cs += c;
	res.push(lexem(cs, eq));
	f = true;

}
void big_fin_st_machine::rec_val(queue<lexem>& res, string& s, char c, bool& f) {
	queue<lexem> tmp(s.size() + 1);
	fin_st_machine_queue m1;
	m1.process(s, tmp);
	fin_st_machine_lex m2;
	queue<int>lex_err = queue<int>(s.size() + 1);
	queue<int>synt_err = queue<int>(s.size() + 1);
	bool lex = m2.process(tmp, lex_err);
	fin_st_machine_synt m3;
	queue<lexem> val_res = queue<lexem>(s.size() * 2);
	bool synt = m3.process(tmp, val_res, synt_err);
	if (!(lex && synt))throw - 1;
	while (!val_res.isEmpty())res.push(val_res.pop());
	s = "";
	//string cs; cs += c;
	//res.push(lexem(cs, smc));
}
void big_fin_st_machine::err(queue<lexem>& res, string& s, char c, bool& f) {
	throw - 1;
}
void big_fin_st_machine::skip(queue<lexem>& res, string& s, char c, bool& f) {
	return;
}

big_fin_st_machine::sign big_fin_st_machine::sign_decode(char c) {
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))return CHAR;
	if ((c <= '9') && (c >= '0'))return NUM;
	switch (c) {
	case '+':return NUM;
	case'-':return NUM;
	case'*':return NUM;
	case'/':return NUM;
	case'(':return NUM;
	case')':return NUM;
	case'=':return EQ;
	case';':return SMC;
	case'\n':return N;
	default:return ERR;
	}
}

big_fin_st_machine::st big_fin_st_machine::st_decode(char c) {
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))return NOT_DEF;
	if ((c <= '9') && (c >= '0'))return NOT_DEF;
	switch (c) {
	case '+':return NOT_DEF;
	case'-':return NOT_DEF;
	case'*':return NOT_DEF;
	case'/':return NOT_DEF;
	case'(':return NOT_DEF;
	case')':return NOT_DEF;
	case'_':return NOT_DEF;
	case'=':return ST1;
	case';':return ST0;
	case'\n':return END;
	default:return ST_ERR;
	}
}

void big_fin_st_machine::process(string a, queue<lexem>& res, int& ii) {
	a += '\n';
	st ST = ST0;
	size_t i = 0;
	string s;
	bool f = false;
	while (ST != END) {
		char c = a[i];
		call[ST][sign_decode(c)](res, s, c, f);
		ST = next[ST][st_decode(c)];
		i++;
		ii = i;
		if (ST == ST_ERR)throw - 1;
	}
}

void fin_st_machine_queue:: record_int(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem(n));
	n = 0;
}
void fin_st_machine_queue:: record_op1(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem(c, op1));
	i++;
}
void fin_st_machine_queue:: record_op2(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem(c, op2));
	i++;
}
void fin_st_machine_queue:: record_lbr(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem("(", l_br));
	i++;
}
void fin_st_machine_queue:: record_rbr(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem(")", r_br));
	i++;
}
void fin_st_machine_queue:: record_else(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem());
	i++;
}
void fin_st_machine_queue:: to_int(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	char ch = c[0];
	n = n * 10 + (ch - 48);
	i++;
}
void fin_st_machine_queue:: skip(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
}
void fin_st_machine_queue::to_st(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	s += c;
	i++;
}
void fin_st_machine_queue::record_var(size_t& i, string c, int& n, string& s, queue<lexem>& res) {
	res.push(lexem(s, var));
	s = "";
}
fin_st_machine_queue:: sign fin_st_machine_queue:: sign_decode(char c) {
	if ((c <= '9') && (c >= '0')) {
		return NUM;
	}
	if (((c <= 'Z') && (c >= 'A')) || (((c <= 'z') && (c >= 'a')))) {
		return CH;
	}
	switch (c) {
	case'_':return NP;
	case '+':return OP1;
	case'-':return OP1;
	case'*':return OP2;
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
	if (((c <= 'Z') && (c >= 'A')) || (((c <= 'z') && (c >= 'a'))) || (c == '_')) {
		return ST2;
	}
	if (c == '\n') {
		return STF;
	}
	return ST0;
}
void fin_st_machine_queue:: process(string a, queue<lexem>& res) {
	a += '\n';
	int n = 0;
	string s;
	st ST = ST0;
	size_t i = 0;
	while (ST != STF) {
		char c = a[i];
		string cs;
		cs += a[i];
		call[ST][sign_decode(c)](i, cs, n, s, res);
		ST = next[ST][st_decode(c)];
		cs = "";
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
	new_str.push(lexem("*", op2));
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
	case var: return NUM;
	case num: {
		if (l.val_int == 0)return ZERO;
		return NUM;
	};
	case op1: {
		if (l.val_st == "+")return SUM;
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
	case var:return ST_NUM;
	case num: return ST_NUM;
	case op1: return ST_OP1;
	case op2: {
		if (l.val_st == "*")return ST_MUL;
		return ST_DIV;
	}
	case l_br:return ST_L_BR;
	case r_br:return ST_R_BR;
	default:return ST;
	}
}
bool fin_st_machine_synt:: process(queue<lexem> str, queue<lexem>& new_str, queue<int>& err) {
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