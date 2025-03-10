#include "../s21_avl_tree.h"
#include "gtest/gtest.h"

using s21::AVLTree;

// Тест на конструктор по умолчанию
TEST(AVLTreeTest, DefaultConstructor) {
  AVLTree<std::string, int> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(), 0u);
  EXPECT_EQ(tree.begin(), tree.end());
}

// Тест на конструктор с initializer_list и итерацию (in-order traversal)
TEST(AVLTreeTest, InitializerListConstructor) {
  AVLTree<int, std::string> tree = {
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
  AVLTree<int> tree = {3, 1, 4, 2, 5};
  AVLTree<int> copy(tree);
  EXPECT_EQ(copy.size(), tree.size());

  // Проверяем, что in-order обход копии совпадает с оригиналом
  std::vector<int> traversal, copyTraversal;
  for (auto it = tree.begin(); it != tree.end(); ++it) traversal.push_back(*it);
  for (auto it = copy.begin(); it != copy.end(); ++it)
    copyTraversal.push_back(*it);
  EXPECT_EQ(traversal, copyTraversal);
}

// // Тест на конструктор перемещения
// TEST(AVLTreeTest, MoveConstructor) {
//   AVLTree<int> tree = {3, 1, 4, 2, 5};
//   AVLTree<int> moved(std::move(tree));
//   EXPECT_EQ(moved.size(), 5u);
//   // После перемещения исходное дерево должно оказаться пустым
//   EXPECT_TRUE(tree.empty());

//   std::vector<int> expected = {1, 2, 3, 4, 5};
//   std::vector<int> movedTraversal;
//   for (auto it = moved.begin(); it != moved.end(); ++it)
//     movedTraversal.push_back(*it);
//   EXPECT_EQ(movedTraversal, expected);
// }

// // Тест на оператор перемещающего присваивания
// TEST(AVLTreeTest, MoveAssignment) {
//   AVLTree<int> tree1 = {10, 20, 30};
//   AVLTree<int> tree2 = {40, 50};
//   tree1 = std::move(tree2);
//   EXPECT_EQ(tree1.size(), 2u);
//   EXPECT_TRUE(tree2.empty());
//   EXPECT_TRUE(tree1.contains(40));
//   EXPECT_TRUE(tree1.contains(50));
// }

// // Тест на метод insert и работу с дубликатами
// TEST(AVLTreeTest, Insert) {
//   AVLTree<int> tree;
//   tree.insert(10);
//   tree.insert(5);
//   tree.insert(15);
//   EXPECT_FALSE(tree.empty());
//   EXPECT_EQ(tree.size(), 3u);
//   EXPECT_TRUE(tree.contains(10));
//   EXPECT_TRUE(tree.contains(5));
//   EXPECT_TRUE(tree.contains(15));

//   // Вставляем дубликат: в multiset всегда вставка успешна
//   tree.insert(10);
//   EXPECT_EQ(tree.count(10), 2u);
// }

// // Тест на удаление по ключу (remove)
// TEST(AVLTreeTest, Remove) {
//   AVLTree<int> tree = {20, 10, 30, 25, 35};
//   EXPECT_TRUE(tree.contains(30));
//   tree.remove(30);
//   EXPECT_FALSE(tree.contains(30));

//   // Удаление несуществующего ключа не должно повлиять на дерево
//   tree.remove(100);
//   EXPECT_EQ(tree.size(), 4u);
// }

// // Тест на удаление по итератору (erase)
// TEST(AVLTreeTest, Erase) {
//   AVLTree<int> tree = {10, 20, 30, 40};
//   auto it = tree.find(20);
//   ASSERT_NE(it, tree.end());
//   tree.erase(it);
//   EXPECT_FALSE(tree.contains(20));
//   EXPECT_EQ(tree.size(), 3u);
// }

// // Тест на swap
// TEST(AVLTreeTest, Swap) {
//   AVLTree<int> tree1 = {1, 2, 3};
//   AVLTree<int> tree2 = {4, 5, 6};
//   tree1.swap(tree2);
//   EXPECT_TRUE(tree1.contains(4));
//   EXPECT_TRUE(tree1.contains(5));
//   EXPECT_TRUE(tree1.contains(6));
//   EXPECT_TRUE(tree2.contains(1));
//   EXPECT_TRUE(tree2.contains(2));
//   EXPECT_TRUE(tree2.contains(3));
// }

// // Тест на merge
// TEST(AVLTreeTest, Merge) {
//   AVLTree<int> tree1 = {1, 3, 5};
//   AVLTree<int> tree2 = {2, 3, 4};  // двойное вхождение "3"
//   tree1.merge(tree2);
//   // После слияния второе дерево должно оказаться пустым
//   EXPECT_TRUE(tree2.empty());
//   // Проверяем, что все элементы присутствуют, в частности дубликаты
//   EXPECT_EQ(tree1.count(3), 2u);

//   std::vector<int> expected = {1, 2, 3, 3, 4, 5};
//   std::vector<int> traversal;
//   for (auto it = tree1.begin(); it != tree1.end(); ++it)
//     traversal.push_back(*it);
//   EXPECT_EQ(traversal, expected);
// }

// // Тест на методы count и contains
// TEST(AVLTreeTest, CountContains) {
//   AVLTree<int> tree;
//   tree.insert(50);
//   tree.insert(50);
//   tree.insert(30);
//   tree.insert(70);
//   EXPECT_EQ(tree.count(50), 2u);
//   EXPECT_TRUE(tree.contains(30));
//   EXPECT_FALSE(tree.contains(100));
// }

// // Тест на метод find
// TEST(AVLTreeTest, Find) {
//   AVLTree<int> tree = {10, 20, 30};
//   auto it = tree.find(20);
//   ASSERT_NE(it, tree.end());
//   EXPECT_EQ(*it, 20);

//   auto it_nonexist = tree.find(100);
//   EXPECT_EQ(it_nonexist, tree.end());
// }

// // Тесты на lower_bound и upper_bound
// TEST(AVLTreeTest, LowerBoundUpperBound) {
//   AVLTree<int> tree = {10, 20, 30, 40};

//   // lower_bound для несуществующего значения (ожидается 30)
//   auto lb = tree.lower_bound(25);
//   ASSERT_NE(lb, tree.end());
//   EXPECT_EQ(*lb, 30);

//   // upper_bound для существующего значения (upper_bound(30) -> 40)
//   auto ub = tree.upper_bound(30);
//   ASSERT_NE(ub, tree.end());
//   EXPECT_EQ(*ub, 40);

//   // Тестируем для ключа, который присутствует
//   auto lb_eq = tree.lower_bound(20);
//   ASSERT_NE(lb_eq, tree.end());
//   EXPECT_EQ(*lb_eq, 20);
//   auto ub_eq = tree.upper_bound(20);
//   ASSERT_NE(ub_eq, tree.end());
//   EXPECT_EQ(*ub_eq, 30);

//   // Для ключа, превышающего максимальный элемент, итераторы должны быть
//   end() EXPECT_EQ(tree.lower_bound(50), tree.end());
//   EXPECT_EQ(tree.upper_bound(50), tree.end());
// }

// // Тест на метод equal_range
// TEST(AVLTreeTest, EqualRange) {
//   AVLTree<int> tree;
//   // Вставляем несколько дубликатов
//   tree.insert(100);
//   tree.insert(50);
//   tree.insert(100);
//   tree.insert(150);
//   tree.insert(100);

//   auto range = tree.equal_range(100);
//   size_t cntFromEqualRange = 0;
//   for (auto it = range.first; it != range.second; ++it) {
//     if (*it == 100) cntFromEqualRange++;
//   }
//   EXPECT_EQ(cntFromEqualRange, tree.count(100));

//   // Для отсутствующего ключа оба итератора должны совпадать.
//   auto range_not = tree.equal_range(999);
//   EXPECT_EQ(range_not.first, range_not.second);
// }

// // Тест на метод insert_many (вариативная вставка)
// TEST(AVLTreeTest, InsertMany) {
//   AVLTree<int> tree;
//   auto results = tree.insert_many(5, 2, 8, 6, 10);
//   EXPECT_EQ(results.size(), 5u);
//   for (const auto& p : results) {
//     EXPECT_TRUE(p.second);
//   }
//   // Ожидаем отсортированный порядок при обходе дерева
//   std::vector<int> expected = {2, 5, 6, 8, 10};
//   std::vector<int> traversal;
//   for (auto it = tree.begin(); it != tree.end(); ++it)
//   traversal.push_back(*it); EXPECT_EQ(traversal, expected);
// }

// // Тест итераторов (прямой и обратный обход)
// TEST(AVLTreeTest, IteratorTraversal) {
//   AVLTree<int> tree = {15, 10, 20, 8, 12, 16, 25};
//   std::vector<int> in_order;
//   for (auto it = tree.begin(); it != tree.end(); ++it) {
//     in_order.push_back(*it);
//   }
//   std::vector<int> expected = {8, 10, 12, 15, 16, 20, 25};
//   EXPECT_EQ(in_order, expected);

//   // Обратный обход: начиная от end() и используя оператор --
//   std::vector<int> reverse;
//   for (auto it = tree.end(); it != tree.begin();) {
//     --it;
//     reverse.push_back(*it);
//   }
//   std::vector<int> expected_reverse = {25, 20, 16, 15, 12, 10, 8};
//   EXPECT_EQ(reverse, expected_reverse);
// }

// // Тест на метод clear
// TEST(AVLTreeTest, Clear) {
//   AVLTree<int> tree = {1, 2, 3, 4, 5};
//   EXPECT_FALSE(tree.empty());
//   tree.clear();
//   EXPECT_TRUE(tree.empty());
//   EXPECT_EQ(tree.size(), 0u);
//   EXPECT_EQ(tree.begin(), tree.end());
// }

// // Тест на max_size
// TEST(AVLTreeTest, MaxSize) {
//   AVLTree<int> tree;
//   EXPECT_GT(tree.max_size(), 0u);
// }

// //
// // Тесты для константных версий публичных методов
// //

// // Тест для константных begin() и end()
// TEST(AVLTreeConstTest, ConstBeginEnd) {
//   AVLTree<int> tree = {10, 20, 30, 40, 50};
//   const AVLTree<int>& const_tree = tree;

//   auto it = const_tree.begin();
//   auto end = const_tree.end();
//   std::vector<int> traversal;
//   for (; it != end; ++it) {
//     traversal.push_back(*it);
//   }
//   // Ожидается отсортированный порядок при обходе
//   std::vector<int> expected = {10, 20, 30, 40, 50};
//   EXPECT_EQ(traversal, expected);
// }

// // Тест для константного метода find()
// TEST(AVLTreeConstTest, ConstFind) {
//   AVLTree<int> tree = {2, 3, 5, 7, 11};
//   const AVLTree<int>& const_tree = tree;

//   auto it = const_tree.find(7);
//   ASSERT_NE(it, const_tree.end());
//   EXPECT_EQ(*it, 7);

//   auto not_found = const_tree.find(13);
//   EXPECT_EQ(not_found, const_tree.end());
// }

// // Тест для константных lower_bound() и upper_bound()
// TEST(AVLTreeConstTest, ConstLowerBoundUpperBound) {
//   AVLTree<int> tree = {1, 3, 5, 7, 9};
//   const AVLTree<int>& const_tree = tree;

//   auto lb = const_tree.lower_bound(6);
//   ASSERT_NE(lb, const_tree.end());
//   EXPECT_EQ(*lb, 7);

//   auto ub = const_tree.upper_bound(7);
//   ASSERT_NE(ub, const_tree.end());
//   EXPECT_EQ(*ub, 9);

//   // Для ключа, превышающего наибольший элемент, итераторы должны быть равны
//   // end()
//   EXPECT_EQ(const_tree.lower_bound(10), const_tree.end());
//   EXPECT_EQ(const_tree.upper_bound(10), const_tree.end());
// }

// // Тест для константного метода equal_range()
// TEST(AVLTreeConstTest, ConstEqualRange) {
//   AVLTree<int> tree;
//   tree.insert(100);
//   tree.insert(50);
//   tree.insert(100);
//   tree.insert(150);
//   tree.insert(100);

//   const AVLTree<int>& const_tree = tree;
//   auto range = const_tree.equal_range(100);
//   size_t count = 0;
//   for (auto it = range.first; it != range.second; ++it) {
//     if (*it == 100) ++count;
//   }
//   EXPECT_EQ(count, const_tree.count(100));

//   // Для отсутствующего ключа оба итератора должны совпадать
//   auto empty_range = const_tree.equal_range(999);
//   EXPECT_EQ(empty_range.first, empty_range.second);
// }

// // Тест для константных методов count() и contains()
// TEST(AVLTreeConstTest, ConstCountContains) {
//   AVLTree<int> tree;
//   tree.insert(42);
//   tree.insert(42);
//   tree.insert(100);

//   const AVLTree<int>& const_tree = tree;
//   EXPECT_EQ(const_tree.count(42), 2u);
//   EXPECT_TRUE(const_tree.contains(42));
//   EXPECT_FALSE(const_tree.contains(256));
// }

// // Тест обхода дерева с использованием константных итераторов
// TEST(AVLTreeConstTest, ConstIteratorTraversal) {
//   AVLTree<int> tree = {8, 3, 10, 1, 6, 14, 4, 7, 13};
//   const AVLTree<int>& const_tree = tree;

//   std::vector<int> in_order;
//   for (auto it = const_tree.begin(); it != const_tree.end(); ++it)
//     in_order.push_back(*it);

//   std::vector<int> expected = {1, 3, 4, 6, 7, 8, 10, 13, 14};
//   EXPECT_EQ(in_order, expected);
// }

// TEST(AVLTreeConstTest, DecrementOperator) {
//   s21::AVLTree<int> tree{5, 3, 7, 2, 4, 6, 8};

//   std::vector<int> expected = {8, 7, 6, 5, 4, 3, 2};
//   std::vector<int> actual;

//   s21::AVLTree<int>::const_iterator it = tree.end();

//   while (it != tree.begin()) {
//     --it;
//     actual.push_back(*it);
//   }
//   EXPECT_EQ(actual, expected);
// }

// TEST(AVLTreeConstTest, ConstIteratorTraversal_2) {
//   AVLTree<int> tree = {8, 3, 10, 1, 1, 1, 1, 1,  1, 1, 1,
//                        1, 1, 1,  1, 1, 1, 6, 14, 4, 7, 13};
//   const AVLTree<int>& const_tree = tree;

//   std::vector<int> in_order;
//   for (auto it = const_tree.begin(); it != const_tree.end(); ++it)
//     in_order.push_back(*it);

//   std::vector<int> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,
//                                1, 1, 1, 3, 4, 6, 7, 8, 10, 13, 14};
//   EXPECT_EQ(in_order, expected);
// }
