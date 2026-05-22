#pragma once
#include"queue.h"
#include"lexem.h"
#include"stack.h"
#include<iostream>
#include<string>

using namespace std;

class big_fin_st_machine {
	enum sign {
		CHAR,
		NUM,
		EQ,
		SMC,
		N,
		ERR,
	};
	enum st {
		ST0,
		ST1,
		END,
		NOT_DEF,
		ST_ERR,
	};

	static void to_string(queue<lexem>& res, string& s, char c, bool& f);
	static void rec_var(queue<lexem>& res, string& s, char c, bool& f);
	static void rec_val(queue<lexem>& res, string& s, char c, bool& f);
	static void err(queue<lexem>& res, string& s, char c, bool& f);
	static void skip(queue<lexem>& res, string& s, char c, bool& f);

	st next[2][5];
	void(*call[2][6])(queue<lexem>&, string&, char, bool&);

	sign sign_decode(char c);
	st st_decode(char c);

public:
	big_fin_st_machine() {
		next[ST0][ST0] = ST0;
		next[ST0][ST1] = ST1;
		next[ST0][END] = END;
		next[ST0][NOT_DEF] = ST0;
		next[ST0][ST_ERR] = ST_ERR;
		next[ST1][ST0] = ST0;
		next[ST1][ST1] = ST1;
		next[ST1][END] = ST_ERR;
		next[ST1][NOT_DEF] = ST1;
		next[ST1][ST_ERR] = ST_ERR;

		call[ST0][CHAR] = to_string;
		call[ST0][NUM] = to_string;
		call[ST0][EQ] = rec_var;
		call[ST0][SMC] = err;
		call[ST0][N] = skip;
		call[ST0][ERR] = err;
		call[ST1][CHAR] = to_string;
		call[ST1][NUM] = to_string;
		call[ST1][EQ] = err;
		call[ST1][SMC] = rec_val;
		call[ST1][N] = err;
		call[ST1][ERR] = err;
	}

	void process(string a, queue<lexem>& res, int& ii);
};

class fin_st_machine_queue {
	enum sign {
		NUM,
		L_BR,
		R_BR,
		OP1,
		OP2,
		FIN,
		ELSE,
		CH,
		NP,
	};
	enum st {
		ST0,
		ST1,
		ST2,
		STF
	};

