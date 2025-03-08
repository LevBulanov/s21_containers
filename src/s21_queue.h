#ifndef S21_CONTAINERS_QUEUE_H
#define S21_CONTAINERS_QUEUE_H

#include <cstddef>
#include <initializer_list>

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  // constructors, think about exceptions
  queue() = default;
  queue(std::initializer_list<value_type> const &items) : container_(items) {}
  queue(const queue &q) : container_(q.container_) {}
  queue(queue &&q) noexcept : container_(std::move(q.container_)) {}

  // destructor
  ~queue() = default;

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      container_ = std::move(q.container_);
    }
    return *this;
  }

  const_reference front() const { return container_.front(); }

  const_reference back() const { return container_.back(); }

  bool empty() const { return container_.empty(); }

  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

  void swap(queue &other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    container_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<value_type> container_;
};

}  // namespace s21

#endif