#include"lexem.h"
#include<iostream>

std::ostream& operator<<(std::ostream& ostr, const lexem& other) {
	if (other.tp == num) {
		ostr << other.val_int;
	}
	else {
		ostr << other.val_ch;
	}
	return ostr;
}