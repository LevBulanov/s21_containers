#include <string>

#include "../s21_stack.h"
#include "gtest/gtest.h"

TEST(StackTest, EmptyStack1) {
  s21::stack<int> stack1;
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack1.size(), 0);
  stack1.pop();
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack1.size(), 0);
  stack1.push(10);
  EXPECT_EQ(stack1.top(), 10);
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.size(), 1);
  stack1.pop();
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack1.size(), 0);
}

TEST(StackTest, EmptyStack2) {
  std::string str1 = "hello";
  std::string str2 = "world";
  std::string str3 = "!!!";
  s21::stack<std::string> stack1;
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack1.size(), 0);
  stack1.push(str1);
  EXPECT_EQ(stack1.top(), str1);
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.size(), 1);
  stack1.push(str2);
  stack1.push(str3);
  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack1.top(), str3);
  stack1.pop();
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack1.top(), str2);
}

TEST(StackTest, ListConstructor) {
  s21::stack<char> stack1{'a', 'b', 'c', 'd'};
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.top(), 'd');
  EXPECT_EQ(stack1.size(), 4);
  stack1.pop();
  stack1.push('x');
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.size(), 4);
  EXPECT_EQ(stack1.top(), 'x');
}

TEST(StackTest, CopyConstructor) {
  s21::stack<char> stack1{'a', 'b', 'c', 'd'};
  s21::stack<char> stack2 = stack1;
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 'd');
  EXPECT_EQ(stack2.size(), 4);
  stack2.pop();
  stack2.push('x');
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.size(), 4);
  EXPECT_EQ(stack2.top(), 'x');
}

TEST(StackTest, MoveConstructor) {
  s21::stack<char> stack1{'a', 'b', 'c', 'd'};
  s21::stack<char> stack2 = std::move(stack1);
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 'd');
  EXPECT_EQ(stack2.size(), 4);
  stack2.pop();
  stack2.push('x');
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.size(), 4);
  EXPECT_EQ(stack2.top(), 'x');
}

TEST(StackTest, SwapTest1) {
  s21::stack<int> stack1;
  s21::stack<int> stack2{1, 2, 3, 4};
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(stack1.size(), 0);
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 4);
  EXPECT_EQ(stack2.size(), 4);
  stack1.swap(stack2);
  EXPECT_EQ(stack2.empty(), true);
  EXPECT_EQ(stack2.size(), 0);
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.top(), 4);
  EXPECT_EQ(stack1.size(), 4);
  stack1.pop();
  stack2.push(5);
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.top(), 3);
  EXPECT_EQ(stack1.size(), 3);
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 5);
  EXPECT_EQ(stack2.size(), 1);
  stack2.swap(stack1);
  EXPECT_EQ(stack2.empty(), false);
  EXPECT_EQ(stack2.top(), 3);
  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack1.empty(), false);
  EXPECT_EQ(stack1.top(), 5);
  EXPECT_EQ(stack1.size(), 1);
}

TEST(StackTest, insertMany1) {
  s21::stack<char> stack1{'a', 'b'};
  EXPECT_EQ(stack1.size(), 2);
  stack1.insert_many_back();
  EXPECT_EQ(stack1.top(), 'b');
  EXPECT_EQ(stack1.size(), 2);
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'a');
}

TEST(StackTest, insertMany2) {
  s21::stack<char> stack1{'a', 'b'};
  EXPECT_EQ(stack1.size(), 2);
  stack1.insert_many_back('c');
  EXPECT_EQ(stack1.top(), 'c');
  EXPECT_EQ(stack1.size(), 3);
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'b');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'a');
}

TEST(StackTest, insertMany3) {
  s21::stack<char> stack1{'a', 'b'};
  EXPECT_EQ(stack1.size(), 2);
  stack1.insert_many_back('c', 'd');
  EXPECT_EQ(stack1.top(), 'd');
  EXPECT_EQ(stack1.size(), 4);
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'c');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'b');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'a');
}

TEST(StackTest, insertMany4) {
  s21::stack<char> stack1{'a', 'b'};
  EXPECT_EQ(stack1.size(), 2);
  stack1.insert_many_back('c', 'd', 'e', 'f', 'g');
  EXPECT_EQ(stack1.top(), 'g');
  EXPECT_EQ(stack1.size(), 7);
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'f');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'e');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'd');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'c');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'b');
  stack1.pop();
  EXPECT_EQ(stack1.top(), 'a');
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
