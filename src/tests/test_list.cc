#include <string>

#include "../s21_list.h"
#include "gtest/gtest.h"

TEST(ListTest, FrontBack) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  EXPECT_EQ(list1.front(), 'a');
  EXPECT_EQ(list1.back(), 'd');
  s21::list<int> list2;
  EXPECT_EQ(list2.front(), 0);
  EXPECT_EQ(list2.back(), 0);
}

TEST(ListTest, Iterator) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  auto it = list1.begin();
  EXPECT_EQ(list1.begin(), it);
  EXPECT_EQ(list1.front(), *it);
  ++it;
  EXPECT_EQ(*it, 'b');
  ++it;
  EXPECT_EQ(*it, 'c');
  ++it;
  EXPECT_EQ(*it, list1.back());
  --it;
  EXPECT_EQ(*it, 'c');
  EXPECT_NE(*it, list1.back());
}

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
  s21::list<int>::iterator it = list1.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  list1.pop_back();
  EXPECT_EQ(list1.size(), 1);
  list1.push_back(30);
  it = list1.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 30);
  list1.clear();
  list1.pop_back();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.push_back(10);
  list1.push_back(20);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 2);
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
  auto it = list1.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  list1.pop_front();
  EXPECT_EQ(list1.size(), 1);
  list1.push_front(1);
  list1.clear();
  list1.pop_front();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.push_front(20);
  list1.push_front(10);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 2);
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
  EXPECT_EQ(list1.front(), 1);
  list1.pop_front();
  EXPECT_EQ(list1.front(), 10);
  EXPECT_EQ(list1.back(), 30);
  list1.pop_back();
  EXPECT_EQ(list1.back(), 20);
  list1.pop_front();
  list1.pop_back();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Insert) {
  s21::list<int> list1;
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  auto it = list1.begin();
  it = list1.insert(it, 10);
  EXPECT_EQ(list1.front(), 10);
  EXPECT_EQ(*it, 10);
  it = list1.insert(it, 1);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 10);
  it = list1.insert(it, 5);
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 10);
  it = list1.end();
  it = list1.insert(it, 20);
  EXPECT_EQ(list1.back(), 20);
}

TEST(ListTest, Copy) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  s21::list<char> list2 = list1;
  EXPECT_EQ(list2.size(), 4);
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list1.front(), 'a');
  EXPECT_EQ(list1.back(), 'd');
  list2.pop_back();
  list2.pop_front();
  EXPECT_EQ(list2.front(), 'b');
  EXPECT_EQ(list2.back(), 'c');
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list2.size(), 2);
  list2.push_front('A');
  list2.push_back('Z');
  EXPECT_EQ(list2.front(), 'A');
  EXPECT_EQ(list2.back(), 'Z');
  EXPECT_EQ(list2.size(), 4);
  EXPECT_EQ(list2.empty(), false);
  list1 = list2;
  list2.pop_front();
  EXPECT_EQ(list2.size(), 3);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.front(), 'A');
  EXPECT_EQ(list1.back(), 'Z');
  list2.clear();
  list1 = list2;
  EXPECT_EQ(list1.empty(), true);
}

TEST(ListTest, Move) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  s21::list<char> list2;
  list2 = std::move(list1);
  EXPECT_EQ(list2.size(), 4);
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list1.size(), 0);
  EXPECT_EQ(list1.empty(), true);
  s21::list<char> list3 = std::move(list2);
  EXPECT_EQ(list3.size(), 4);
  EXPECT_EQ(list3.empty(), false);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_EQ(list2.empty(), true);
  EXPECT_EQ(list3.front(), 'a');
  EXPECT_EQ(list3.back(), 'd');
  list3.pop_front();
  list3.pop_back();
  list1 = std::move(list3);
  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.front(), 'b');
  EXPECT_EQ(list1.back(), 'c');
}

TEST(ListTest, Swap) {
  s21::list<int> list1(5);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 5);
  s21::list<int> list2{1, 2, 3, 4};
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list2.size(), 4);
  list1.swap(list2);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
  EXPECT_EQ(list2.empty(), false);
  EXPECT_EQ(list2.size(), 5);
  EXPECT_EQ(list2.front(), 0);
  EXPECT_EQ(list2.back(), 0);
}

TEST(ListTest, Reverse) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 'a');
  EXPECT_EQ(list1.back(), 'd');
  list1.reverse();
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 'd');
  EXPECT_EQ(list1.back(), 'a');
  list1.push_front('e');
  list1.reverse();
  EXPECT_EQ(list1.front(), 'a');
  EXPECT_EQ(list1.back(), 'e');
  list1.clear();
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(list1.size(), 0);
  list1.reverse();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
