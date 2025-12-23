#include"stack.h"

void check(std::string a, stack<int>& err) {
	stack<int> s(a.size());
	for (int i = 0; i < a.size(); i++) {
		try {
			if (a[i] == '(') {
				s.push(i);
				err.push(i);
			}
			else {
				s.pop();
				err.pop();
			}
		}
		catch (...) { err.push(i); }
	}
}

void search(int* arr, int n, int* ind) {
	stack<int> a(n);
	for (int i = 0; i < n; i++) {
		a.push(-1);
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				a.push(j);
			}
		}
		ind[i] = a.pop();
		while (!a.isEmpty())a.pop();
	}
}