	static void record_int(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_op1(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_op2(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_lbr(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_rbr(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_else(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void to_int(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void skip(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void to_st(size_t& i, string c, int& n, string& s, queue<lexem>& res);
	static void record_var(size_t& i, string c, int& n, string& s, queue<lexem>& res);

	st next[3][4];
	void(*call[3][9])(size_t&, string, int&, string&, queue<lexem>&);

	sign sign_decode(char c);
	st st_decode(char c);

public:
	fin_st_machine_queue(){
		next[ST0][ST0] = ST0;
		next[ST0][ST1] = ST1;
		next[ST0][ST2] = ST2;
		next[ST0][STF] = STF;
		next[ST1][ST0] = ST0;
		next[ST1][ST1] = ST1;
		next[ST1][ST2] = ST2;
		next[ST1][STF] = STF;
		next[ST2][ST0] = ST0;
		next[ST2][ST1] = ST2;
		next[ST2][ST2] = ST2;
		next[ST2][STF] = STF;

		call[ST0][NUM] = to_int;
		call[ST0][L_BR] = record_lbr;
		call[ST0][R_BR] = record_rbr;
		call[ST0][OP1] = record_op1;
		call[ST0][OP2] = record_op2;
		call[ST0][FIN] = skip;
		call[ST0][ELSE] = record_else;
		call[ST0][CH] = to_st;
		call[ST0][NP] = record_else;
		call[ST1][NUM] = to_int;
		call[ST1][L_BR] = record_int;
		call[ST1][R_BR] = record_int;
		call[ST1][OP1] = record_int;
		call[ST1][OP2] = record_int;
		call[ST1][FIN] = record_int;
		call[ST1][ELSE] = record_int;
		call[ST1][CH] = record_int;
		call[ST1][NP] = record_int;
		call[ST2][NUM] = to_st;
		call[ST2][L_BR] = record_var;
		call[ST2][R_BR] = record_var;
		call[ST2][OP1] = record_var;
		call[ST2][OP2] = record_var;
		call[ST2][FIN] = record_var;
		call[ST2][ELSE] = record_var;
		call[ST2][CH] = to_st;
		call[ST2][NP] = to_st;
	}

	void process(string a, queue<lexem>& res);
};

class fin_st_machine_lex {

	enum sign {
		TRUE,
		FALSE
	};
	enum st {
		ST_T,
		ST_F
	};

	st next[2][2];
	void(*call[2][2])(int, queue<int>&);

	static void error(int i, queue<int>& err);
	static void skip(int i, queue<int>& err);

	sign sign_decode(lexem l);
	st st_decode(lexem l);

public:
	fin_st_machine_lex() {
		next[ST_T][ST_T] = ST_T;
		next[ST_T][ST_F] = ST_F;
		next[ST_F][ST_T] = ST_F;
		next[ST_F][ST_F] = ST_F;

		call[ST_T][TRUE] = skip;
		call[ST_T][FALSE] = error;
		call[ST_F][TRUE] = skip;
		call[ST_F][FALSE] = error;
	}

	bool process(queue<lexem> str, queue<int>& err);
};

class fin_st_machine_synt {

	enum sign {
		ZERO,
		NUM,
		L_BR,
		R_BR,
		SUM,
		DIF,
		OP2,
		ELSE,
		FIN,
	};
	enum st {
		ST0,
		ST_NUM,
		ST_L_BR,
		ST_R_BR,
		ST_OP1,
		ST_MUL,
		ST_DIV,
		ST_ELSE,
	};

	//st next[2][2];
	void(*call[7][9])(int&, queue<int>&, stack<char>&, lexem, queue<lexem>&, stack<int>&);

	static void error(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);
	static void skip(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);
	static void smul(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);
	static void dmul(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);
	static void lbr(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);
	static void rbr(int& i, queue<int>& err, stack<char>& br, lexem l, queue<lexem>& new_str, stack<int>& br_err);

	sign sign_decode(lexem l);
	st st_decode(lexem l, st ST);

public:
	fin_st_machine_synt() {

		call[ST0][ZERO] = skip;
		call[ST0][NUM] = skip;
		call[ST0][SUM] = smul;
		call[ST0][DIF] = dmul;
		call[ST0][OP2] = error;
		call[ST0][L_BR] = lbr;
		call[ST0][R_BR] = rbr;
		call[ST0][ELSE] = skip;
		call[ST0][FIN] = smul;
		call[ST_NUM][ZERO] = error;
		call[ST_NUM][NUM] = error;
		call[ST_NUM][SUM] = skip;
		call[ST_NUM][DIF] = skip;
		call[ST_NUM][OP2] = skip;
		call[ST_NUM][L_BR] = lbr;
		call[ST_NUM][R_BR] = rbr;
		call[ST_NUM][ELSE] = skip;
		call[ST_NUM][FIN] = smul;
		call[ST_OP1][ZERO] = skip;
		call[ST_OP1][NUM] = skip;
		call[ST_OP1][SUM] = error;
		call[ST_OP1][DIF] = error;
		call[ST_OP1][OP2] = error;
		call[ST_OP1][L_BR] = lbr;
		call[ST_OP1][R_BR] = rbr;
		call[ST_OP1][ELSE] = skip;
		call[ST_OP1][FIN] = error;
		call[ST_MUL][ZERO] = skip;
		call[ST_MUL][NUM] = skip;
		call[ST_MUL][SUM] = error;
		call[ST_MUL][DIF] = error;
		call[ST_MUL][OP2] = error;
		call[ST_MUL][L_BR] = lbr;
		call[ST_MUL][R_BR] = rbr;
		call[ST_MUL][ELSE] = skip;
		call[ST_MUL][FIN] = error;
		call[ST_DIV][ZERO] = error;
		call[ST_DIV][NUM] = skip;
		call[ST_DIV][SUM] = error;
		call[ST_DIV][DIF] = error;
		call[ST_DIV][OP2] = error;
		call[ST_DIV][L_BR] = lbr;
		call[ST_DIV][R_BR] = rbr;
		call[ST_DIV][ELSE] = skip;
		call[ST_DIV][FIN] = error;
		call[ST_L_BR][ZERO] = skip;
		call[ST_L_BR][NUM] = skip;
		call[ST_L_BR][SUM] = smul;
		call[ST_L_BR][DIF] = dmul;
		call[ST_L_BR][OP2] = error;
		call[ST_L_BR][L_BR] = lbr;
		call[ST_L_BR][R_BR] = rbr;
		call[ST_L_BR][ELSE] = skip;
		call[ST_L_BR][FIN] = smul;
		call[ST_R_BR][ZERO] = error;
		call[ST_R_BR][NUM] = error;
		call[ST_R_BR][SUM] = skip;
		call[ST_R_BR][DIF] = skip;
		call[ST_R_BR][OP2] = skip;
		call[ST_R_BR][L_BR] = lbr;
		call[ST_R_BR][R_BR] = rbr;
		call[ST_R_BR][ELSE] = skip;
		call[ST_R_BR][FIN] = smul;
	}

	bool process(queue<lexem> str, queue<lexem>& new_str, queue<int>& err);
};