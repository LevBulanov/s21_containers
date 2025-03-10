#ifndef S21_CONTAINERS_SET_H
#define S21_CONTAINERS_SET_H

#include <initializer_list>
#include <limits>

#include "s21_avl_tree.h"

namespace s21 {

template <typename Key>
class set : public avl_tree<Key, Key> {
 public:
  using value_type = Key;
  using key_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using Node = typename s21::avl_tree<value_type, value_type>::Node;
  using base = typename s21::avl_tree<value_type, value_type>;
  using base_iterator =
      typename s21::avl_tree<value_type, value_type>::iterator;
  using base_const_iterator =
      typename s21::avl_tree<value_type, value_type>::const_iterator;

  class iterator {
   public:
    iterator() = default;
    iterator(base_iterator it) : it_(it) {}
    const_reference operator*() { return (*it_).first; }

    bool operator==(const iterator& other) const {
      return this->it_ == other.it_;
    }

    bool operator!=(const iterator& other) const {
      return !this->operator==(other);
    }

    iterator& operator++() {
      ++it_;
      return *this;
    }

    iterator& operator--() {
      --it_;
      return *this;
    }

   private:
    base_iterator it_;
    friend class set;
  };

  class const_iterator {
   public:
    const_iterator() = default;
    const_iterator(base_const_iterator it) : it_(it) {}
    const_iterator(const iterator& it) : it_(it) {}
    const_reference operator*() const { return (*it_).first; }

    bool operator==(const const_iterator& other) const {
      return this->it_ == other.it_;
    }

    bool operator!=(const const_iterator& other) const {
      return !this->operator==(other);
    }

    const_iterator& operator++() {
      ++it_;
      return *this;
    }

    const_iterator& operator--() {
      --it_;
      return *this;
    }

   private:
    base_const_iterator it_;
    friend class set;
  };

  // constructors
  set() : avl_tree<value_type, value_type>() {}

  set(std::initializer_list<value_type> const& items) : set() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      insert(*it);
    }
  }

  set(const set& other) : set() {
    this->root_ = this->copyTree(other.root_, nullptr);
  }

  set(set&& other) noexcept : avl_tree<value_type, value_type>() {
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

  iterator find(const value_type& val) { return iterator(base::find(val)); }

  const_iterator find(const value_type& val) const {
    return const_iterator(base::find(val));
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(args));
    ((results.push_back(this->insert(std::forward<Args>(args)))), ...);
    return results;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = iterator(this->find(value));
    std::pair<iterator, bool> result = {it, false};
    if (should_insert(it)) {
      Node* insertedNode = nullptr;
      this->root_ = avl_tree<value_type, value_type>::insert(
          this->root_, std::pair(value, value), nullptr, &insertedNode);
      result.first = iterator(base_iterator(insertedNode, this));
      result.second = true;
    }
    return result;
  }

  void merge(set& other) {
    if (this == &other) return;
    this->mergeNodes(other.root_);
    other.root_ = nullptr;
  }

  iterator begin() {
    return iterator(base_iterator(this->minValueNode(this->root_), this));
  }

  const_iterator begin() const {
    return const_iterator(
        base_const_iterator(this->minValueNode(this->root_), this));
  }

  iterator end() { return iterator(base_iterator(nullptr, this)); }

  const_iterator end() const {
    return const_iterator(base_const_iterator(nullptr, this));
  }

  iterator lower_bound(const Key& key) {
    return iterator(base::lower_bound(key));
  }

  const_iterator lower_bound(const Key& key) const {
    return const_iterator(base::lower_bound(key));
  }

  iterator upper_bound(const Key& key) {
    return iterator(base::upper_bound(key));
  }

  const_iterator upper_bound(const Key& key) const {
    return const_iterator(base::upper_bound(key));
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto range = base::equal_range(key);
    return std::pair(iterator(range.first), iterator(range.second));
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    auto range = base::equal_range(key);
    return std::pair(const_iterator(range.first), const_iterator(range.second));
  }

  void erase(iterator pos) { base::erase(pos.it_); }

 protected:
  virtual bool should_insert(const value_type& val) {
    return !this->contains(val);
  }

  virtual bool should_insert(iterator it) { return it == end(); }

 private:
  void mergeNodes(Node* node) {
    if (!node) return;
    mergeNodes(node->left);
    mergeNodes(node->right);
    // «Отрываем» данный узел от дерева-источника
    node->left = node->right = nullptr;
    node->parent = nullptr;
    // Вставляем узел в текущее дерево, если не дубль
    if (this->should_insert(node->key())) {
      this->root_ = this->insertNode(this->root_, node, nullptr);
    } else {
      delete node;
    }
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_SET_H