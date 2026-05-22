#pragma once
#include"tset.h"
#include<iostream>
#include<vector>

using namespace std;

template<class K, class V>
class HTable {
	struct Pair {
		K key;
		V val;
		Pair() :key(K()), val(V()) {};
		Pair(K k, V v) :key(k), val(v) {};
	};
	vector<Pair>data;
	TSet use;
	int size;
	int q1, q2, iter;
public:
	HTable(int sz = 100) :data(sz), use(sz), size(sz), q1(7), q2(3), iter(5) {};
	int hash_(int p) {
		return((p * q1 + q2) % size);
	}
	int find(K k) {
		hash<K> hasher;
		int p = hasher(k);
		if (p < 0)p *= -1;
		for (size_t i = 0; i < iter; ++i) {
			p = hash_(p);
			if (use.IsMember(p))if (data[p].key == k)return p;
		}
		return -1;
	}
	void insert(K k, V v) {
		int pos = find(k);
		if (pos != -1) {
			data[pos].val = v;
			return;
		}
		hash<K> hasher;
		int p = hasher(k);
		if (p < 0)p *= -1;
		for (size_t i = 0; i < iter; ++i) {
			p = hash_(p);
			if (!use.IsMember(p)) {
				data[p] = Pair(k, v);
				use.InsElem(p);
				return;
			}
		}
		resize();
		insert(k, v);
	}
	void resize() {
		HTable new_tab(size * 2);
		for (int i = 0; i < size; ++i)if (use.IsMember(i))new_tab.insert(data[i].key, data[i].val);
		data = new_tab.data;
		use=new_tab.use;
	}
	void del(K k) {
		int pos = find(k);
		if (pos != -1) {
			use.DelElem(pos);
			return;
		}
	}
	V get(K k) {
		int pos = find(k);
		if (pos != -1)return data[pos].val;
		throw - 1;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const HTable& other) {
		for (int i = 0; i < other.size; ++i)if (other.use.IsMember(i))ostr << other.data[i].key << " = " << other.data[i].val << ';' << endl;
		return ostr;
	}
};