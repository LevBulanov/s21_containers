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
  s21::list<double> list1;
  // EXPECT_EQ(list1.empty(), true);
  // EXPECT_EQ(list1.size(), 0);
  // list1.push_front(10);
  // list1.push_back(20);
  // list1.push_front(1);
  // list1.push_back(30);
  // EXPECT_EQ(list1.size(), 4);
  // EXPECT_EQ(list1.empty(), false);
  // list1.print();  // 1, 10, 20, 30
  // list1.pop_front();
  // list1.print();  // 10, 20, 30
  // list1.pop_back();
  // list1.print();  // 10, 20
  // list1.pop_front();
  // list1.pop_back();
  // EXPECT_EQ(list1.empty(), true);
  // EXPECT_EQ(list1.size(), 0);
}

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
