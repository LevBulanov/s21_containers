#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "s21_avl_tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public avl_tree<Key, T> {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename s21::avl_tree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename s21::avl_tree<key_type, mapped_type>::const_iterator;
  using size_type = std::size_t;
  using tree = typename s21::avl_tree<key_type, mapped_type>;

 public:
  map() = default;

  map(std::initializer_list<value_type> const& items) : tree(items) {};

  map(const map& other) : tree(other) {}

  map(map&& other) noexcept : tree(other) {}

  ~map() = default;

  map& operator=(map&& other) {
    tree::operator=(std::move(other));
    return *this;
  }

  T& at(const key_type& key) {
    auto it = this->find(key);
    if (it == this->end()) {
      throw std::out_of_range("Key not found");
    }
    return it->second;
  }

  T& operator[](const key_type& key) {
    auto it = this->find(key);
    if (it == this->end()) {
      this->insert({key, T()});
      it = this->find(key);
    }
    return it->second;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = iterator(this->find(value.first));
    std::pair<iterator, bool> result = {it, false};
    if (it == this->end()) {
      it = tree::insert(value);
      result = {it, true};
    }
    return result;
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return insert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    auto try_insert = insert({key, obj});
    if (!try_insert.second) {
      this->operator[](key) = obj;
    }
    return try_insert;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return s21::vector<std::pair<iterator, bool>>();
  }
};
}  // namespace s21

#endif  // S21_MAP_H