#include <string>
#include <vector>

#include "../s21_set.h"
#include "gtest/gtest.h"

TEST(SetTest, EmptySet) {
  s21::set<int> set1;
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set1.size(), 0);
  auto pair = set1.insert(1);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 1);
  EXPECT_EQ(*(pair.first), 1);
  EXPECT_EQ(pair.second, true);
  pair = set1.insert(1);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 1);
  EXPECT_EQ(*(pair.first), 1);
  EXPECT_EQ(pair.second, false);
  pair = set1.insert(2);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 2);
  EXPECT_EQ(*(pair.first), 2);
  EXPECT_EQ(pair.second, true);
  pair = set1.insert(0);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 3);
  EXPECT_EQ(*(pair.first), 0);
  EXPECT_EQ(pair.second, true);
  set1.clear();
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set1.size(), 0);
}

TEST(SetTest, Begin) {
  s21::set<int> set1;
  auto it = set1.begin();
  EXPECT_EQ(it, set1.end());
  set1.insert(1);
  set1.insert(2);
  it = set1.begin();
  EXPECT_EQ(*it, 1);
  set1.insert(3);
  set1.insert(0);
  it = set1.begin();
  EXPECT_EQ(*it, 0);
}

TEST(SetTest, End) {
  s21::set<int> set1;
  auto it = set1.end();
  EXPECT_EQ(it, set1.begin());
  set1.insert(5);
  set1.insert(3);
  it = set1.end();
  EXPECT_EQ(*(--it), 5);
  set1.insert(7);
  set1.insert(6);
  it = set1.end();
  EXPECT_EQ(*(--it), 7);
  set1.insert(10);
  it = set1.end();
  EXPECT_EQ(*(--it), 10);
}

TEST(SetTest, ListConstructor) {
  s21::set<int> set1{1, 2, 3, 4, 2, 3};
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 4);
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(++it, set1.end());
  it = set1.end();
  EXPECT_EQ(*(--it), 4);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*(--it), 1);
  EXPECT_EQ(--it, set1.end());
}

TEST(SetTest, IteratorEmptySet) {
  s21::set<int> set1;
  auto it = set1.begin();
  auto it2 = set1.end();
  EXPECT_EQ(it, it2);
  EXPECT_EQ(++it, it2);
  EXPECT_EQ(--it, it2);
  set1.insert(10);
  EXPECT_EQ(*(--it2), 10);
}

TEST(SetTest, Iterator1) {
  s21::set<int> set1{4, 3, 2, 1};
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(++it, set1.end());
  EXPECT_EQ(*(--it), 4);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*(--it), 1);
  EXPECT_EQ(--it, set1.end());
}

TEST(SetTest, Iterator2) {
  s21::set<std::string> set1{"Nina", "Anna", "Peter", "Alex", "Inna", "Masha"};
  auto it = set1.begin();
  EXPECT_EQ(*it, "Alex");
  EXPECT_EQ(*(++it), "Anna");
  EXPECT_EQ(*(++it), "Inna");
  EXPECT_EQ(*(++it), "Masha");
  EXPECT_EQ(*(++it), "Nina");
  EXPECT_EQ(*(++it), "Peter");
  EXPECT_EQ(++it, set1.end());
  EXPECT_EQ(*(--it), "Peter");
  EXPECT_EQ(*(--it), "Nina");
  EXPECT_EQ(*(--it), "Masha");
  EXPECT_EQ(*(--it), "Inna");
  EXPECT_EQ(*(--it), "Anna");
  EXPECT_EQ(*(--it), "Alex");
  EXPECT_EQ(--it, set1.end());
}

TEST(SetTest, MoveAssigmnent) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  s21::set<char> set2;
  set1 = std::move(set2);
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set2.size(), 0);
  EXPECT_EQ(set2.empty(), true);
  s21::set<char> set3{'b', 'c', 'a', 'd'};
  set1 = std::move(set3);
  EXPECT_EQ(set1.size(), 4);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set3.size(), 0);
  EXPECT_EQ(set3.empty(), true);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(++it, set1.end());
}

TEST(SetTest, MoveConstructor) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  s21::set<char> set2 = std::move(set1);
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set2.size(), 4);
  EXPECT_EQ(set2.empty(), false);
  auto it = set2.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
}

