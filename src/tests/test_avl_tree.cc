#include "../s21_avl_tree.h"
#include "gtest/gtest.h"

using s21::avl_tree;

// Тест на конструктор по умолчанию
TEST(AVLTreeTest, DefaultConstructor) {
  avl_tree<std::string, int> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0u);
  EXPECT_EQ(tree.begin(), tree.end());
}

// Тест на конструктор с initializer_list и итерацию (in-order traversal)
TEST(AVLTreeTest, InitializerListConstructor) {
  avl_tree<int, std::string> tree = {
      {3, "three"}, {1, "one"}, {4, "four"}, {2, "two"}, {5, "five"}};

  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 5u);

  // Проверяем наличие всех элементов
  for (int key : {1, 2, 3, 4, 5}) EXPECT_TRUE(tree.contains(key));

  // Итерируем по дереву – ожидается отсортированный порядок
  std::vector<std::pair<int, std::string>> traversal;
  for (auto it = tree.begin(); it != tree.end(); ++it) traversal.push_back(*it);
  std::vector<std::pair<int, std::string>> expected = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  EXPECT_EQ(traversal, expected);
}

// Тест на копирующий конструктор
TEST(AVLTreeTest, CopyConstructor) {
  avl_tree<int, std::string> tree = {
      {3, "three"}, {1, "one"}, {4, "four"}, {2, "two"}, {5, "five"}};
  avl_tree<int, std::string> copy(tree);
  EXPECT_EQ(copy.size(), tree.size());

  // Проверяем, что in-order обход копии совпадает с оригиналом
  std::vector<std::pair<int, std::string>> traversal, copyTraversal;
  for (auto it = tree.begin(); it != tree.end(); ++it) traversal.push_back(*it);
  for (auto it = copy.begin(); it != copy.end(); ++it)
    copyTraversal.push_back(*it);
  EXPECT_EQ(traversal, copyTraversal);
}

// Тест на конструктор перемещения
TEST(AVLTreeTest, MoveConstructor) {
  avl_tree<int, std::string> tree = {
      {3, "three"}, {1, "one"}, {4, "four"}, {2, "two"}, {5, "five"}};
  avl_tree<int, std::string> moved(std::move(tree));
  EXPECT_EQ(moved.size(), 5u);
  // После перемещения исходное дерево должно оказаться пустым
  EXPECT_TRUE(tree.empty());

  std::vector<std::pair<int, std::string>> expected = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  std::vector<std::pair<int, std::string>> movedTraversal;
  for (auto it = moved.begin(); it != moved.end(); ++it)
    movedTraversal.push_back(*it);
  EXPECT_EQ(movedTraversal, expected);
}

// Тест на оператор перемещающего присваивания
TEST(AVLTreeTest, MoveAssignment) {
  avl_tree<int, std::string> tree1 = {
      {10, "ten"}, {20, "twenty"}, {30, "thirty"}};

  avl_tree<int, std::string> tree2 = {{40, "forty"}, {50, "fifty"}};

  tree1 = std::move(tree2);
  EXPECT_EQ(tree1.size(), 2u);
  EXPECT_TRUE(tree2.empty());
  EXPECT_TRUE(tree1.contains(40));
  EXPECT_TRUE(tree1.contains(50));
}

// Тест на метод insert и работу с дубликатами
TEST(AVLTreeTest, Insert) {
  avl_tree<int, std::string> tree;
  tree.insert(std::pair<int, std::string>(10, "ten"));
  tree.insert(std::pair<int, std::string>(5, "five"));
  tree.insert(std::pair<int, std::string>(15, "fifteen"));
  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(), 3u);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(15));

  // Вставляем дубликат: в multiset всегда вставка успешна
  tree.insert(std::pair<int, std::string>(10, "ten"));
  EXPECT_EQ(tree.count(10), 2u);
}

// Тест на удаление по ключу (remove)
TEST(AVLTreeTest, Remove) {
  avl_tree<int, std::string> tree = {{20, "twenty"},
                                     {10, "ten"},
                                     {30, "thirty"},
                                     {25, "twenty five"},
                                     {35, "thirty five"}};

  EXPECT_EQ(tree.size(), 5u);
  EXPECT_TRUE(tree.contains(30));
  tree.remove(30);
  EXPECT_FALSE(tree.contains(30));
  EXPECT_EQ(tree.size(), 4u);

  // Удаление несуществующего ключа не должно повлиять на дерево
  tree.remove(100);
  EXPECT_EQ(tree.size(), 4u);
}

