#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_avl_tree.h"

namespace s21 {

template <typename Key>
class multiset : public AVLTree<Key> {
 public:
  using AVLTree<Key>::AVLTree;
};

}  // namespace s21

#endif  // S21_MULTISET_H