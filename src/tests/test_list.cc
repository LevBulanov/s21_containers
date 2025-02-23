#include <string>

#include "../s21_list.h"
#include "gtest/gtest.h"

TEST(ListTest, EmptyList1) {
  s21::list<int> list1;
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);

  // list1.pop();
  // EXPECT_EQ(list1.empty(), true);
  // EXPECT_EQ(list1.size(), 0);
  // list1.push(10);
  // EXPECT_EQ(list1.top(), 10);
  // EXPECT_EQ(list1.empty(), false);
  // EXPECT_EQ(list1.size(), 1);
  // list1.pop();
  // EXPECT_EQ(list1.empty(), true);
  // EXPECT_EQ(list1.size(), 0);
  list1.clear();
}

// TEST(StackTest, EmptyStack2) {
//   std::string str1 = "hello";
//   std::string str2 = "world";
//   std::string str3 = "!!!";
//   s21::list<std::string> list1;
//   EXPECT_EQ(list1.empty(), true);
//   EXPECT_EQ(list1.size(), 0);
//   list1.push(str1);
//   EXPECT_EQ(list1.top(), str1);
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.size(), 1);
//   list1.push(str2);
//   list1.push(str3);
//   EXPECT_EQ(list1.size(), 3);
//   EXPECT_EQ(list1.top(), str3);
//   list1.pop();
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.size(), 2);
//   EXPECT_EQ(list1.top(), str2);
// }

// TEST(StackTest, ListConstructor) {
//   s21::list<char> list1{'a', 'b', 'c', 'd'};
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.top(), 'd');
//   EXPECT_EQ(list1.size(), 4);
//   list1.pop();
//   list1.push('x');
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.size(), 4);
//   EXPECT_EQ(list1.top(), 'x');
// }

// TEST(StackTest, CopyConstructor) {
//   s21::list<char> list1{'a', 'b', 'c', 'd'};
//   s21::list<char> list2 = list1;
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.top(), 'd');
//   EXPECT_EQ(list2.size(), 4);
//   list2.pop();
//   list2.push('x');
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.size(), 4);
//   EXPECT_EQ(list2.top(), 'x');
// }

// TEST(StackTest, MoveConstructor) {
//   s21::list<char> list1{'a', 'b', 'c', 'd'};
//   s21::list<char> list2 = std::move(list1);
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.top(), 'd');
//   EXPECT_EQ(list2.size(), 4);
//   list2.pop();
//   list2.push('x');
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.size(), 4);
//   EXPECT_EQ(list2.top(), 'x');
// }

// TEST(StackTest, SwapTest1) {
//   s21::list<int> list1;
//   s21::list<int> list2{1, 2, 3, 4};
//   EXPECT_EQ(list1.empty(), true);
//   EXPECT_EQ(list1.size(), 0);
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.top(), 4);
//   EXPECT_EQ(list2.size(), 4);
//   list1.swap(list2);
//   EXPECT_EQ(list2.empty(), true);
//   EXPECT_EQ(list2.size(), 0);
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.top(), 4);
//   EXPECT_EQ(list1.size(), 4);
//   list1.pop();
//   list2.push(5);
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.top(), 3);
//   EXPECT_EQ(list1.size(), 3);
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.top(), 5);
//   EXPECT_EQ(list2.size(), 1);
//   list2.swap(list1);
//   EXPECT_EQ(list2.empty(), false);
//   EXPECT_EQ(list2.top(), 3);
//   EXPECT_EQ(list2.size(), 3);
//   EXPECT_EQ(list1.empty(), false);
//   EXPECT_EQ(list1.top(), 5);
//   EXPECT_EQ(list1.size(), 1);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
