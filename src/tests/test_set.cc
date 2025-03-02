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
  EXPECT_EQ(*it, 5);
  set1.insert(7);
  set1.insert(6);
  it = set1.end();
  EXPECT_EQ(*it, 7);
  set1.insert(10);
  it = set1.end();
  EXPECT_EQ(*it, 10);
}

TEST(SetTest, ListConstructor) {
  s21::set<int> set1{1, 2, 3, 4, 2, 3};
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set1.size(), 4);
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 4);
  it = set1.end();
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(SetTest, IteratorEmptySet) {
  s21::set<int> set1;
  auto it = set1.begin();
  auto it2 = set1.end();
  EXPECT_EQ(it, it2);
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 0);
  it = set1.end();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 0);
  set1.insert(10);
  ++it;
  EXPECT_EQ(*it, 10);
  --it2;
  EXPECT_EQ(*it2, 10);
}

TEST(SetTest, Iterator1) {
  s21::set<int> set1{4, 3, 2, 1};
  auto it = set1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 4);
  it = set1.end();
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(SetTest, Iterator2) {
  s21::set<std::string> set1{"Nina", "Anna", "Peter", "Alex", "Inna", "Masha"};
  auto it = set1.begin();
  EXPECT_EQ(*it, "Alex");
  ++it;
  EXPECT_EQ(*it, "Anna");
  ++it;
  EXPECT_EQ(*it, "Inna");
  ++it;
  EXPECT_EQ(*it, "Masha");
  ++it;
  EXPECT_EQ(*it, "Nina");
  ++it;
  EXPECT_EQ(*it, "Peter");
  ++it;
  EXPECT_EQ(*it, "Peter");
  it = set1.end();
  EXPECT_EQ(*it, "Peter");
  --it;
  EXPECT_EQ(*it, "Nina");
  --it;
  EXPECT_EQ(*it, "Masha");
  --it;
  EXPECT_EQ(*it, "Inna");
  --it;
  EXPECT_EQ(*it, "Anna");
  --it;
  EXPECT_EQ(*it, "Alex");
  --it;
  EXPECT_EQ(*it, "Alex");
  --it;
  EXPECT_EQ(*it, "Alex");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
