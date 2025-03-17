#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_set.h"

namespace s21 {

template <typename Key>
class multiset : public s21::set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename s21::set<Key>::iterator;
  using const_iterator = typename s21::set<Key>::const_iterator;
  using size_type = size_t;
  using s21::set<Key>::set;
  using base = s21::set<Key>;

  multiset() : set<value_type>() {}

  multiset(std::initializer_list<value_type> const& items) : multiset() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      this->insert(*it);
    }
  }

 protected:
  bool should_insert(const Key& val) override {
    (void)val;
    return true;
  }
  bool should_insert(iterator it) override {
    (void)it;
    return true;
  }
};

}  // namespace s21

#endif  // S21_MULTISET_H