#ifndef S21_CONTAINERS_STACK_H
#define S21_CONTAINERS_STACK_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "s21_containers_common.h"

namespace s21 {

template <typename value_type>
class stack {
 private:
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  node<value_type>* ptr_top_ = nullptr;
  size_type size_ = 0;

  void clear() {
    node<value_type>* ptr_tmp = ptr_top_;
    while (ptr_top_ != nullptr) {
      ptr_top_ = ptr_tmp->get_next();
      delete ptr_tmp;
      ptr_tmp = ptr_top_;
    }
    size_ = 0;
  }

 public:
  stack() : ptr_top_(nullptr), size_(0) {};
  stack(std::initializer_list<value_type> const& items) : stack() {
    // std::cout << "List constructor" << std::endl;
    for (const_reference item : items) {
      this->push(item);
    }
  };
  stack(const stack& s) : stack() {
    // std::cout << "Copy constructor" << std::endl;
    node<value_type>* ptr_s = s.ptr_top_;
    if (s.ptr_top_ != nullptr) {
      while (ptr_s->get_next() != nullptr) {
        ptr_s = ptr_s->get_next();
      };
      while (ptr_s != nullptr) {
        this->push(ptr_s->get_data());
        ptr_s = ptr_s->get_previous();
      };
    };
  };
  stack(stack&& s) noexcept : stack() {
    // std::cout << "Move constructor" << std::endl;
    *this = std::move(s);
  }
  ~stack() { this->clear(); };
  stack& operator=(stack&& s) {
    this->clear();
    size_ = s.size_;
    ptr_top_ = s.ptr_top_;
    s.size_ = 0;
    s.ptr_top_ = nullptr;
    return *this;
  }

  const_reference top() const {
    if (ptr_top_ == nullptr) {
      throw std::range_error("Stack is empty");
    }
    return ptr_top_->get_data();
  };

  bool empty() const { return ptr_top_ == nullptr; };

  size_type size() const { return size_; };

  void push(const_reference value) {
    ++size_;
    node<value_type>* new_node = new node<value_type>;
    new_node->set_data(value);
    new_node->set_next(ptr_top_);
    new_node->set_previous(nullptr);
    if (ptr_top_ != nullptr) ptr_top_->set_previous(new_node);
    ptr_top_ = new_node;
  }

  void pop() {
    if (size_ != 0) {
      --size_;
      node<value_type>* tmp = ptr_top_;
      ptr_top_ = ptr_top_->get_next();
      delete tmp;
      if (ptr_top_ != nullptr) ptr_top_->set_previous(nullptr);
    }
  };

  void swap(stack& other) {
    node<value_type>* ptr_tmp = other.ptr_top_;
    size_type size_tmp = other.size_;
    other.size_ = this->size_;
    other.ptr_top_ = this->ptr_top_;
    this->ptr_top_ = ptr_tmp;
    this->size_ = size_tmp;
  };

  void print() const {
    std::cout << "{";
    node<value_type>* ptr = ptr_top_;
    while (ptr != nullptr) {
      std::cout << ptr->get_data();
      ptr = ptr->get_next();
      if (ptr != nullptr) std::cout << ", ";
    }
    std::cout << "}" << std::endl;
  };
};

}  // namespace s21

#endif  // S21_CONTAINERS_STACK_H