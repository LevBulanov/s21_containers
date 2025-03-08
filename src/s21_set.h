#ifndef S21_CONTAINERS_SET_H
#define S21_CONTAINERS_SET_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

#include "s21_avl_tree.h"

namespace s21 {

template <typename Key>
class set : public AVLTree<Key> {
 public:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using Node = typename AVLTree<Key>::Node;
  using iterator = typename AVLTree<Key>::iterator;
  using const_iterator = typename AVLTree<Key>::const_iterator;

  // constructors
  set() : AVLTree<Key>() {}
  set(std::initializer_list<value_type> const& items) : set() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      insert(*it);
    }
  }
  set(const set& other) : set() {
    this->root_ = this->copyTree(other.root_, nullptr);
  }
  set(set&& other) noexcept : AVLTree<Key>() {
    this->root_ = other.root_;
    other.root_ = nullptr;
  }
  // destructor
  ~set() {}

  set& operator=(const set& other) {
    if (this != &other) {
      this->clear();
      this->root_ = this->copyTree(other.root_, nullptr);
    }
    return *this;
  }

  set& operator=(set&& other) noexcept {
    if (this != &other) {
      this->clear();
      this->root_ = other.root_;
      other.root_ = nullptr;
    }
    return *this;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(args));
    ((results.push_back(this->insert(std::forward<Args>(args)))), ...);
    return results;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = this->find(value);
    std::pair<iterator, bool> result = {it, false};
    if (it == this->end()) {
      Node* insertedNode = nullptr;
      this->root_ =
          AVLTree<Key>::insert(this->root_, value, nullptr, &insertedNode);
      result.first = iterator(insertedNode, this);
      result.second = true;
    }
    return result;
  }

  void merge(set& other) {
    if (this == &other) return;
    this->mergeNodes(other.root_);
    other.root_ = nullptr;
  }

 private:
  void mergeNodes(Node* node) {
    if (!node) return;
    mergeNodes(node->left);
    mergeNodes(node->right);
    // «Отрываем» данный узел от дерева-источника
    node->left = node->right = nullptr;
    node->parent = nullptr;
    // Вставляем узел в текущее дерево, если не дубль
    if (!this->contains(node->key)) {
      this->root_ = this->insertNode(this->root_, node, nullptr);
    } else {
      delete node;
    }
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SET_H