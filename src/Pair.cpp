#include"Pair.h"

bool Pair::operator==(const Pair& p) {
	return s == p.s;
}
bool Pair::operator!=(const Pair& p) {
	return s != p.s;
}
bool Pair::operator>=(const Pair& p) {
	return s >= p.s;
}
bool Pair::operator<=(const Pair& p) {
	return s <= p.s;
}
bool Pair::operator>(const Pair& p) {
	return s > p.s;
}
bool Pair::operator<(const Pair& p) {
	return s < p.s;
}
std::ostream& operator<<(std::ostream& ostr, const Pair& other) {
	ostr << other.s << " = " << other.v << ';' << endl;
	return ostr;
}
void AVLTable::insert(string s, int v) {
	tree.Insert(Pair(s, v));
}
void AVLTable::del(string s) {
	tree.del(Pair(s, 0));
}
void AVLTable::set(string s, int v) {
	Node<Pair>* node = tree.search(Pair(s, 0));
	if (!node) throw - 1;
	node->val.v = v;
}
int AVLTable::get(string s) {
	Node<Pair>* node = tree.search(Pair(s, 0));
	if (!node) throw - 1;
	return node->val.v;
}
bool AVLTable::search(string s) {
	Node<Pair>* node = tree.search(Pair(s, 0));
	if (!node) return false;
	return true;
}
void AVLTable::print() {
	cout << tree;
}

void HashTable::insert(string s, int v) {
	tree.insert(s, v);
}
void HashTable::del(string s) {
	tree.del(s);
}
void HashTable::set(string s, int v) {
	if (tree.find(s) == -1)throw - 1;
	tree.insert(s, v);
}
int HashTable::get(string s) {
	return tree.get(s);
}
bool HashTable::search(string s) {
	if (tree.find(s) == -1)return false;
	return true;
}
void HashTable::print() {
	cout << tree;
}