TEST(SetTest, CopyAssigmnent) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  s21::set<char> set2;
  set1 = set2;
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set2.size(), 0);
  EXPECT_EQ(set2.empty(), true);
  s21::set<char> set3{'b', 'c', 'a', 'd'};
  set1 = set3;
  EXPECT_EQ(set1.size(), 4);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set3.size(), 4);
  EXPECT_EQ(set3.empty(), false);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  it = set3.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
}

TEST(SetTest, CopyConstructor) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  s21::set<char> set2 = set1;
  EXPECT_EQ(set1.size(), 4);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set2.size(), 4);
  EXPECT_EQ(set2.empty(), false);
  auto it = set2.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
}

TEST(SetTest, MaxSize) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  EXPECT_GT(set1.max_size(), 0);
}

TEST(SetTest, Find1) {
  s21::set<char> set1{'a', 'b', 'c', 'd'};
  EXPECT_EQ(set1.contains('c'), true);
  auto it = set1.find('c');
  EXPECT_EQ(set1.size(), 4);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(*it, 'c');
  EXPECT_EQ(set1.contains('A'), false);
  EXPECT_EQ(set1.find('A'), set1.end());
  EXPECT_EQ(set1.contains('a'), true);
  it = set1.find('a');
  EXPECT_EQ(*it, 'a');
  s21::set<char> set2;
  EXPECT_EQ(set2.contains('a'), false);
  it = set2.find('a');
  EXPECT_EQ(it, set2.end());
}

TEST(SetTest, Find2) {
  s21::set<std::string> set1{"Nina", "Anna", "Peter", "Alex", "Inna", "Masha"};
  EXPECT_EQ(set1.contains("Peter"), true);
  auto it = set1.find("Peter");
  EXPECT_EQ(*it, "Peter");
  EXPECT_EQ(set1.contains("Alex"), true);
  it = set1.find("Alex");
  EXPECT_EQ(*it, "Alex");
  EXPECT_EQ(set1.contains("Nina"), true);
  it = set1.find("Nina");
  EXPECT_EQ(*it, "Nina");
  EXPECT_EQ(set1.contains("Polina"), false);
  it = set1.find("Polina");
  EXPECT_EQ(it, set1.end());
}

TEST(SetTest, Merge1) {
  s21::set<int> set1{1, 2, 3, 4};
  s21::set<int> set2;
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 4);
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, set1.end());
  EXPECT_EQ(set2.size(), 0);
}

TEST(SetTest, Merge2) {
  s21::set<int> set1{1, 2, 3, 4};
  s21::set<int> set2;
  set2.merge(set1);
  EXPECT_EQ(set2.size(), 4);
  EXPECT_EQ(set2.empty(), false);
  auto it = set2.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  ++it;
  EXPECT_EQ(it, set2.end());
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
}

TEST(SetTest, Merge3) {
  s21::set<int> set1{3, 1, 4, 5};
  s21::set<int> set2{0, 2, 4, 10, 20, 5};
  set2.merge(set1);
  EXPECT_EQ(set2.size(), 8);
  EXPECT_EQ(set2.empty(), false);
  auto it = set2.begin();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(++it), 20);
  ++it;
  EXPECT_EQ(it, set2.end());
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
}

TEST(SetTest, Merge4) {
  s21::set<int> set1{3, 1, 4, 5};
  s21::set<int> set2{0, 2, 4, 10, 20, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 8);
  EXPECT_EQ(set1.empty(), false);
  auto it = set1.begin();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(++it), 20);
  ++it;
  EXPECT_EQ(it, set1.end());
  EXPECT_EQ(set2.size(), 0);
  EXPECT_EQ(set2.empty(), true);
}

TEST(SetTest, Erase1) {
  s21::set<int> set1{3, 1, 4, 5};
  set1.erase(++set1.begin());
  EXPECT_EQ(*(++set1.begin()), 4);
  set1.erase(set1.begin());
  EXPECT_EQ(*set1.begin(), 4);
  set1.erase(--set1.end());
  EXPECT_EQ(*(--set1.end()), 4);
  set1.erase(set1.begin());
  EXPECT_EQ(set1.end(), set1.begin());
  EXPECT_EQ(set1.size(), 0);
  EXPECT_EQ(set1.empty(), true);
}

