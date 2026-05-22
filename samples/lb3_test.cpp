#include <iostream>
#include"fin_st_machine.h"
#include"lexem.h"
#include"queue.h"
#include"TArithmeticExpression.h"
#include"AVL.h"
#include"HashTable.h"

int main()
{
    //a=9-1;b=5+a*2;
    std::string a;
    std::cin >> a;


    AVLTable* tab1 = new AVLTable();
    TArithmeticExpression alg1(a, tab1);
    std::cout << '\n';
    alg1.CalculateIterationTree();
    alg1.printTable();
    std::cout << '\n';


    HashTable* tab2 = new HashTable();
    TArithmeticExpression alg2(a, tab2);
    std::cout << '\n';
    alg2.CalculateIterationTree();
    alg2.printTable();
    std::cout << '\n';

    /*std::cout << "Lex errors: ";
    alg.GetLexErr().print();
    std::cout << '\n';
    std::cout << "Synt errors: ";
    alg.GetSyntErr().print();
    std::cout << '\n';*/
    /*try {
        std::cout << "Res: " << alg.Calculate();
    }
    catch (...) {
        std::cout << "Result can't be gotten";
    }*/
}
