#ifndef S21_CONTAINERS_AVL_TREE_H
#define S21_CONTAINERS_AVL_TREE_H

#include <initializer_list>
#include <limits>

#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class avl_tree {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  struct tree_node {
    value_type data;
    tree_node* left;
    tree_node* right;
    tree_node* parent;
    int height;

    tree_node(value_type data, tree_node* parent = nullptr)
        : data(data),
          left(nullptr),
          right(nullptr),
          parent(parent),
          height(1) {}

    key_type key() const { return data.first; }
  };

  class iterator {
   public:
    using pointer = value_type*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    iterator() : node_(nullptr), tree_(nullptr) {}
    iterator(tree_node* node, const avl_tree<key_type, mapped_type>* tree)
        : node_(node), tree_(tree) {}

    reference operator*() { return node_->data; }
    pointer operator->() { return &(node_->data); }

    iterator& operator++() {
      if (node_ == nullptr) return *this;
      if (node_->right != nullptr) {
        node_ = minimum(node_->right);
      } else {
        tree_node* p = node_->parent;
        while (p != nullptr and node_ == p->right) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    iterator& operator--() {
      if (node_ == nullptr) {
        node_ = maximum(tree_->root_);
      } else if (node_->left != nullptr) {
        node_ = maximum(node_->left);
      } else {
        tree_node* p = node_->parent;
        while (p != nullptr and node_ == p->left) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    bool operator==(const iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   protected:
    tree_node* node_;
    const avl_tree<key_type, mapped_type>* tree_;
    friend class avl_tree<key_type, mapped_type>;

    tree_node* minimum(tree_node* node) const {
      while (node and node->left != nullptr) node = node->left;
      return node;
    }

    tree_node* maximum(tree_node* node) const {
      while (node and node->right != nullptr) node = node->right;
      return node;
    }
  };

  class const_iterator {
   public:
    using pointer = const Key*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    const_iterator() : node_(nullptr), tree_(nullptr) {}
    const_iterator(tree_node* node, const avl_tree<key_type, mapped_type>* tree)
        : node_(node), tree_(tree) {}
    const_iterator(const iterator& it) : node_(it.node_), tree_(it.tree_) {}

    const_reference operator*() const { return node_->data; }
    pointer operator->() const { return &(node_->data); }

    const_iterator& operator++() {
      if (node_ == nullptr) return *this;
      if (node_->right != nullptr) {
        node_ = minimum(node_->right);
      } else {
        tree_node* p = node_->parent;
        while (p != nullptr and node_ == p->right) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    const_iterator& operator--() {
      if (node_ == nullptr) {
        node_ = maximum(tree_->root_);
      } else if (node_->left != nullptr) {
        node_ = maximum(node_->left);
      } else {
        tree_node* p = node_->parent;
        while (p != nullptr and node_ == p->left) {
          node_ = p;
          p = p->parent;
        }
        node_ = p;
      }
      return *this;
    }

    bool operator==(const const_iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

   private:
    tree_node* node_;
    const avl_tree<key_type, mapped_type>* tree_;
    friend class avl_tree<key_type, mapped_type>;

    tree_node* minimum(tree_node* node) const {
      while (node and node->left != nullptr) node = node->left;
      return node;
    }

    tree_node* maximum(tree_node* node) const {
      while (node and node->right != nullptr) node = node->right;
      return node;
    }
  };

  // конструкторы
  avl_tree() : root_(nullptr) {}

  avl_tree(std::initializer_list<value_type> const& items) : root_(nullptr) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      insert(*it);
    }
  }

  avl_tree(const avl_tree& other) : root_(copy_tree(other.root_, nullptr)) {}

  avl_tree(avl_tree&& other) noexcept : root_(other.root_) {
    other.root_ = nullptr;
  }

  avl_tree& operator=(avl_tree&& other) noexcept {
    if (this != &other) {
      this->clear();
      root_ = other.root_;
      other.root_ = nullptr;
    }
    return *this;
  }

  bool empty() const { return (root_ == nullptr); }

  size_type size() const {
    size_type counter = 0;
    for (auto it = this->begin(); it != this->end(); ++it) {
      counter += 1;
    }
    return counter;
  }

  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(tree_node) / 2;
  }

  void clear() {
    destroy(root_);
    root_ = nullptr;
  }

  iterator insert(const value_type& val) {
    tree_node* inserted_node = nullptr;
    root_ = insert(root_, val, nullptr, &inserted_node);
    return iterator(inserted_node, this);
  }

  void remove(const Key& key) {  // удаление первого элемента с заданным ключем
    root_ = remove(root_, root_, key);
  }

  void erase(iterator pos) {  // удаление конкретного элемента
    if (pos == end()) return;
    root_ = erase_node(root_, pos.node_);
  }

  void swap(avl_tree& other) {
    if (this == &other) return;
    tree_node* temp = this->root_;
    this->root_ = other.root_;
    other.root_ = temp;
  }

  void merge(avl_tree& other) {
    if (this == &other) return;
    merge_nodes(other.root_);
    other.root_ = nullptr;
  }

  size_type count(const Key& key) const { return count(root_, key); }

  bool contains(const Key& key) const {
    return search(root_, key).node_ != nullptr;
  }

  const_iterator find(const Key& key) const { return search(root_, key); }

  iterator find(const Key& key) { return search(root_, key); }

  const_iterator lower_bound(const Key& key) const {
    return search_lower_bound(root_, key);
  }

  iterator lower_bound(const Key& key) {
    return search_lower_bound(root_, key);
  }

  const_iterator upper_bound(const Key& key) const {
    return search_upper_bound(root_, key);
  }

  iterator upper_bound(const Key& key) {
    return search_upper_bound(root_, key);
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return std::pair<const_iterator, const_iterator>(
        search_lower_bound(root_, key), search_upper_bound(root_, key));
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::pair<iterator, iterator>(search_lower_bound(root_, key),
                                         search_upper_bound(root_, key));
  }

  const_iterator begin() const { return iterator(min_value_node(root_), this); }

  iterator begin() { return iterator(min_value_node(root_), this); }

  const_iterator end() const { return iterator(nullptr, this); }

  iterator end() { return iterator(nullptr, this); }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(args));
    ((results.push_back(
         std::make_pair(insert(std::forward<Args>(args)), true))),
     ...);  // в multiset всегда успешная вставка
    return results;
  }

  ~avl_tree() { destroy(root_); }

 protected:
  tree_node* root_;
  friend class iterator;

  tree_node* copy_tree(tree_node* node, tree_node* parent) {
    if (!node) return nullptr;
    tree_node* new_node = new tree_node(node->data, parent);
    new_node->left = copy_tree(node->left, new_node);
    new_node->right = copy_tree(node->right, new_node);
    new_node->height = node->height;
    return new_node;
  }

  void destroy(tree_node* node) {
    if (node) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }

  int height(tree_node* node) { return node ? node->height : 0; }

  int get_balance(tree_node* node) {
    return node ? (height(node->left) - height(node->right)) : 0;
  }

  tree_node* rotate_right(tree_node* y) {
    tree_node* x = y->left;
    tree_node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->parent = y->parent;
    y->parent = x;
    if (T2 != nullptr) T2->parent = y;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
  }

  tree_node* rotate_left(tree_node* x) {
    tree_node* y = x->right;
    tree_node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->parent = x->parent;
    x->parent = y;

    if (T2 != nullptr) T2->parent = x;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return y;
  }

  tree_node* min_value_node(tree_node* node) const {
    tree_node* current = node;
    while (current and current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  tree_node* balance(tree_node* node) {
    int balanceFactor = get_balance(node);
    // Left Left
    if (balanceFactor > 1 and get_balance(node->left) >= 0) {
      return rotate_right(node);
    }
    // Left Right
    if (balanceFactor > 1 and get_balance(node->left) < 0) {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }
    // Right Right
    if (balanceFactor < -1 and get_balance(node->right) <= 0) {
      return rotate_left(node);
    }
    // Right Left
    if (balanceFactor < -1 and get_balance(node->right) > 0) {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    }
    return node;
  }

  // копирующая вставка по ключю
  tree_node* insert(tree_node* node, const value_type val, tree_node* parent,
                    tree_node** inserted_node) {
    if (node == nullptr) {
      *inserted_node = new tree_node(val, parent);
      return *inserted_node;
    }
    if (val.first < node->key()) {
      node->left = insert(node->left, val, node, inserted_node);
    } else {
      node->right = insert(node->right, val, node, inserted_node);
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    tree_node* balanced = balance(node);
    balanced->parent = parent;
    return balanced;
  }

  // Вспомогательный метод для вставки уже выделенного узла.
  // Перед вставкой нужно обнулить левый и правый дочерние указатели узла.
  tree_node* insert_node(tree_node* curr, tree_node* node, tree_node* parent) {
    if (!curr) {
      node->parent = parent;
      node->left = node->right = nullptr;
      node->height = std::max(height(node->left), height(node->right)) + 1;
      return node;
    }
    if (node->key() < curr->key())
      curr->left = insert_node(curr->left, node, curr);
    else
      curr->right = insert_node(curr->right, node, curr);
    curr->height = std::max(height(curr->left), height(curr->right)) + 1;
    return balance(curr);
  }

  void merge_nodes(tree_node* node) {
    if (!node) return;
    merge_nodes(node->left);
    merge_nodes(node->right);
    // «Отрываем» данный узел от дерева-источника
    node->left = node->right = nullptr;
    node->parent = nullptr;
    // Вставляем узел в текущее дерево
    root_ = insert_node(root_, node, nullptr);
  }

  void transplant(tree_node*& root, tree_node* u, tree_node* v) {
    if (u->parent == nullptr) {
      // u - корень дерева
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    if (v) v->parent = u->parent;
  }

  // удаляет по указателю
  tree_node* erase_node(tree_node*& root, tree_node* target) {
    if (target == nullptr) return root;
    if (target->left == nullptr) {
      transplant(root, target, target->right);
      delete target;
    } else if (target->right == nullptr) {
      transplant(root, target, target->left);
      delete target;
    } else {
      tree_node* succ = min_value_node(target->right);
      if (succ->parent != target) {
        transplant(root, succ, succ->right);
        succ->right = target->right;
        if (succ->right) succ->right->parent = succ;
      }
      transplant(root, target, succ);
      succ->left = target->left;
      if (succ->left) succ->left->parent = succ;
      delete target;
    }
    if (root) {
      root->height = std::max(height(root->left), height(root->right)) + 1;
      root = balance(root);
    }
    return root;
  }

  tree_node* remove(tree_node*& root, tree_node* node, const Key& key) {
    if (node == nullptr) return node;
    if (key < node->key()) {
      node->left = remove(root, node->left, key);
    } else if (key > node->key()) {
      node->right = remove(root, node->right, key);
    } else {
      // Узел для удаления найден
      if (node->left == nullptr) {
        tree_node* temp = node->right;
        transplant(root, node, temp);
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        tree_node* temp = node->left;
        transplant(root, node, temp);
        delete node;
        return temp;
      } else {
        tree_node* successor = min_value_node(node->right);
        if (successor != node->right) {
          transplant(root, successor, successor->right);
          successor->right = node->right;
          if (successor->right) {
            successor->right->parent = successor;
          }
        }
        transplant(root, node, successor);
        successor->left = node->left;
        if (successor->left) {
          successor->left->parent = successor;
        }
        delete node;
        return successor;
      }
    }
    node->height = std::max(height(node->left), height(node->right)) + 1;
    return balance(node);
  }

  size_type count(tree_node* node, const Key& key) const {
    if (node == nullptr) return 0;
    if (key < node->key())
      return count(node->left, key);
    else if (node->key() < key)
      return count(node->right, key);
    else {
      return 1 + count(node->left, key) + count(node->right, key);
    }
  }

  iterator search(tree_node* node, const Key& key) const {
    if (node == nullptr) {
      return iterator(node, this);
    }
    if (key == node->key()) {
      return iterator(node, this);
    }
    if (key < node->key()) {
      return search(node->left, key);
    }
    return search(node->right, key);
  }

  iterator search_lower_bound(tree_node* node, const Key& key) const {
    tree_node* res = nullptr;
    while (node != nullptr) {
      if (!(node->key() < key)) {  // node->key >= key
        res = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return iterator(res, this);
  }

  iterator search_upper_bound(tree_node* node, const Key& key) const {
    tree_node* res = nullptr;
    while (node != nullptr) {
      if (key < node->key()) {
        res = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return iterator(res, this);
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_AVL_TREE_H