#include <string>

#include "../s21_set.h"
#include "gtest/gtest.h"

TEST(SetTest, EmptySet) {
  s21::set<int> set1;
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set1.size(), 0);
  set1.insert(1);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 1);
  set1.insert(1);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 1);
  set1.insert(2);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 2);
  set1.insert(0);
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 3);
  set1.clear();
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set1.size(), 0);
}

TEST(SetTest, Begin) {
  s21::set<int> set1;
  auto it = set1.begin();
  EXPECT_EQ(*it, 0);
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
  EXPECT_EQ(*it, 0);
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
  EXPECT_EQ(*(++it), 0);
  it = set1.end();
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(--it), 4);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*(--it), 1);
  EXPECT_EQ(*(--it), 1);
}

TEST(SetTest, IteratorEmptySet) {
  s21::set<int> set1;
  auto it = set1.begin();
  auto it2 = set1.end();
  EXPECT_EQ(it, it2);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*(++it), 0);
  EXPECT_EQ(*it2, 0);
  EXPECT_EQ(*(++it2), 0);
  set1.insert(10);
  EXPECT_EQ(*(++it), 10);
  EXPECT_EQ(*(--it2), 10);
}

TEST(SetTest, Iterator1) {
  s21::set<int> set1{4, 3, 2, 1};
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 4);
  EXPECT_EQ(*(++it), 0);
  it = set1.end();
  EXPECT_EQ(*(--it), 4);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*(--it), 1);
  EXPECT_EQ(*(--it), 1);
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
  it = set1.end();
  EXPECT_EQ(*(--it), "Peter");
  EXPECT_EQ(*(--it), "Nina");
  EXPECT_EQ(*(--it), "Masha");
  EXPECT_EQ(*(--it), "Inna");
  EXPECT_EQ(*(--it), "Anna");
  EXPECT_EQ(*(--it), "Alex");
  EXPECT_EQ(*(--it), "Alex");
  EXPECT_EQ(*(--it), "Alex");
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
