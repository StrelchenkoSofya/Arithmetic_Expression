#include "stack.h"

#include <gtest.h>

TEST(stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(stack<int> st(5));
}
TEST(stack, throws_when_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(stack<int> st(-5));
}
TEST(stack, can_get_size)
{
	stack<int> st(5);
	EXPECT_EQ(5, st.size());
}
TEST(stack, can_get_curr)
{
	stack<int> st(5);
	st.push(3);
	EXPECT_EQ(0, st.return_curr());
}
TEST(stack, can_create_copied_stack)
{
	stack<int> st(5);
	ASSERT_NO_THROW(stack<int> st1(st));
}
TEST(stack, copied_stack_is_equal_to_source_one)
{
	stack<int> st(5);
	st.push(3);
	stack<int> st1(st);
	EXPECT_EQ(st, st1);
}
TEST(stack, copied_stack_has_its_own_memory)
{
	stack<int> st(5);
	stack<int> st1(st);
	EXPECT_NE(st.get_mem(), st1.get_mem());
}
TEST(stack, can_push_and_pop_element)
{
	stack<int> st(5);
	st.push(3);
	EXPECT_EQ(3, st.pop());
}
TEST(stack, can_push_and_top_element)
{
	stack<int> st(5);
	st.push(3);
	EXPECT_EQ(3, st.top());
}
TEST(stack, throws_when_pop_element_from_empty_stack)
{
	stack<int> st(5);
	ASSERT_ANY_THROW(st.pop());
}
TEST(stack, throws_when_top_element_from_empty_stack)
{
	stack<int> st(5);
	ASSERT_ANY_THROW(st.top());
}
TEST(stack, change_curr_when_pop_element_from_empty_stack)
{
	stack<int> st(5);
	st.push(3);
	st.pop();
	EXPECT_EQ(-1, st.return_curr());
}
TEST(stack, not_change_curr_when_top_element_from_empty_stack)
{
	stack<int> st(5);
	st.push(3);
	st.top();
	EXPECT_EQ(0, st.return_curr());
}
TEST(stack, throws_when_push_element_to_full_stack)
{
	stack<int> st(1);
	st.push(3);
	ASSERT_ANY_THROW(st.push(3));
}
TEST(stack, can_assign_stack_to_itself)
{
	stack<int> st(5);
	ASSERT_NO_THROW(st = st);
}
TEST(stack, can_assign_stacks_of_equal_size)
{
	stack<int> st(5);
	stack<int> st1(3);
	ASSERT_NO_THROW(st = st1);
}
TEST(stack, assign_operator_change_stack_size)
{
	stack<int> st(5);
	stack<int> st1(3);
	st = st1;
	EXPECT_EQ(3, st.size());
}
TEST(stack, can_assign_stack_of_different_size)
{
	stack<int> st(5);
	stack<int> st1(3);
	ASSERT_NO_THROW(st = st1);
}
TEST(stack, can_identify_empty_stack)
{
	stack<int> st(5);
	EXPECT_EQ(true, st.isEmpty());
	st.push(3);
	EXPECT_EQ(false, st.isEmpty());
}