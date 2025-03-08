#include "../s21_map.h"
#include "gtest/gtest.h"

TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> map;
  EXPECT_EQ(map.size(), 0);
}