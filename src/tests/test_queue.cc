#include <gtest/gtest.h>

#include "../s21_queue.h"

TEST(QueueTest, DefaultConstructorEmpty) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3, 4};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, Push) {
  s21::queue<int> q;
  q.push(42);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 42);

  q.push(100);
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 100);
}

TEST(QueueTest, Pop) {
  s21::queue<int> q = {10, 20, 30};
  q.pop();
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), 20);

  q.pop();
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 30);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 5);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, InsertManyBack) {
  s21::queue<int> q;
  q.insert_many_back(7, 8, 9, 10);
  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.front(), 7);
  EXPECT_EQ(q.back(), 10);
}

TEST(QueueTest, InsertManyBack_zero_args) {
  s21::queue<int> q;
  q.insert_many_back();
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1 = {100, 200, 300};
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), q1.size());
  EXPECT_EQ(q2.front(), q1.front());
  EXPECT_EQ(q2.back(), q1.back());

  q1.pop();
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 100);
}

TEST(QueueTest, MoveConstructorAndAssignment) {
  s21::queue<int> q1 = {5, 6, 7};
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 5);
  EXPECT_EQ(q2.back(), 7);
  EXPECT_TRUE(q1.empty());

  s21::queue<int> q3;
  q3 = std::move(q2);
  EXPECT_EQ(q3.size(), 3);
  EXPECT_EQ(q3.front(), 5);
  EXPECT_EQ(q3.back(), 7);
  EXPECT_TRUE(q2.empty());
}
