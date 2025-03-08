#include <list>
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
  s21::list<char>::iterator it = list1.begin();
  EXPECT_EQ(list1.begin(), it);
  EXPECT_EQ(list1.front(), *it);
  ++it;
  EXPECT_EQ(*it, 'b');
  *it = 'g';
  EXPECT_EQ(*it, 'g');
  ++it;
  EXPECT_EQ(*it, 'c');
  ++it;
  EXPECT_EQ(*it, list1.back());
  --it;
  EXPECT_EQ(*it, 'c');
  EXPECT_NE(*it, list1.back());
}

TEST(ListTest, ConstIterator) {
  s21::list<char> list1{'a', 'b', 'c', 'd'};
  s21::list<char>::const_iterator it = list1.begin();
  EXPECT_EQ(list1.begin(), it);
  EXPECT_EQ(list1.front(), *it);
  ++it;
  EXPECT_EQ(*it, 'b');
  // *it = 'g';
  // EXPECT_EQ(*it, 'g');
  ++it;
  EXPECT_EQ(*it, 'c');
  ++it;
  EXPECT_EQ(*it, list1.back());
  ++it;
  EXPECT_EQ(list1.end(), it);
  --it;
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

TEST(ListTest, Erase) {
  s21::list<char> list1{'a', 'b', 'c', 'd', 'e'};
  auto it = list1.begin();
  list1.erase(it);
  EXPECT_EQ(list1.front(), 'b');
  EXPECT_EQ(list1.size(), 4);
  it = list1.begin();
  ++it;
  list1.erase(it);
  EXPECT_EQ(list1.front(), 'b');
  it = list1.begin();
  ++it;
  EXPECT_EQ(*it, 'd');
  it = list1.end();
  list1.erase(it);
  EXPECT_EQ(list1.back(), 'e');
  EXPECT_EQ(list1.size(), 3);
  --it;
  list1.erase(it);
  EXPECT_EQ(list1.back(), 'd');
  EXPECT_EQ(list1.size(), 2);
  list1.clear();
  EXPECT_EQ(list1.size(), 0);
  it = list1.begin();
  list1.erase(it);
  it = list1.begin();
  EXPECT_EQ(list1.size(), 0);
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

TEST(ListTest, Unique) {
  s21::list<int> list1{1, 1, 2, 3, 1, 3, 3, 2, 2};
  list1.unique();
  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 2);
  ++it;
  EXPECT_EQ(it, list1.end());
}

TEST(ListTest, Splice1) {
  s21::list<int> list1{1, 2, 3, 4};
  s21::list<int> list2;
  list1.splice(list1.begin(), list2);
  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, list1.end());
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list2.size(), 0);
}

TEST(ListTest, Splice2) {
  s21::list<int> list1{1, 2, 3, 4};
  s21::list<int> list2;
  list2.splice(list2.begin(), list1);
  auto it = list2.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, list2.end());
  EXPECT_EQ(list2.size(), 4);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Splice3) {
  s21::list<int> list1{1, 2, 3, 4};
  s21::list<int> list2{0, 10, 20};
  list2.splice(++list2.begin(), list1);
  auto it = list2.begin();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(++it), 20);
  ++it;
  EXPECT_EQ(it, list2.end());
  EXPECT_EQ(list2.size(), 7);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Merge1) {
  s21::list<int> list1{1, 2, 3, 4};
  s21::list<int> list2;
  list1.merge(list2);
  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, list1.end());
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list2.size(), 0);
}

TEST(ListTest, Merge2) {
  s21::list<int> list1{1, 2, 3, 4};
  s21::list<int> list2;
  list2.merge(list1);
  auto it = list2.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, list2.end());
  EXPECT_EQ(list2.size(), 4);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Merge3) {
  s21::list<int> list1{1, 3, 4, 5};
  s21::list<int> list2{0, 2, 10, 20};
  list2.merge(list1);
  auto it = list2.begin();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(++it), 20);
  ++it;
  EXPECT_EQ(it, list2.end());
  EXPECT_EQ(list2.size(), 8);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Merge4) {
  s21::list<int> list1{0, 2, 10, 20};
  s21::list<int> list2{1, 3, 4, 5};
  list2.merge(list1);
  auto it = list2.begin();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(++it), 20);
  ++it;
  EXPECT_EQ(it, list2.end());
  EXPECT_EQ(list2.size(), 8);
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Sort1) {
  s21::list<int> list1;
  list1.sort();
  EXPECT_EQ(list1.size(), 0);
}

