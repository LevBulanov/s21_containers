#include "../s21_vector.h"
#include "gtest/gtest.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 3);
}

TEST(VectorTest, SizeConstructor) {
  s21::vector<int> vec(5);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = vec1;
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2.capacity(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = std::move(vec1);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2.capacity(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec1.capacity(), 0);
}