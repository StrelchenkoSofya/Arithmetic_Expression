#include <iostream>
#include"fin_st_machine.h"
#include"lexem.h"
#include"queue.h"
#include"TArithmeticExpression.h"

int main()
{
    std::string a;
    std::cin >> a;
    TArithmeticExpression alg(a);
    std::cout << '\n';
    std::cout << alg.Calculate();
}
