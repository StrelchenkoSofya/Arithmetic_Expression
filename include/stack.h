#pragma once
#include <iostream>

template<typename T>
class stack {
	int curr;
	int n;
	T* mem;
public:
	stack(int _n) {
		if (_n < 0)throw - 1;
		n = _n;
		curr = -1;
		mem = new T[n];
	}
	stack(const stack& t) {
		n = t.n;
		curr = t.curr;
		mem = new T[n];
		for (int i = 0; i <= curr; i++) {
			mem[i] = t.mem[i];
		}
	}
	~stack() {
		delete[]mem;
	}
	T* get_mem() { return mem; }
	int size() { return n; }
	stack& operator=(const stack& t) {
		if (this == &t)return *this;
		curr = t.curr;
		n = t.n;
		delete[]mem;
		mem = new T[n];
		for (int i = 0; i <= curr; i++) {
			mem[i] = t.mem[i];
		}
		return *this;
	}
	bool operator==(const stack& t) const {
		if (curr != t.curr)return false;
		if (n != t.n)return false;
		for (int i = 0; i <= curr; i++) {
			if (mem[i] != t.mem[i])return false;
		}
		return true;
	}
	bool operator!=(const stack& t) const {
		return !(*this == t);
	}
	void push(const T& el) {
		if (curr == n - 1) {
			throw - 1;
		}
		curr++;
		mem[curr] = el;
	}
	const T& pop() {
		if (curr < 0) {
			throw - 1;
		}
		return mem[curr--];
	}
	T& top() {
		if (curr < 0) {
			throw - 1;
		}
		return mem[curr];
	}
	bool isEmpty() {
		return curr == -1;
	}
	int return_curr() { return curr; }
};

void check(std::string a, stack<int>& err);
void search(int* arr, int n, int* ind);