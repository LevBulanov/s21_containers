#include "../s21_map.h"
#include "gtest/gtest.h"

TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> map;
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.at("one"), 1);
  EXPECT_EQ(map.at("two"), 2);
  EXPECT_EQ(map.at("three"), 3);
}

TEST(MapTest, CopyConstructor) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> map_copy(map);
  EXPECT_EQ(map_copy.size(), 3);
  EXPECT_EQ(map_copy.at("one"), 1);
  EXPECT_EQ(map_copy.at("two"), 2);
  EXPECT_EQ(map_copy.at("three"), 3);
}

TEST(MapTest, MoveConstructor) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> map_move(std::move(map));
  EXPECT_EQ(map_move.size(), 3);
  EXPECT_EQ(map_move.at("one"), 1);
  EXPECT_EQ(map_move.at("two"), 2);
  EXPECT_EQ(map_move.at("three"), 3);
}

TEST(MapTest, MoveAssignment) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> map_copy;
  map_copy = std::move(map);
  EXPECT_EQ(map_copy.size(), 3);
  EXPECT_EQ(map_copy.at("one"), 1);
  EXPECT_EQ(map_copy.at("two"), 2);
  EXPECT_EQ(map_copy.at("three"), 3);
}

TEST(MapTest, At) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  EXPECT_EQ(map.at("one"), 1);
  EXPECT_EQ(map.at("two"), 2);
  EXPECT_EQ(map.at("three"), 3);
  EXPECT_THROW(map.at("four"), std::out_of_range);
}

TEST(MapTest, OperatorBracket) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  EXPECT_EQ(map["one"], 1);
  EXPECT_EQ(map["two"], 2);
  EXPECT_EQ(map["three"], 3);
  map["four"] = 4;
  EXPECT_EQ(map["four"], 4);
}

TEST(MapTest, Begin) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  auto it = map.begin();
  EXPECT_EQ(it->first, "one");
  EXPECT_EQ(it->second, 1);
}

TEST(MapTest, End) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  auto it = map.end();
  EXPECT_EQ(it, map.end());
  --it;
  EXPECT_EQ(it->first, "two");
  EXPECT_EQ(it->second, 2);
}

TEST(MapTest, Empty) {
  s21::map<std::string, int> map;
  EXPECT_TRUE(map.empty());
  map["one"] = 1;
  EXPECT_FALSE(map.empty());
}

TEST(MapTest, Size) {
  s21::map<std::string, int> map;
  EXPECT_EQ(map.size(), 0);
  map["one"] = 1;
  map["two"] = 2;
  map["three"] = 3;
  EXPECT_EQ(map.size(), 3);
}

TEST(MapTest, MaxSize) {
  s21::map<std::string, int> map;
  EXPECT_GT(map.max_size(), 0);
}

TEST(MapTest, Clear) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, Insert) {
  s21::map<std::string, int> map;
  auto pair = map.insert({"one", 1});
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(pair.first->first, "one");
  EXPECT_EQ(pair.first->second, 1);
  EXPECT_EQ(pair.second, true);
  pair = map.insert({"one", 1});
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(pair.first->first, "one");
  EXPECT_EQ(pair.first->second, 1);
  EXPECT_EQ(pair.second, false);
  pair = map.insert({"two", 2});
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(pair.first->first, "two");
  EXPECT_EQ(pair.first->second, 2);
  EXPECT_EQ(pair.second, true);
  pair = map.insert({"zero", 0});
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(pair.first->first, "zero");
  EXPECT_EQ(pair.first->second, 0);
  EXPECT_EQ(pair.second, true);
}

TEST(MapTest, InsertNonPair) {
  s21::map<std::string, int> map;
  auto pair = map.insert("one", 1);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(pair.first->first, "one");
  EXPECT_EQ(pair.first->second, 1);
  EXPECT_EQ(pair.second, true);
  pair = map.insert("one", 1);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(pair.first->first, "one");
  EXPECT_EQ(pair.first->second, 1);
  EXPECT_EQ(pair.second, false);
  pair = map.insert("two", 2);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(pair.first->first, "two");
  EXPECT_EQ(pair.first->second, 2);
  EXPECT_EQ(pair.second, true);
  pair = map.insert("zero", 0);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(pair.first->first, "zero");
  EXPECT_EQ(pair.first->second, 0);
  EXPECT_EQ(pair.second, true);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  auto pair = map.insert_or_assign("one", 10);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(pair.first->first, "one");
  EXPECT_EQ(pair.first->second, 10);
  EXPECT_EQ(pair.second, false);
  pair = map.insert_or_assign("four", 4);
  EXPECT_EQ(map.size(), 4);
  EXPECT_EQ(pair.first->first, "four");
  EXPECT_EQ(pair.first->second, 4);
  EXPECT_EQ(pair.second, true);
}

TEST(MapTest, Erase) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  auto it = map.find("two");
  map.erase(it);
  EXPECT_EQ(map.size(), 2);
  it = map.find("one");
  map.erase(it);
  EXPECT_EQ(map.size(), 1);
  it = map.find("three");
  map.erase(it);
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, Swap) {
  s21::map<std::string, int> map1 = {{"one", 1}, {"two", 2}, {"three", 3}};
  s21::map<std::string, int> map2 = {{"four", 4}, {"five", 5}, {"six", 6}};
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 3);
  EXPECT_EQ(map1.at("four"), 4);
  EXPECT_EQ(map1.at("five"), 5);
  EXPECT_EQ(map1.at("six"), 6);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2.at("one"), 1);
  EXPECT_EQ(map2.at("two"), 2);
  EXPECT_EQ(map2.at("three"), 3);
}

TEST(MapTest, Merge) {
  s21::map<std::string, int> map1 = {{"one", 1}, {"three", 3}, {"five", 5}};
  s21::map<std::string, int> map2 = {{"two", 2}, {"three", 3}, {"four", 4}};
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 6);
  EXPECT_EQ(map1.at("one"), 1);
  EXPECT_EQ(map1.at("two"), 2);
  EXPECT_EQ(map1.at("three"), 3);
  EXPECT_EQ(map1.at("four"), 4);
}

TEST(MapTest, Contains) {
  s21::map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};
  EXPECT_TRUE(map.contains("one"));
  EXPECT_TRUE(map.contains("two"));
  EXPECT_TRUE(map.contains("three"));
  EXPECT_FALSE(map.contains("four"));
}