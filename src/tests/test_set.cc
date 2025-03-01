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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