TEST(SetTest, Erase2) {
  s21::set<int> set1{10, 4, 5, 1, 3, 8, 7, 9, 20, 30};
  auto it = set1.begin();
  ++it;
  ++it;
  set1.erase(it);  // 4
  EXPECT_EQ(*(++set1.begin()), 3);
  set1.erase(set1.begin());  // 1
  EXPECT_EQ(*set1.begin(), 3);
  it = set1.begin();
  ++it;
  set1.erase(it);  // 5
  EXPECT_EQ(*(++set1.begin()), 7);
  set1.erase(set1.end());  // do nothing
  it = set1.end();
  --it;
  --it;
  set1.erase(it);  // 20
  it = set1.end();
  --it;
  --it;
  EXPECT_EQ(*it, 10);
  it = set1.end();
  --it;
  --it;
  set1.erase(it);  // 10, "top of tree"
  it = set1.end();
  --it;
  --it;
  EXPECT_EQ(*it, 9);
  EXPECT_EQ(set1.size(), 5);
  EXPECT_EQ(set1.empty(), false);
}

TEST(SetTest, InsertManyEmpty) {
  s21::set<char> set1{'a', 'b'};
  auto v1 = set1.insert_many();
  EXPECT_EQ(set1.size(), 2);
  EXPECT_EQ(v1.size(), 0);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
}

TEST(SetTest, InsertMany1) {
  s21::set<char> set1{'a', 'b'};
  auto v1 = set1.insert_many('c');
  EXPECT_EQ(set1.size(), 3);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(*(v1[0].first), 'c');
  EXPECT_EQ(v1[0].second, true);
}

TEST(SetTest, InsertMany2_1) {
  s21::set<char> set1{'a', 'b'};
  auto v1 = set1.insert_many('c', 'a');
  EXPECT_EQ(set1.size(), 3);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(*(v1[0].first), 'c');
  EXPECT_EQ(v1[0].second, true);
  EXPECT_EQ(*(v1[1].first), 'a');
  EXPECT_EQ(v1[1].second, false);
}

TEST(SetTest, InsertMany3_1) {
  s21::set<char> set1{'a', 'b'};
  auto v1 = set1.insert_many('b', 'c', 'a');
  EXPECT_EQ(set1.size(), 3);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(v1[0].first), 'b');
  EXPECT_EQ(v1[0].second, false);
  EXPECT_EQ(*(v1[1].first), 'c');
  EXPECT_EQ(v1[1].second, true);
  EXPECT_EQ(*(v1[2].first), 'a');
  EXPECT_EQ(v1[2].second, false);
}

TEST(SetTest, InsertMany5_3) {
  s21::set<char> set1{'a', 'b'};
  auto v1 = set1.insert_many('d', 'c', 'a', 'a', 'e');
  EXPECT_EQ(set1.size(), 5);
  auto it = set1.begin();
  EXPECT_EQ(*it, 'a');
  EXPECT_EQ(*(++it), 'b');
  EXPECT_EQ(*(++it), 'c');
  EXPECT_EQ(*(++it), 'd');
  EXPECT_EQ(*(++it), 'e');
  EXPECT_EQ(*(v1[0].first), 'd');
  EXPECT_EQ(v1[0].second, true);
  EXPECT_EQ(*(v1[1].first), 'c');
  EXPECT_EQ(v1[1].second, true);
  EXPECT_EQ(*(v1[2].first), 'a');
  EXPECT_EQ(v1[2].second, false);
  EXPECT_EQ(*(v1[3].first), 'a');
  EXPECT_EQ(v1[3].second, false);
  EXPECT_EQ(*(v1[4].first), 'e');
  EXPECT_EQ(v1[4].second, true);
}

TEST(SetTest, Swap) {
  s21::set<char> set1{'a', 'b'};
  s21::set<char> set2{'c', 'd'};
  set1.swap(set2);
  EXPECT_TRUE(set1.contains('c'));
  EXPECT_TRUE(set1.contains('d'));
  EXPECT_TRUE(set2.contains('a'));
  EXPECT_TRUE(set2.contains('b'));
}