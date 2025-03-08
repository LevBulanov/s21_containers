#include <stdexcept>

#include "../s21_array.h"
#include "gtest/gtest.h"

TEST(ArrayTest, DefaultEmptyConstructor) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
}

TEST(ArrayTest, InitializerListConstructorTooManyElements) {
  try {
    s21::array<int, 4> arr = {1, 2, 3, 4, 5};
  } catch (std::out_of_range &e) {
    EXPECT_STREQ(e.what(), "Too many elements in the initializer list");
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = arr1;
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = {5, 6, 7, 8};
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, At) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_THROW(arr.at(4), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest, BeginEnd) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  auto begin = arr.begin();
  auto end = arr.end();
  EXPECT_EQ(*begin, 1);
  ++begin;
  EXPECT_EQ(*begin, 2);
  ++begin;
  EXPECT_EQ(*begin, 3);
  ++begin;
  EXPECT_EQ(*begin, 4);
  ++begin;
  EXPECT_EQ(begin, end);
}

TEST(ArrayTest, Data) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  int *data = arr.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[3], 4);
}

TEST(ArrayTest, Empty) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.empty(), true);
}

TEST(ArrayTest, NonEmpty) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.empty(), false);
}

TEST(ArrayTest, Size) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.max_size(), 4);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = {5, 6, 7, 8};
  arr1.swap(arr2);
  EXPECT_EQ(arr1.size(), 4);
  EXPECT_EQ(arr1[0], 5);
  EXPECT_EQ(arr1[1], 6);
  EXPECT_EQ(arr1[2], 7);
  EXPECT_EQ(arr1[3], 8);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 4> arr;
  arr.fill(5);
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 5);
  EXPECT_EQ(arr[2], 5);
  EXPECT_EQ(arr[3], 5);
}