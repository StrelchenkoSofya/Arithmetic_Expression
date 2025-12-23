#include "TArithmeticExpression.h"

#include <gtest.h>

TEST(TArithmeticExpression, can_create_infix)
{
	TArithmeticExpression alg("(9+2*2/2-1)*(1+3*2)");
	queue<lexem> q(38);
	q.push(lexem('(', l_br)); q.push(lexem(9)); q.push(lexem('+', op1)); q.push(lexem(2)); q.push(lexem('*', op2)); q.push(lexem(2));
	q.push(lexem('/', op2)); q.push(lexem(2)); q.push(lexem('-', op1)); q.push(lexem(1)); q.push(lexem(')', r_br)); q.push(lexem('*', op2));
	q.push(lexem('(', l_br)); q.push(lexem(1)); q.push(lexem('+', op1)); q.push(lexem(3)); q.push(lexem('*', op2)); q.push(lexem(2));
	q.push(lexem(')', r_br));
	EXPECT_EQ(q, alg.GetInfix());
	TArithmeticExpression alg1("-(-1)");
	queue<lexem> q1(10);
	q1.push(lexem(-1)); q1.push(lexem('*', op2)); q1.push(lexem('(', l_br)); q1.push(lexem(-1));
	q1.push(lexem('*', op2)); q1.push(lexem(1)); q1.push(lexem(')', r_br));
	EXPECT_EQ(q1, alg1.GetInfix());
}
TEST(TArithmeticExpression, can_create_postfix)
{
	TArithmeticExpression alg("(9+2*2/2-1)*(1+3*2)");
	queue<lexem> q(38);
	q.push(lexem(9)); q.push(lexem(2)); q.push(lexem(2)); q.push(lexem('*', op2)); q.push(lexem(2));
	q.push(lexem('/', op2)); q.push(lexem(1)); q.push(lexem('-', op1)); q.push(lexem('+', op1)); q.push(lexem(1));
	q.push(lexem(3)); q.push(lexem(2)); q.push(lexem('*', op2)); q.push(lexem('+', op1)); q.push(lexem('*', op2));
	EXPECT_EQ(q, alg.GetPostfix());
	TArithmeticExpression alg1("-(-1)");
	queue<lexem> q1(10);
	q1.push(lexem(-1)); q1.push(lexem(-1)); q1.push(lexem(1)); q1.push(lexem('*', op2)); q1.push(lexem('*', op2));
	EXPECT_EQ(q1, alg1.GetPostfix());
}
TEST(TArithmeticExpression, can_calculate)
{
	TArithmeticExpression alg("(9+2*2/2-1)*(1+3*2)");
	EXPECT_EQ(alg.Calculate(), 70);
	TArithmeticExpression alg1("-(-1)");
	EXPECT_EQ(alg1.Calculate(), 1);
}
TEST(TArithmeticExpression, cant_calculate_with_errors)
{
	TArithmeticExpression alg("(9+2*2/2-a)*(1+3*2)");
	ASSERT_ANY_THROW(alg.Calculate());
	TArithmeticExpression alg1("-((-1)");
	ASSERT_ANY_THROW(alg1.Calculate());
}