TEST(ListTest, Sort2) {
  s21::list<int> list1{1};
  list1.sort();
  EXPECT_EQ(list1.size(), 1);
  EXPECT_EQ(list1.front(), 1);
}

TEST(ListTest, Sort3) {
  s21::list<int> list1{5, 2, 1, 3, 4};
  list1.sort();
  EXPECT_EQ(list1.size(), 5);
  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 5);
}

TEST(ListTest, Sort4) {
  s21::list<char> list1{'z', 'y', 'x', 'c', 'b', 'a'};
  list1.sort();
  EXPECT_EQ(list1.size(), 6);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'x');
  EXPECT_EQ(*(++it), 'y');
  EXPECT_EQ(*(++it), 'z');
}

TEST(ListTest, MaxSize) {
  s21::list<double> list1{'z', 'y', 'x', 'c', 'b', 'a'};
  std::list<double> list_ref{'z', 'y', 'x', 'c', 'b', 'a'};
  EXPECT_EQ(list1.max_size(), list_ref.max_size());
}

TEST(ListTest, InsertMany1) {
  s21::list<char> list1{'a', 'b'};
  auto it = ++list1.begin();
  auto it2 = list1.insert_many(it);
  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(*it, 'b');
  EXPECT_EQ(*it2, 'b');
  it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertMany2) {
  s21::list<char> list1{'a', 'b'};
  auto it = ++list1.begin();
  auto it2 = list1.insert_many(it, 'c');
  EXPECT_EQ(list1.size(), 3);
  EXPECT_EQ(*it, 'b');
  EXPECT_EQ(*it2, 'c');
  it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertMany3) {
  s21::list<char> list1{'a', 'b'};
  auto it = ++list1.begin();
  auto it2 = list1.insert_many(it, 'c', 'd', 'e');
  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(*it, 'b');
  EXPECT_EQ(*it2, 'c');
  it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertMany4) {
  s21::list<char> list1{'a', 'b'};
  auto it = ++list1.begin();
  auto it2 = list1.insert_many(it, 'c', 'd', 'e', 'f', 'g');
  EXPECT_EQ(list1.size(), 7);
  EXPECT_EQ(*it, 'b');
  EXPECT_EQ(*it2, 'c');
  it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(++it), 'f');
  EXPECT_EQ(*(++it), 'g');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertManyBack1) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_back();
  EXPECT_EQ(list1.size(), 2);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertManyBack2) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_back('c');
  EXPECT_EQ(list1.size(), 3);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
}

TEST(ListTest, InsertManyBack3) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_back('c', 'd', 'e');
  EXPECT_EQ(list1.size(), 5);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
}

TEST(ListTest, InsertManyBack4) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_back('c', 'd', 'e', 'f', 'g');
  EXPECT_EQ(list1.size(), 7);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(++it), 'f');
  EXPECT_EQ(*(++it), 'g');
}

TEST(ListTest, InsertManyFront1) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_front();
  EXPECT_EQ(list1.size(), 2);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertManyFront2) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_front('c');
  EXPECT_EQ(list1.size(), 3);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'c');
  EXPECT_EQ(*(++it), 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertManyFront3) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_front('c', 'd', 'e');
  EXPECT_EQ(list1.size(), 5);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(++it), 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(ListTest, InsertManyFront4) {
  s21::list<char> list1{'a', 'b'};
  list1.insert_many_front('c', 'd', 'e', 'f', 'g');
  EXPECT_EQ(list1.size(), 7);
  auto it = list1.begin();
  EXPECT_EQ(*it, 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(++it), 'f');
  EXPECT_EQ(*(++it), 'g');
  EXPECT_EQ(*(++it), 'a');
  EXPECT_EQ(*(++it), 'b');
}
