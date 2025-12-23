#include "queue.h"

#include <gtest.h>

TEST(queue, can_create_queue_with_positive_size)
{
	ASSERT_NO_THROW(queue<int> q(5));
}
TEST(queue, throws_when_create_queue_with_negative_size)
{
	ASSERT_ANY_THROW(queue<int> q(-5));
}
TEST(queue, can_get_size)
{
	queue<int> q(5);
	EXPECT_EQ(5, q.get_size());
}
TEST(queue, can_get_next)
{
	queue<int> q(5);
	EXPECT_EQ(0, q.next(4));
}
TEST(queue, can_create_copied_queue)
{
	queue<int> q(5);
	ASSERT_NO_THROW(queue<int> q1(q));
}
TEST(queue, copied_queue_is_equal_to_source_one)
{
	queue<int> q(5);
	q.push(3);
	queue<int> q1(q);
	EXPECT_EQ(q, q1);
}
TEST(queue, copied_queue_has_its_own_memory)
{
	queue<int> q(5);
	queue<int> q1(q);
	EXPECT_NE(q.get_mem(), q1.get_mem());
}
TEST(queue, can_push_and_pop_element)
{
	queue<int> q(5);
	q.push(3);
	EXPECT_EQ(3, q.pop());
}
TEST(queue, throws_when_pop_element_from_empty_queue)
{
	queue<int> q(5);
	ASSERT_ANY_THROW(q.pop());
}
TEST(queue, throws_when_push_element_to_full_queue)
{
	queue<int> q(1);
	ASSERT_ANY_THROW(q.push(3));
}
TEST(queue, can_assign_queue_to_itself)
{
	queue<int> q(5);
	ASSERT_NO_THROW(q = q);
}
TEST(queue, can_assign_queue_of_equal_size)
{
	queue<int> q(5);
	queue<int> q1(5);
	ASSERT_NO_THROW(q = q1);
}
TEST(queue, assign_operator_change_queue_size)
{
	queue<int> q(5);
	queue<int> q1(3);
	q = q1;
	EXPECT_EQ(3, q.get_size());
}
TEST(queue, can_assign_queue_of_different_size)
{
	queue<int> q(5);
	queue<int> q1(3);
	ASSERT_NO_THROW(q = q1);
}
TEST(queue, can_identify_empty_queue)
{
	queue<int> q(5);
	EXPECT_EQ(true, q.isEmpty());
	q.push(3);
	EXPECT_EQ(false, q.isEmpty());
}
TEST(queue, can_identify_full_queue)
{
	queue<int> q(2);
	EXPECT_EQ(false, q.isFull());
	q.push(3);
	EXPECT_EQ(true, q.isFull());
}