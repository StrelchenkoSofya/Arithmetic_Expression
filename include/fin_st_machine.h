#pragma once
#include"queue.h"
#include"lexem.h"
#include"stack.h"
#include<iostream>
#include<string>

using namespace std;

class fin_st_machine_queue {
	enum sign {
		NUM,
		L_BR,
		R_BR,
		OP1,
		OP2,
		FIN,
		ELSE,
	};
	enum st {
		ST0,
		ST1,
		STF
	};

	static void record_int(size_t& i, char c, int& n, queue<lexem>& res);
	static void record_op1(size_t& i, char c, int& n, queue<lexem>& res);
	static void record_op2(size_t& i, char c, int& n, queue<lexem>& res);
	static void record_lbr(size_t& i, char c, int& n, queue<lexem>& res);
	static void record_rbr(size_t& i, char c, int& n, queue<lexem>& res);
	static void record_else(size_t& i, char c, int& n, queue<lexem>& res);
	static void to_int(size_t& i, char c, int& n, queue<lexem>& res);
	static void skip(size_t& i, char c, int& n, queue<lexem>& res);

	st next[2][3];
	void(*call[2][7])(size_t&, char, int&, queue<lexem>&);

	sign sign_decode(char c);
	st st_decode(char c);

public:
	fin_st_machine_queue(){
		next[ST0][ST0] = ST0;
		next[ST0][ST1] = ST1;
		next[ST0][STF] = STF;
		next[ST1][ST0] = ST0;
		next[ST1][ST1] = ST1;
		next[ST1][STF] = STF;

		call[ST0][NUM] = to_int;
		call[ST0][L_BR] = record_lbr;
		call[ST0][R_BR] = record_rbr;
		call[ST0][OP1] = record_op1;
		call[ST0][OP2] = record_op2;
		call[ST0][FIN] = skip;
		call[ST0][ELSE] = record_else;
		call[ST1][NUM] = to_int;
		call[ST1][L_BR] = record_int;
		call[ST1][R_BR] = record_int;
		call[ST1][OP1] = record_int;
		call[ST1][OP2] = record_int;
		call[ST1][FIN] = record_int;
		call[ST1][ELSE] = record_int;
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

	bool process(queue<lexem> str, queue<int>& err, queue<lexem>& new_str);
};