#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
  class MapIterator;
  class MapConstIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = std::size_t;

 public:
  map() = default;

  map(std::initializer_list<value_type> const& items) {
    for (auto it = items.begin(); it != items.end(); ++it) {
      insert(*it);
    }
  };

  map(const map& other) {
    for (const auto& item : other) {
      insert(item);
    }
  }

  map(map&& other) noexcept {
    for (auto& item : other) {
      insert(std::move(item));
    }
  }

  ~map() = default;

  map& operator=(map&& other) {}

  T& at(const key_type& key) {
    auto it = find(key);
    if (it == end()) {
      throw std::out_of_range("Key not found");
    }
    return it->second;
  }

  T& operator[](const key_type& key) {
    auto it = find(key);
    if (it == end()) {
      insert({key, T()});
      it = find(key);
    }
    return it->second;
  }

  iterator begin() { return iterator(); }
  iterator end() { return iterator(); }

  bool empty() const { return true; }
  size_type size() const { return 0; }
  size_type max_size() const { return 0; }

  void clear() {}
  std::pair<iterator, bool> insert(const value_type& value) {
    return {iterator(), false};
  }

  std::pair<iterator, bool> insert(const Key& key, const T& value) {
    return {iterator(), false};
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
    auto it = find(key);
    if (it != end()) {
      it->second = obj;
      return {it, false};
    } else {
      return insert({key, obj});
    }
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return s21::vector<std::pair<iterator, bool>>();
  }

  void erase(iterator pos) {}
  void swap(map& other) {}
  void merge(map& other) {}

  bool contains(const key_type& key) const { return false; }
};
}  // namespace s21

#endif  // S21_MAP_H