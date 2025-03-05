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
