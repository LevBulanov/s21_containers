#include <string>

#include "../s21_list.h"
#include "gtest/gtest.h"

TEST(ListTest, PushBack) {
  s21::list<int> list1;
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.pop_back();
  list1.push_back(10);
  EXPECT_EQ(list1.size(), 1);
  list1.push_back(20);
  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.empty(), false);
  list1.print();  // 10, 20
  list1.pop_back();
  EXPECT_EQ(list1.size(), 1);
  list1.push_back(30);
  list1.print();  // 10, 30
  list1.clear();
  list1.pop_back();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.print();  // {}
  list1.push_back(10);
  list1.push_back(20);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 2);
  list1.print();  // 10, 20
  list1.clear();
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, PushFront) {
  s21::list<double> list1;
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.pop_front();
  list1.push_front(20);
  EXPECT_EQ(list1.size(), 1);
  list1.push_front(10);
  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.empty(), false);
  list1.print();  // 10, 20
  list1.pop_front();
  EXPECT_EQ(list1.size(), 1);
  list1.push_front(1);
  list1.print();  // 1, 20
  list1.clear();
  list1.pop_front();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.print();  // {}
  list1.push_front(20);
  list1.push_front(10);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 2);
  list1.print();  // 10, 20
  list1.clear();
}

TEST(ListTest, PushMix) {
  s21::list<double> list1;
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.push_front(10);
  list1.push_back(20);
  list1.push_front(1);
  list1.push_back(30);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.empty(), false);
  list1.print();  // 1, 10, 20, 30
  list1.pop_front();
  list1.print();  // 10, 20, 30
  list1.pop_back();
  list1.print();  // 10, 20
  list1.pop_front();
  list1.pop_back();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Swap) {
  s21::list<int> list1(5);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 5);
  list1.print();  // 0, 0, 0, 0, 0
  s21::list<int> list2{1, 2, 3, 4};
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list2.size(), 4);
  list2.print();  // 1, 2, 3, 4
  list1.swap(list2);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  list1.print();  // 1, 2, 3, 4
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list2.size(), 5);
  list2.print();  // 0, 0, 0, 0, 0
}

TEST(ListTest, Reverse) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  list1.print();  // a, b, c, d
  list1.reverse();
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  list1.print();  // d, c, b, a
  list1.push_front('e');
  list1.reverse();
  list1.print();  // a, b, c, d, e
  list1.clear();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.reverse();
}

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