// Тест на удаление по итератору (erase)
TEST(AVLTreeTest, Erase) {
  avl_tree<int, std::string> tree = {
      {10, "ten"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"}};
  auto it = tree.find(20);
  ASSERT_NE(it, tree.end());
  tree.erase(it);
  EXPECT_FALSE(tree.contains(20));
  EXPECT_EQ(tree.size(), 3u);
}

// Тест на swap
TEST(AVLTreeTest, Swap) {
  avl_tree<int, std::string> tree1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  avl_tree<int, std::string> tree2 = {{4, "four"}, {5, "five"}, {6, "six"}};
  tree1.swap(tree2);
  EXPECT_TRUE(tree1.contains(4));
  EXPECT_TRUE(tree1.contains(5));
  EXPECT_TRUE(tree1.contains(6));
  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_TRUE(tree2.contains(3));
}

// Тест на merge
TEST(AVLTreeTest, Merge) {
  avl_tree<int, std::string> tree1 = {{1, "one"}, {3, "three"}, {5, "five"}};
  // двойное вхождение "3"
  avl_tree<int, std::string> tree2 = {{2, "two"}, {3, "three"}, {4, "four"}};
  tree1.merge(tree2);
  // После слияния второе дерево должно оказаться пустым
  EXPECT_TRUE(tree2.empty());
  // Проверяем, что все элементы присутствуют, в частности дубликаты
  EXPECT_EQ(tree1.count(3), 2u);

  std::vector<std::pair<int, std::string>> expected = {
      {1, "one"},   {2, "two"},  {3, "three"},
      {3, "three"}, {4, "four"}, {5, "five"}};

  std::vector<std::pair<int, std::string>> traversal;
  for (auto it = tree1.begin(); it != tree1.end(); ++it) {
    traversal.push_back(*it);
  }

  EXPECT_EQ(traversal, expected);
}

// Тест на методы count и contains
TEST(AVLTreeTest, CountContains) {
  avl_tree<int, std::string> tree;
  tree.insert(std::pair(50, "fifty"));
  tree.insert(std::pair(50, "fifty"));
  tree.insert(std::pair(30, "thirty"));
  tree.insert(std::pair(70, "seventy"));
  EXPECT_EQ(tree.count(50), 2u);
  EXPECT_TRUE(tree.contains(30));
  EXPECT_FALSE(tree.contains(100));
}

// Тест на метод find
TEST(AVLTreeTest, Find) {
  avl_tree<int, std::string> tree = {
      {10, "ten"}, {20, "twenty"}, {30, "thirty"}};

  auto it = tree.find(20);
  ASSERT_NE(it, tree.end());
  EXPECT_EQ((*it).first, 20);

  auto it_nonexist = tree.find(100);
  EXPECT_EQ(it_nonexist, tree.end());
}

// Тесты на lower_bound и upper_bound
TEST(AVLTreeTest, LowerBoundUpperBound) {
  avl_tree<int, std::string> tree = {
      {10, "ten"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"}};

  // lower_bound для несуществующего значения (ожидается 30)
  auto lb = tree.lower_bound(25);
  ASSERT_NE(lb, tree.end());
  EXPECT_EQ((*lb).first, 30);

  // upper_bound для существующего значения (upper_bound(30) -> 40)
  auto ub = tree.upper_bound(30);
  ASSERT_NE(ub, tree.end());
  EXPECT_EQ((*ub).first, 40);

  // Тестируем для ключа, который присутствует
  auto lb_eq = tree.lower_bound(20);
  ASSERT_NE(lb_eq, tree.end());
  EXPECT_EQ((*lb_eq).first, 20);
  auto ub_eq = tree.upper_bound(20);
  ASSERT_NE(ub_eq, tree.end());
  EXPECT_EQ((*ub_eq).first, 30);

  // Для ключа, превышающего максимальный элемент, итераторы должны быть end()
  EXPECT_EQ(tree.lower_bound(50), tree.end());
  EXPECT_EQ(tree.upper_bound(50), tree.end());
}

// Тест на метод equal_range
TEST(AVLTreeTest, EqualRange) {
  avl_tree<int, std::string> tree;
  // Вставляем несколько дубликатов
  tree.insert(std::pair(100, "hundred"));
  tree.insert(std::pair(50, "fifty"));
  tree.insert(std::pair(100, "hundred"));
  tree.insert(std::pair(150, "hundred fifty"));
  tree.insert(std::pair(100, "hundred"));

  auto range = tree.equal_range(100);
  size_t cntFromEqualRange = 0;
  for (auto it = range.first; it != range.second; ++it) {
    if ((*it).first == 100) cntFromEqualRange++;
  }
  EXPECT_EQ(cntFromEqualRange, tree.count(100));

  // Для отсутствующего ключа оба итератора должны совпадать.
  auto range_not = tree.equal_range(999);
  EXPECT_EQ(range_not.first, range_not.second);
}

// Тест на метод insert_many (вариативная вставка)
TEST(AVLTreeTest, InsertMany) {
  avl_tree<int, std::string> tree;
  auto results = tree.insert_many(std::pair(5, "five"), std::pair(2, "two"),
                                  std::pair(8, "eight"), std::pair(6, "six"),
                                  std::pair(10, "ten"));

  EXPECT_EQ(results.size(), 5u);
  for (const auto& p : results) {
    EXPECT_TRUE(p.second);
  }
  // Ожидаем отсортированный порядок при обходе дерева
  // 2, 5, 6, 8, 10
  std::vector<std::pair<int, std::string>> expected = {
      {2, "two"}, {5, "five"}, {6, "six"}, {8, "eight"}, {10, "ten"}};

  std::vector<std::pair<int, std::string>> traversal;
  for (auto it = tree.begin(); it != tree.end(); ++it) traversal.push_back(*it);
  EXPECT_EQ(traversal, expected);
}

// Тест итераторов (прямой и обратный обход)
TEST(AVLTreeTest, IteratorTraversal) {
  // 15, 10, 20, 8, 12, 16, 25
  avl_tree<int, std::string> tree = {
      {15, "fifteen"}, {10, "ten"},     {20, "twenty"},     {8, "eight"},
      {12, "twelve"},  {16, "sixteen"}, {25, "twenty five"}};

  std::vector<std::pair<int, std::string>> in_order;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    in_order.push_back(*it);
  }

  std::vector<std::pair<int, std::string>> expected = {
      {8, "eight"},    {10, "ten"},    {12, "twelve"},     {15, "fifteen"},
      {16, "sixteen"}, {20, "twenty"}, {25, "twenty five"}};

  EXPECT_EQ(in_order, expected);

  // Обратный обход: начиная от end() и используя оператор --
  std::vector<std::pair<int, std::string>> reverse;
  for (auto it = tree.end(); it != tree.begin();) {
    --it;
    reverse.push_back(*it);
  }

  std::vector<std::pair<int, std::string>> expected_reverse = {
      {25, "twenty five"}, {20, "twenty"}, {16, "sixteen"}, {15, "fifteen"},
      {12, "twelve"},      {10, "ten"},    {8, "eight"}};
  EXPECT_EQ(reverse, expected_reverse);
}

// Тест на метод clear
TEST(AVLTreeTest, Clear) {
  avl_tree<int, std::string> tree = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  EXPECT_FALSE(tree.empty());
  tree.clear();
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0u);
  EXPECT_EQ(tree.begin(), tree.end());
}

// Тест на max_size
TEST(AVLTreeTest, MaxSize) {
  avl_tree<int, int> tree;
  EXPECT_GT(tree.max_size(), 0u);
}

//
// Тесты для константных версий публичных методов
//

// Тест для константных begin() и end()
TEST(AVLTreeConstTest, ConstBeginEnd) {
  avl_tree<int, std::string> tree = {{10, "ten"},
                                     {20, "twenty"},
                                     {30, "thirty"},
                                     {40, "forty"},
                                     {50, "fifty"}};

  const avl_tree<int, std::string>& const_tree = tree;

  auto it = const_tree.begin();
  auto end = const_tree.end();
  std::vector<std::pair<int, std::string>> traversal;
  for (; it != end; ++it) {
    traversal.push_back(*it);
  }
  std::vector<std::pair<int, std::string>> expected = {{10, "ten"},
                                                       {20, "twenty"},
                                                       {30, "thirty"},
                                                       {40, "forty"},
                                                       {50, "fifty"}};
  EXPECT_EQ(traversal, expected);
}

// Тест для константного метода find()
TEST(AVLTreeConstTest, ConstFind) {
  avl_tree<int, std::string> tree = {
      {2, "two"}, {3, "three"}, {5, "five"}, {7, "seven"}, {11, "eleven"}};

  const avl_tree<int, std::string>& const_tree = tree;

  auto it = const_tree.find(7);
  ASSERT_NE(it, const_tree.end());
  EXPECT_EQ((*it).first, 7);

  auto not_found = const_tree.find(13);
  EXPECT_EQ(not_found, const_tree.end());
}

// Тест для константных lower_bound() и upper_bound()
TEST(AVLTreeConstTest, ConstLowerBoundUpperBound) {
  // {1, 3, 5, 7, 9};
  avl_tree<int, std::string> tree = {
      {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}, {9, "nine"}};

  const avl_tree<int, std::string>& const_tree = tree;

  auto lb = const_tree.lower_bound(6);
  ASSERT_NE(lb, const_tree.end());
  EXPECT_EQ((*lb).first, 7);

  auto ub = const_tree.upper_bound(7);
  ASSERT_NE(ub, const_tree.end());
  EXPECT_EQ((*ub).first, 9);

  // Для ключа, превышающего наибольший элемент, итераторы должны быть равны
  // end()
  EXPECT_EQ(const_tree.lower_bound(10), const_tree.end());
  EXPECT_EQ(const_tree.upper_bound(10), const_tree.end());
}

// Тест для константного метода equal_range()
TEST(AVLTreeConstTest, ConstEqualRange) {
  avl_tree<int, std::string> tree;
  tree.insert(std::pair(100, "hundred"));
  tree.insert(std::pair(50, "fifty"));
  tree.insert(std::pair(100, "hundred"));
  tree.insert(std::pair(150, "hundred fifty"));
  tree.insert(std::pair(100, "hundred"));

  const avl_tree<int, std::string>& const_tree = tree;
  auto range = const_tree.equal_range(100);
  size_t count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    if ((*it).first == 100) ++count;
  }
  EXPECT_EQ(count, const_tree.count(100));

  // Для отсутствующего ключа оба итератора должны совпадать
  auto empty_range = const_tree.equal_range(999);
  EXPECT_EQ(empty_range.first, empty_range.second);
}

// Тест для константных методов count() и contains()
TEST(AVLTreeConstTest, ConstCountContains) {
  avl_tree<int, std::string> tree;
  tree.insert(std::pair(42, "forty two"));
  tree.insert(std::pair(42, "forty two"));
  tree.insert(std::pair(100, "hundred"));

  const avl_tree<int, std::string>& const_tree = tree;
  EXPECT_EQ(const_tree.count(42), 2u);
  EXPECT_TRUE(const_tree.contains(42));
  EXPECT_FALSE(const_tree.contains(256));
}

// Тест обхода дерева с использованием константных итераторов
TEST(AVLTreeConstTest, ConstIteratorTraversal) {
  avl_tree<int, std::string> tree = {
      {8, "eight"},     {3, "three"}, {10, "ten"},  {1, "one"},      {6, "six"},
      {14, "fourteen"}, {4, "four"},  {7, "seven"}, {13, "thirteen"}};

  const avl_tree<int, std::string>& const_tree = tree;

  std::vector<std::pair<int, std::string>> in_order;
  for (auto it = const_tree.begin(); it != const_tree.end(); ++it)
    in_order.push_back(*it);

  std::vector<std::pair<int, std::string>> expected = {
      {1, "one"},  {3, "three"},     {4, "four"},
      {6, "six"},  {7, "seven"},     {8, "eight"},
      {10, "ten"}, {13, "thirteen"}, {14, "fourteen"}};

  EXPECT_EQ(in_order, expected);
}

TEST(AVLTreeConstTest, DecrementOperator) {
  s21::avl_tree<int, std::string> tree = {
      {5, "five"}, {3, "three"}, {7, "seven"}, {2, "two"},
      {4, "four"}, {6, "six"},   {8, "eight"}};

  std::vector<std::pair<int, std::string>> expected = {
      {8, "eight"}, {7, "seven"}, {6, "six"}, {5, "five"},
      {4, "four"},  {3, "three"}, {2, "two"}};

  std::vector<std::pair<int, std::string>> actual;

  s21::avl_tree<int, std::string>::const_iterator it = tree.end();

  while (it != tree.begin()) {
    --it;
    actual.push_back(*it);
  }
  EXPECT_EQ(actual, expected);
}

TEST(AVLTreeConstTest, ConstIteratorTraversal_2) {
  avl_tree<int, std::string> tree = {
      {8, "eight"},    {3, "three"},     {10, "ten"}, {1, "one"},
      {1, "one"},      {1, "one"},       {1, "one"},  {1, "one"},
      {1, "one"},      {1, "one"},       {1, "one"},  {1, "one"},
      {1, "one"},      {1, "one"},       {1, "one"},  {1, "one"},
      {6, "six"},      {14, "fourteen"}, {4, "four"}, {7, "seven"},
      {13, "thirteen"}};

  const avl_tree<int, std::string>& const_tree = tree;

  std::vector<std::pair<int, std::string>> in_order;
  for (auto it = const_tree.begin(); it != const_tree.end(); ++it)
    in_order.push_back(*it);

  std::vector<std::pair<int, std::string>> expected = {
      {1, "one"},      {1, "one"},   {1, "one"},  {1, "one"},
      {1, "one"},      {1, "one"},   {1, "one"},  {1, "one"},
      {1, "one"},      {1, "one"},   {1, "one"},  {1, "one"},
      {1, "one"},      {3, "three"}, {4, "four"}, {6, "six"},
      {7, "seven"},    {8, "eight"}, {10, "ten"}, {13, "thirteen"},
      {14, "fourteen"}};

  EXPECT_EQ(in_order, expected);
}
