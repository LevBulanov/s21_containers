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

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2;
  vec2 = std::move(vec1);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2.capacity(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, At) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.at(2), 3);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(VectorTest, OperatorBracket) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, Front) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.front(), 1);
}

TEST(VectorTest, Back) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.back(), 3);
}

TEST(VectorTest, Data) {
  s21::vector<int> vec = {1, 2, 3};
  int *data = vec.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
}

TEST(VectorTest, Begin) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, End) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.end();
  auto data = vec.data();
  EXPECT_EQ(it, data + vec.size());
}

TEST(VectorTest, IteratorAdvance) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, IteratorDecrement) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, IteratorComparison) {
  s21::vector<int> vec = {1, 2, 3};
  auto it1 = vec.begin();
  auto it2 = vec.begin();
  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);

  auto it3 = vec.end();
  --it3;
  ++it1;
  EXPECT_EQ(it1, it3);
}

TEST(VectorTest, IteratorDereference) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, Empty) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, NonEmpty) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.max_size(), std::numeric_limits<size_t>::max());
}

TEST(VectorTest, Reserve) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.capacity(), 3);
  vec.reserve(5);
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(5);
  EXPECT_EQ(vec.capacity(), 5);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 3);
}

TEST(VectorTest, Clear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 3);
}

TEST(VectorTest, Insert) {
  s21::vector<int> vec = {1, 2, 3};
  auto pos = vec.begin();
  ++pos;
  ++pos;
  auto it = vec.insert(pos, 4);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 4);
  EXPECT_EQ(vec[3], 3);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, Erase) {
  s21::vector<int> vec = {1, 2, 3};
  auto pos = vec.begin();
  ++pos;
  vec.erase(pos);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.push_back(4);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
}

TEST(VectorTest, PopBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Swap) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5, 6, 7};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 4);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec1[1], 5);
  EXPECT_EQ(vec1[2], 6);
  EXPECT_EQ(vec1[3], 7);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> vec = {1, 2, 3};
  auto pos = vec.begin();
  ++pos;
  vec.insert_many(pos, 4, 5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 4);
  EXPECT_EQ(vec[2], 5);
  EXPECT_EQ(vec[3], 2);
  EXPECT_EQ(vec[4], 3);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.insert_many_back(4, 5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}
